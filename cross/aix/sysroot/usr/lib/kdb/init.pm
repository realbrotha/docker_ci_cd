# @(#)30        1.6  src/bos/usr/lib/kdb/init.perlmod, cmdkdb, bos530 4/26/01 08:29:49
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/init.perlmod 1.6 
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
#
#   COMPONENT_NAME: kdb
#
#   FUNCTIONS: init script for AUTOMATED DUMP - set the environment
#
#   ORIGINS: 83
#
#
#   (C) COPYRIGHT International Business Machines Corp. 1999
#   All Rights Reserved
#   Licensed Materials - Property of IBM
#   US Government Users Restricted Rights - Use, duplication or
#   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#

################################################################


			package init;


################################################################


use Exporter ();		### Export some global variables
@ISA = qw(Exporter);
@EXPORT = qw( $Dbg $Warn $Dump $Kernel $Memory $Script $ErrFound cached );
@EXPORT_OK = qw( $BaseName $smode $Prompt );

require KDB;			### Include some packages
require Dump;
require Kernel;
require Memory;

require packlib; 		### All the dump objects


###################################
#
#	parsing the command line
#
###################################



### Build a string with the arguments to apply the search pattern to

my $arg = join ' ',(@ARGV);

### Search the UNIX - all UNIX qualified pathnames are supported -

my ( $unix ) = $arg =~ m# -u \s+ ([\.\/\w]+) #x;

### Search the kdb command - all UNIX qualified pathnames are supported -

my ( $kdb ) = $arg =~ m# -k \s+ ([\.\/\w]+) #x;

### Search the dump - all UNIX qualified pathnames are supported -

my ( $dump ) = $arg =~ m# -d \s+ ([\.\/\w]+) #x;

### Search the script - all UNIX qualified pathnames are supported -

( $Script ) = $arg =~ m# -s \s+ ([\.\/\w]+) #x;


##################################
#
#	set the default values
#
##################################



$unix ||= '/unix';
$kdb ||= '/usr/sbin/kdb';



### If no dump supplied : call `sysdumpdev -L` for defaults
### according to the processing done by the snap command

unless ($dump)
{
	$_ = `sysdumpdev -L 2>/dev/null`;
	die "A recent dump does not exist.\n" if $?;

	/Device name\W\s*(.+)\n(.*\n)*Size\W\s*(\d+)/;
	my $dumpdev = $1;
	my $dumpsize = $3;
	die "The dump that was taken is zero bytes.\n" unless $dumpsize;

	my $cmd = "lsps `basename $dumpdev 2>/dev/null` 2>/dev/null";
	`$cmd`;
	if ($? == 0) {			### the dump device is paging space

		my $ret = /Dump copy filename\W\s*(.+)/;
		$dump = $1 if $ret or die "A dump was taken to $dumpdev but attempt to copy the dump to a file on boot failed.\n";
	} 
	else {				### the dump is not a paging space

		my $ret = $dumpdev =~ /^\//;
		if ($ret) {
			$dump = $dumpdev;
		}
		else { 			### the dump is remote

			my ( $hostname, $fullname ) = split /:/, $dumpdev, 2;
			my $filedir = `dirname $fullname`;
			my $basename = `basename $fullname`;

			`mount $hostname:$filedir /mnt >/dev/null`;
			die "Unable to copy the dump from $hostname:$fullname\n" if $?;
			$dump = "/mnt/$basename";
		}
	}
			
}




#####################################
#
#	Launch the Kernel Debugger
#
#####################################

$Warn ="";			### Initialization of global $Warn and $Dbg
$Dbg = KDB->new;

eval { $Dbg->open($kdb.' -A',$dump,$unix) };

die $@ if $@;			### Check for errors when opening the pipe

die "$Warn" if $Warn;		### Check for KDB errors when launching




#####################################################
#
#	Create the global Dump and Kernel objects
#
#####################################################



$Dump = Dump->new($_);		### $_ still contains the KDB header at launching

$Kernel = Kernel->new;		### Initialization of global $Kernel and $Memory

$Memory = Memory->new;

$ErrFound = undef;

$Prompt = undef;

$main::{cached} = $main::init::{cached};
sub cached {
	my $var = shift;
	if (defined $var) {
		return $smode;
	}
	else {
		return $var;
	}
}

$smode = 1;

END { 
	$Dbg->close if defined $Dbg;
}

1;
