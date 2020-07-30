# @(#)42        1.4  src/bos/usr/lib/kdb/Dump.perlmod, cmdkdb, bos530 4/26/01 08:29:02
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Dump.perlmod 1.4 
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
#   FUNCTIONS: Dump CLASS
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


			package Dump;


################################################################



require Comm;			### This class inherits from the Comm class
@ISA = qw( Comm );

use init qw( $Dbg $ErrFound );            ### Import $Dbg


#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = (			### Cache for exposed attributes

        stat => undef,
        dumpinfo => undef,
	cur_cpu_id => undef,
	cur_cpu => undef,
);

my %dmpbuild = (
				### KDB subcommand is 'stat'

        _rawcmd => [ ['senddata','stat',''],
                     ['readdata','stat'] ],
);


########################################################################
########################################################################



########
#
# new
#
########

sub new {
        my $class = shift;
        my $self = {
                %fields,
                %dmpbuild,
        };

	$self->{dumpinfo} = shift;	### Update 'dumpinfo' attr with the argument
	$self->{dumpinfo} =~ s/\(\d+\)>\s*$//;

	bless $self, $class;            ### Attach the object to the class

	$self->rawinfo;			### Update the 'stat' attribute

        return $self;
}


### The 'cur_cpu_id' and 'cur_cpu' attributes shall not be put in cache because
### their meaning is shortlived.
### They are then not retrieved from the 'rawinfo' attribute.


##############
#
# cur_cpu_id
#
##############

### kdb manages the current CPU including it in the kdb prompt

sub cur_cpu_id {

	my $self = shift;		### First argument is always the class

	eval{ $Dbg->sendcmd('') }; 	### Pick up the kdb prompt
	if ($@) {	
		$ErrFound = $self->{_errstr} = $@;
		return 'undef';
	}
	
	$self->{cur_cpu_id} = eval{ $Dbg->readcmd };
	if ($@) {
		$ErrFound = $self->{_errstr} = $@;
		return 'undef';
	}

	$self->{cur_cpu_id} =~ s#^ .* \( (\d+) \) > \s $#$1#sx;

	return $self->{cur_cpu_id};

}
	
	

###########
#
# cur_cpu
#
###########

sub cur_cpu {

	my $self = shift;       ### First argument is always the class

	my $cpuid = $self->cur_cpu_id;

				### Was there an error detected ?
	if ( defined $cpuid ) {
		$self->{cur_cpu} = Cpu->new($cpuid);
		return $self->{cur_cpu};
	}
	else {
				### $@ has been updated by $self->cur_cpu_id
		return 'undef';
	}
}
	
### The stat and dumpinfo methods should avoid dealing with the cache
### because they are data retrieved when the Kernel debugger is launched.
### Then they should not be implicit methods. 

########
#
# stat
#
########

sub stat {

        my $self = shift;       ### First argument is always the class
        return $self->{stat};
}


############
#
# dumpinfo
#
############

sub dumpinfo {

        my $self = shift;       ### First argument is always the class
        return $self->{dumpinfo};
}

1;
