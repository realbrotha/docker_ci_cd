# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Registers.perlmod 1.3 
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
################################################################


			package Registers;


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

	reg => undef,
	iar => undef,
	lr => undef,
	msr => undef,
	cr => undef,
);

my %rgbuild = (
			### KDB subcommand switches to the thread and requires
			### to display the specific registers

        _rawcmd => [ ['senddata','sw','signature'],
		     ['senddata','dr gp; dr iar; dr lr; dr msr; dr cr'],
		     ['readdata'] ],

			### 'iar' is the value following the pattern 'iar'

	_raw_iar => [ 'pattern2val', 'iar\W*:\W*(\w+)\W+' ],

			### 'lr' is the value following the pattern 'lr'

	_raw_lr => [ 'pattern2val', 'lr\W*:\W*(\w+)\W+' ],

			### 'msr' is the value following the pattern 'msr'

        _raw_msr => [ 'pattern2val', 'msr\W*:\W*(\w+)\W+' ],

			### 'cr' is the value following the pattern 'cr'

        _raw_cr => [ 'pattern2val', 'cr\W*:\W*(\w+)\W+' ],


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
		%rgbuild,
	};

	return undef unless (@_);	### an argument is expected

	$self->{signature} = shift;

	bless $self, $class;		### Attach the object to the class
	return $self;
}



########
#
# reg
#
########

### Returns the value of the indexed General Purpose Register. 

sub reg {

	my $self = shift;		### First argument is always the class

	return undef unless (@_);	### an argument is expected

	my $index = shift;

	### General Purpose Registers are indexed up to 31

	if ( $index > 31 ) {
		$ErrFound = $self->{_errstr} = 'Bad index';
		return undef;
	}

	unless ( cached $self->{reg}[$index] ) {	

		$self->rawinfo;

		unless ( defined $self->{_errstr} ) {
			$self->rawinfo =~ /r$index\W+(\w+)\W+/;

			$self->{reg}[$index] = $1;
		}
	}

	return $self->{reg}[$index];
}


1;

