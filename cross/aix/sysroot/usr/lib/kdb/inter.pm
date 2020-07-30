# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/inter.perlmod 1.9 
#  
# Licensed Materials - Property of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 1999,2001 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 

use init;
use init qw( $BaseName $smode $Prompt );

use English;
use POSIX (termios_h);
use FileHandle;
use GetLine;

sub int_handle {	### ^C should be sent to KDB instead of exiting
	$Dbg->sendcmd("\cC");
	my $kdbrep = $Dbg->readcmd;
	$kdbrep =~ s#({{ERR\s*|ERR}}\s*)##g;
	$kdbrep =~ s# \( \w+ \) > \s* $ ##xs;
	print STDOUT $kdbrep;
	die;
}

sub print_more {

        my $line = shift;

        if ( $totlines <  $kdb_screen_size ) {
                print STDOUT "$line\n";
                $totlines += 1;
        }
        else {
                print STDOUT $Prompt, '> more (^C to quit) ? ';

		raw_on();
		sysread( STDIN, $c, 1);
                while ( $c ne ' ' and $c ne "\n" and $c ne "\cC" ) {
			print STDOUT "\a";
			sysread( STDIN, $c, 1);
                }
		raw_off();

                if ( $c eq ' ' ) {
                        ### one more line can be printed
                        print STDOUT "\n$line\n";
                        $totlines += 1;
                        return;
                }

                if ( $c eq "\n" ) {
                        print STDOUT "\n$line\n";
                        $totlines = 1;
                }

		if ( $c eq "\cC" ) {
			print STDOUT "\n";
			$stop = 1;
		}
        }
}

sub raw_on {
	$term->setlflag($noecho);
	$term->setcc(VTIME, 1);
	$term->setattr($fd_stdin, TCSANOW);
}

sub raw_off {
	$term->setlflag($oterm);
	$term->setcc(VTIME, 0);
	$term->setattr($fd_stdin, TCSANOW);
}


##############################################################################
#
#			INTERACTIVE MODE
#
##############################################################################

	
### Initialize global variables

$logon = 0;
$logfile = '';
@MacroFiles = ();			### Array of macros files

$Dbg->sendcmd('set');
$kdb_screen_size = $Dbg->readcmd;
$kdb_screen_size =~ /\sscreen_size\s+(\d+)\s+/;
$kdb_screen_size = $1;

$term = POSIX::Termios->new;
$fd_stdin = fileno(STDIN);
$term->getattr($fd_stdin);
$oterm = $term->getlflag;

$echo = ISIG | ICANON | ECHO | ECHOK | ECHOE | ECHONL;
$noecho = $oterm & ~$echo;

$| = 1;		### AUTOFLUSH

### If a script has been specified by the -s option : run it first

require "$Script" if defined $Script;

### Set the user environment

if ($ENV{HOME} eq '/') {
	$histfile = join '',$ENV{HOME},'.adumphist';
	$rcfile = join '',$ENV{HOME},'.adumprc.pm';
} else {
	$histfile = join '/',$ENV{HOME},'.adumphist';
	$rcfile = join '/',$ENV{HOME},'.adumprc.pm';
}

do "$rcfile";
print "\'.adumprc\' : $@\n" unless (!$@);

### Initialize the command-line editing

my %EDIT = ( 'emacs' => 1, 'vi' => 2 );
$editor = $EDIT{$ENV{EDITOR}};
$histsize = ( $ENV{ADUMPHISTSZ} ? $ENV{ADUMPHISTSZ} : 128 );

GetLine::gl_init( $editor, $histfile, $histsize, 0);

### Display the KDB prompt

$Dbg->sendcmd('');
$Prompt = $Dbg->readcmd;
$Prompt =~ s/\s*\n//;
$Prompt = join '',"\n",$Prompt;

$smode = 0;

### Start the interactive processing

local $SIG{__WARN__} = sub { die; };

while (1) {

	local $SIG{INT} = \&int_handle;

eval {

	$ErrFound = undef;

	@incmd = ();
	$#incmd = 256;

	$len = GetLine::getline($Prompt, $incmd[0], 256, 0);
	$incmd = sprintf "%s",(@incmd);

	$fd = select;
	if ( $fd ne 'main::STDOUT' ) {
		print $Prompt," $incmd\n";
	}

	chomp $incmd;		### \n will be added by sendcmd anyway

	$incmd =~ s/^\s*//;

	if ( $incmd ) {		### Unless data from keyboard empty

		### case 1 : the subcommand is for shell

		if ( $incmd =~ s# ^! \s* (\w+) #\1#x ) {
	
			if ( $GID != $EGID && $UID ) {
				if (fork) {
					wait;
				}
				else {
					system($incmd);
				}
			}
			else {
				system($incmd);
			}
			die;
		}


		### case 2 : the subcommand is for exiting

		if ( $incmd eq 'q' or $incmd eq 'g' or $incmd eq 'e' or $incmd eq 'quit' ) {
				last;
		}


		### default :
		### the subcommand could be EITHER a Perl instruction/script
		### OR a kdb subcommand

		### Perl 'eval' successfully barewords and 
		### one-word kdb subcommands will then be intercepted as Perl instruction
		### Parenthesis will force interpretation as a function if only one word


		if ( $incmd =~ m# ^ \s* \w+ \s* $ #x ) {
			$functcmd = join '', $incmd, "\(\)";
			eval $functcmd;
		}
		else {
			if ( $incmd =~ m# ^ \s* \w+ \s* ; #x ) {
				$functcmd = $incmd;
				$functcmd =~ s# ^ \s* (\w+) \s* ; #\1\(\);#x;
				eval $functcmd;
			}
			else {
				eval $incmd;
			}
		}


		print STDOUT "$ErrFound\n" if ( defined $ErrFound );

		my $ErrSave = join "\n", $@, $ErrFound if ( defined $@ );

		die unless $@;
			
		### Assume it is a kdb subcommand

		$stop = 0;
		$totlines = 0;

		### ...which could include a pipe to the shell

		( $incmd, $tosh ) = split /(?=\|)/, $incmd, 2;
		
		### This is help for adump	
		
		if(($incmd eq "h") || ($incmd eq "help")||($incmd eq "?")){
        		print STDOUT "\n\nCMD\t\t\tFUNCTION\t\t\tARG\n";
		        print STDOUT "\n\t\t*** basic adump commands ***\n";
		        print STDOUT "\nlistmacro\t\tlist available macros\n";
		        print STDOUT "redirect\t\tredirects output\t\t[path]\n";
		        print STDOUT "set lines,\t\tsets screen size\t\t[num lines]\n";
		        print STDOUT "print\t\t\tprints value\t\t\t[\$varname]\n\n";
		        print STDOUT "\n\t\t*** Help for kdb ***\n\n";
		}

		### Use 'eval' to prevent from some peculiar Perl interpretation

		$Dbg->sendcmd(eval (sprintf "\'%s\'",$incmd));

		$buffer = $Dbg->readcmd;

		### Managing incomplete kdb subcommands, such as scb/pte...

		if ($buffer =~ /\(\w+\)>/) {
			($cmdpart, $buffer) = split m# (?=\n) #mx, $buffer, 2;
		}
		else {
			do {
				($cmdpart, $buffer) = split m# (?=\n) #mx, $buffer, 2;
				print STDOUT $buffer;
				($buffer, $moreinfo) = split m# (?=[^\n]+$) #sx, $buffer, 2;

				@incmd = ();
				$#incmd = 256;
				$len = GetLine::getline($moreinfo, $incmd[0], 256, 0);
				$incmd = sprintf "%s",(@incmd);

				if ( $fd ne 'main::STDOUT' ) {
					print $incmd,"\n";
				}

				chomp $incmd;
				$kdbcmd = sprintf "\'%s\'",$incmd;

				$Dbg->sendcmd(eval $kdbcmd);
				$buffer = $Dbg->readcmd;

			} until ($buffer =~ /\(\w+\)>/);

			($cmdpart, $buffer) = split m# (?=\n) #mx, $buffer, 2;
		}

		my $iserr = $buffer =~ s#({{ERR\s*|ERR}}\s*)##g;

		if ($iserr) {
			print STDOUT $ErrSave,"\n";
		}

		### Manage pipes to shell

		$fd = select;

		if ( defined $tosh ) {

			$cmdpart = join ' ', $cmdpart, $tosh;
			$tosh =~ s/^\|//;

			### Manage a temporary file
			### because SIGINT cannot be catched while print'

			umask 0;
			sysopen BUFFER, "/tmp/buffer.out", O_CREAT|O_RDWR|O_APPEND, 0666;
			select BUFFER;
			$| = 1;
			print $buffer;

			select $fd;
			$| = 1;

			$buffer = `cat /tmp/buffer.out|$tosh`;
			`rm /tmp/buffer.out`;
		}


		### Simulating the KDB more functionality...

		if ( $fd eq 'main::STDOUT' ) {

			### Guess a bug with split...workaround!
			$buffer = $cmdpart unless ($buffer);
			$buffer =~ s# \( \w+ \) > \s* $ ##xs;

			do {
				($line, $extra) = split /\n/, $buffer, 2;
				print_more $line;
				$buffer = $extra;
		
			} until ( $stop == 1 or !defined $extra );
		}

		### ...unless redirection

		else {
			$buffer =~ s# \( \w+ \) > \s* $ ##xs;
			print $buffer,"\n";
		}
	}
	else {  ### Ensure a kdb-like behaviour

		$stop = 0;
		$totlines = 0;

		$Dbg->sendcmd('');
		$buffer = $Dbg->readcmd;
	
		my $iserr = $buffer =~ s#({{ERR\s*|ERR}}\s*)##g;

		if ($iserr) {
			print STDOUT $ErrSave,"\n";
		}

		$buffer =~ s# \( \w+ \) > \s* $ ##xs;

		$fd = select;

		if ( $fd eq 'main::STDOUT' ) {
			do {
				($line, $extra) = split /\n/, $buffer, 2;
				print_more $line;
				$buffer = $extra;
			} until ( $stop == 1 or !defined $extra );
		}
		else {
			print $buffer,"\n";
		}
	}

};

### Retrieve the KDB prompt

$Prompt = join '',"\n",$Prompt;
if ($fd eq 'main::STDOUT' and $incmd =~ /print/) {
	print STDOUT "\n";	
}
	
}

1;

BEGIN {

$RS = "\n";

########
#
# set
#
########


sub set {

	die unless (@_);       ### at least one argument is expected

	my $type = lc shift;

	for ($type) {

		### set lines for the screen size
		/^lines$/ and do {
		
					my $choice = shift;

					if ($ret = $choice =~ /^\d+$/) {

						$kdb_screen_size = $choice;
					
						### send to KDB for compatibility
						my $cmd = sprintf "\'set 3 %s\'",$choice;
						$Dbg->sendcmd(eval $cmd);
						$Dbg->readcmd;	### ignore
					}

					last;
				};

		die;
	}
}
		
############
#
# redirect
#
############


sub redirect {

	if (@_) {               ### redirection of the output

		umask 0;        ### or can't create the file
		my $outfile = shift;
		sysopen TH, $outfile, O_CREAT|O_RDWR|O_APPEND, 0666;
		select TH;
		$| = 1;         ### set autoflush on THIS filehandle

	}

	else {			### restore redirection to STDOUT

		select STDOUT;
		$| = 1;
	}
}



########
#
# def
#
########


sub def {

	die unless (@_); 	### arguments expected

	my $type = lc shift;

	for ($type) {

		### define a file as a macros file
	
		/^macrofile$/ and do {

			my $choice = shift;

			### the file should not exist

			if ( -e $choice or -s $choice ) {
				print STDOUT "\'$choice\' already exists\n";
				last;
			}
	
			### file name should be a package name

			if ( $ret = $choice =~ /(\w+)\.pm$/ ) {

				$BaseName = $1;

				do {
					umask 0;
					$ret = sysopen MF, $choice, O_CREAT|O_RDWR|O_APPEND, 0666;

					last unless $ret;
					my $SV = select;
					select MF;
					$|=1;

					do '/usr/lib/kdb/MacroTemplate.pm';

					select $SV;
					$|=1;
					close MF;

				} unless -f $choice;

			}
			else {
				print STDOUT "\'$choice\' can't name a macros file\n";
			}

			last;
		};
				
		die;
	}
}


##########
#
# load
#
##########


sub load {

	die unless (@_);	### arguments expected

	my $type = lc shift;

	for ($type) {

		### load a macros file : the file should exist as a text file

		/^macrofile$/ and do {

			my $choice = shift;

			if ( -T $choice and $ret = $choice =~ /(\w+)\.pm$/ ) {

				$BaseName = $1;
				my $macropack = $1;
				
				### Add the directory to the Perl search path

				my $is = 0;
				chomp( my $dir = `dirname $choice` );

				for ( $i=0;$i<=$#INC;$i++ ) {
					
					if ( `cd $dir;pwd` eq `cd $INC[$i];pwd`) {
						$is = 1;
						last;
					}
				}

				unless ($is) { 
					$strdir = sprintf( "\'%s\'",$dir);

					eval "use lib $strdir";
				}

				### Load the package with macros

				eval "no $macropack";
				if ($@) {
					print "NO $@\n";
					return;
				}

				eval "use $macropack";
				if ($@) {
					print "USE $@\n";
					eval "no $macropack";
					return;
				}
				
				### Info for listmacro()

				$is = 0;

				for ( $i=0;$i<=$#MacroFiles;$i++ ) {

					chomp( my $dir2 = `dirname $MacroFiles[$i]` );
					if ( `cd $dir;pwd` eq `cd $dir2;pwd`
					  && "$macropack.pm\n" eq `basename $MacroFiles[$i]` ){

						$is = 1;
						last;
					}
				}

				unless ($is) {
	
					unless ( $ret = $choice =~ /^[\.\/]/ ) {
						$choice = './'.$choice;
					}
						
					push @MacroFiles, ($choice);
				}

			} 
			else {
				print STDOUT "\'$choice\' is not a macro file\n";
			}

			last;
		};

		die;
	}

}



############
#
# listmacro
#
############


sub listmacro {

	for $key (sort keys %main::MacroLib::) {

		local *sym=$main::MacroLib::{$key};
		print STDOUT "\t$key\n" if (defined &sym && $key ne 'unimport'
							&& $key ne 'cached');
	}

	for ($i=0;$i<=$#INC;$i++) {	

		my $libdir = `cd $INC[$i];pwd`;

		for ( $j=0;$j<=$#MacroFiles;$j++ ) {

			my ( $macrodir, $macrofile ) = split /(\w+)\.pm$/, $MacroFiles[$j] ;

			if ( $libdir eq `cd $macrodir;pwd` ) {
				print STDOUT "Library $macrofile :\n";

				for $key (sort keys %{"main::".$macrofile."::"}) {

					local *sym = ${"main::".$macrofile."::"}{$key};
					print STDOUT "\t$key\n" if (defined &sym && $key ne 'unimport' && $key ne 'cached');
				}

			}
		}
	}
}


##########
#
# unload
#
##########


sub unload {

	die unless (@_);        ### arguments expected

	my $type = lc shift;

	for ($type) {

		### unload a macros file

		/^macrofile$/ and do {

			my $choice = shift;

			if ( -T $choice and $ret = $choice =~ /(\w+)\.pm$/ ) {

				$BaseName = $1;
				my $macropack = $1;


				eval "no $macropack";
				if ($@) {
					print "$@\n";
					return;
				}

				### Info for listmacro()

				my $is = 0;
				chomp( my $dir = `dirname $choice` );
				my $macrosize = $#MacroFiles + 1;

				for ( $i=0; $i<$macrosize; $i++ ) {

					chomp( my $dir2 = `dirname $MacroFiles[$i]` );

					if ( `cd $dir;pwd` eq `cd $dir2;pwd`
					  && "$macropack.pm\n" eq `basename $MacroFiles[$i]` ){


						for ( $i; $i<$macrosize; $i++ ) {
							splice @MacroFiles, $i, 1;
						}

						last;
					}
				}
			}

			last;
		};

		die;
	}

}

			
##########
#
# reload
#
##########


sub reload {

	die unless (@_);		### arguments expected

	my $choice = shift;		### Get package name
	
	eval "no $choice";
	if ($@) {
		print "NO $@\n";
		return;
	}

	eval "use $choice";
	if ($@) {
		print "USE $@\n";
		eval "no $choice";
		return;
	}
}

}

		

