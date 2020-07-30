# @(#)32        1.3  src/bos/usr/lib/kdb/Thread.perlmod, cmdkdb, bos530 10/3/00 06:50:55
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Thread.perlmod 1.3 
#  
# Licensed Materials - Property of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 1999,2000 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
#
#   COMPONENT_NAME: kdb
#
#   FUNCTIONS: Thread CLASS
#
#   ORIGINS: 83
#
#
#   (C) COPYRIGHT International Business Machines Corp. 1999
#   All Rights Reserved
#   Licensed Materials - Property of IBM
#   US Government Users Restricted Rights - Use, duplication or
#   

################################################################


			package Thread;


################################################################


require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );

use init;		### Import default symbols


#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = (		### Cache for exposed attributes

	id => undef,
	slot => undef,
	process => undef,
	mst => undef,
	stack => undef,
	uthread => undef,
	cur_space => undef,
	waitseg => undef,
);

my %thbuild = (
			### KDB subcommand is 'th'

        _rawcmd => [ ['senddata','th','signature'],
		     ['readdata'] ],

			### 'id' retrieved by TID in TABLE

	_raw_id => [ 'tabfield2val', 'TID' ],

			### 'slot' retrieved by SLOT in TABLE

	_raw_slot => [ 'tabfield2val', 'SLOT' ],

			### the set of word characters following DATA.....procp
			### indicates the Process object to be created

        _raw_process => [ 'pattern2obj','DATA\W+.*\W+procp\W+(\w+)\W+','Process' ],

			### 'slot' attr indicates the Mst object to be created

	_raw_mst => [ 'arg2obj','slot','Mst' ],

			### 'slot' attr indicates the Stack object to be created

	_raw_stack => [ 'arg2obj','slot','Stack' ],

			### 'slot' attr indicates the UThread object to be created

	_raw_uthread => [ 'arg2obj','slot','UThread' ],

			### 'slot' attr indicates the AdSpace object to be created

	_raw_cur_space => [ 'arg2obj','slot','AdSpace' ],

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
		%thbuild,
	};

	if (@_) {		### the method argument will indicate the object

		$self->{signature} = shift;
	}

	bless $self, $class;	### Attach the object to the class
	return $self;
}


###########
#
# waitseg
#
###########

### Retrieve a 'SCB wait list' Segment object on which the thread is waiting 
### for pagein.

sub waitseg {

	my $self = shift;               ### First argument is always the class

	unless ( cached $self->{waitseg} ) {

		$self->rawinfo;

		return undef if ( defined $self->{_errstr} );

		### If the thread is not waiting for pagein, forget it!

		$self->{rawinfo} =~ m# WTYPE \W+ (\w+) \W+ #x;

		if ( $1 eq 'WPGIN' ) {

			### Get the VMM Wait status for the address the thread
			### is awaiting (stored in wchan2)
 
			$self->{rawinfo} =~ m# \W+ wchan2 \W+ (\w+) \W+ #x;

			$self->{waitseg} = $1;
			return undef unless ( $self->{waitseg} =~ /[^0]+/ );

			### 'waitseg' used as intermediary to ensure the Comm 
			### class interface with the kdb command 

			$self->senddata( [ 'vmwait','waitseg' ] );
			$self->readdata( [ 'waitseg' ] );

			if ( $self->{waitseg} =~ /not a VMM wait address/ ) {
				return undef;
			}

			### Retrieve the segment index

			if ( $self->{waitseg} =~ m# \W+ sidx \W+ (\w+) \W+ #x ) {
				$self->{waitseg} = $Kernel->seg_table->element($1);
			}
		}
	}

	return $self->{waitseg};
}


1;

