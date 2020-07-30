# @(#)46        1.6  src/bos/usr/lib/kdb/KDB.perlmod, cmdkdb, bos530 4/26/01 08:31:17
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/KDB.perlmod 1.6 
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
#   FUNCTIONS: KDB CLASS 
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


			package KDB;


################################################################


use English;
use init qw( $Warn $Prompt );

my $state;
my $kdbpid;

local $SIG{PIPE} = \&kdbpipe;		### Initialize some signal handlers
local $SIG{ALRM} = \&kdbalarm;
local $SIG{__WARN__} = sub { $Warn = $_[0] };



###############################
#
# Create the KDB object
#
###############################


sub new {

	my $class = shift;
	my $self = {};
	bless $self, $class;		### Attach the object to the class
	return $self;
}



########
#
# open
#
########

### Launch the kdb command
### Initialize the communication pipe and state


sub open {

        use IPC::Open2;

        my $self = shift;	### First argument is the class

				### Build the kdb command and open

	$kdbpid = eval { open2(\*RDR, \*WTR, join " ", @_ , "2>/dev/null" )};

	die $@ if $@;           ### That will test an error on eval

	$RS = ")>";		### Set the INPUT SEPARATOR to KDB prompt

        $_ = <RDR>;		### Read on pipe

	if (/\)>/) {		### Check for the KDB prompt 

				### update the 'state' and 'Dbg_Count' for flow control
		$state = 'UP';
		$Dbg_Count = 0;
						### set toggles 
		$self->sendcmd('set 9');	### 'display_stack_frames'
		$self->sendcmd('set 10');	### and 'display_stacked_regs'
		$self->readcmd();
	}
	else {
		$state = 'DOWN';
		warn "\n\n ***  ERROR LAUNCHING KDB  ***\n$!\n$?\n$_\n\n";
	}

}



###########
#
# sendcmd
#
###########

### Send a kdb subcommand


sub sendcmd {

	my $self = shift;		### First argument is always the class

					### Check 'state' before sending
	die "State is down" if ($state eq 'DOWN');

	alarm 60;  		### reinitialize the alarm each sending

	$demand = shift;		### write on the pipe
	if ($demand ne "\cC") {
		print WTR $demand, "\n";
	}


	$Dbg_Count += 1;


}



###########
#
# readcmd
#
###########

### Read all pending KDB replies
### NOTE : to manage errors properly this function should be called via an eval


sub readcmd {

	my $self = shift;		### First argument is always the class

	my $replies = '';

	$FH = select;
	select RDR;
	$|=1;

	while (1) {

		### Check 'state' before reading
		### because readcmd should have been called via an eval - 
		### update $@ in case of error and UNDEFINED will be returned

		die "State is down" if ($state eq 'DOWN');

		### Collect the data from the pipe

		while (1) {
			sysread RDR,$reply, 50;
			$replies = join '', $replies, $reply;
			$rep = sprintf "%s", $replies;

			if ( $rep =~ /\(\w+\)> $/ ) {
				$isprompt = 1;
				last;
			}

			if ( $rep =~ /Enter.*(?=:)/ ) {
				$isprompt = 0;
				last;
			}

			if ( $rep =~ /\(in hex\)(?=:)/ ) {
				$isprompt = 0;
				last;
			}

		}


		$nb = $rep =~ s#\(\w+\)>#\(\w+\)>#g;


		if ( $isprompt == 0 ) {

			$Dbg_Count -= ($nb + 1);
			last;
		}
		else {
			next if ( $Dbg_Count - $nb );
			$Dbg_Count -= $nb;
			$rep =~ /\(\w+\)> $/;
			$Prompt = $MATCH;
			last;
		}
	}


	select $FH;
	$|=1;

	alarm 0;	### all data have been picked up : unset the alarm

	return $replies;
}



#######################
#
# PIPE signal handler
#
#######################

### When signal PIPE received - stop the flow on the pipe


sub kdbpipe {

	$state = 'DOWN';
}


#######################
#
# ALRM signal handler
#
#######################


### When signal ALRM received - stop the flow on the pipe and kill the kdb command


sub kdbalarm {

	$state = 'DOWN';

        kill 9, $kdbpid;
        wait;


}

########
#
# close
#
########

sub close {

	my $self = shift;

	if ( $state eq 'UP' ) {	
				### Send 'quit' to KDB and close the filehandles
		$self->sendcmd('q');
		close RDR;
		close WTR;
	}
}

1;
