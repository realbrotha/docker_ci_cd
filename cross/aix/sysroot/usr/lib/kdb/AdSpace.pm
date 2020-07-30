# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/AdSpace.perlmod 1.2 
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


			package AdSpace;


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

	segreg => undef,
);

my %adspbuild = (
			### KDB subcommand switches to the thread and requires
			### to display the specific registers

        _rawcmd => [ ['senddata','sw','signature'],
		     ['senddata','dr sr;sr64'],
		     ['readdata'] ],

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
		%adspbuild,
	};

	return undef unless (@_);	### an argument is expected

	$self->{signature} = shift;

	bless $self, $class;		### Attach the object to the class
	return $self;
}



##########
#
# segreg
#
##########

### Returns the value of the indexed Segment Register. 

sub segreg {

	my $self = shift;		### First argument is always the class

	return undef unless (@_);	### an argument is expected

	my $index = shift;

	### In 32-bits Segment Registers are indexed up to 15

	if ( $index > 15 ) {
		$ErrFound = $self->{_errstr} = 'Bad index';
		return undef;
	}

	unless ( cached $self->{segreg}[$index] ) {	

		$self->rawinfo;

		unless ( defined $self->{_errstr} ) {
			$self->rawinfo =~ /s$index\W+(\w+)\W+/;
			$self->{segreg}[$index] = $1;
		}
	}

	return $self->{segreg}[$index];
}


############
#
# seginuse
#
############

sub seginuse {

	my $self = shift;               ### First argument is always the class

	return undef unless (@_);       ### an argument is expected

	my $index = shift;

	### Provisional implementation for 32 bits

	### In 32-bits Segment Registers are indexed up to 15

	if ( $index > 15 ) {
		$ErrFound = $self->{_errstr} = 'Bad index';
		return undef;
	}

	unless ( cached $self->{segreg}[$index] ) {

		$self->rawinfo;

		unless ( defined $self->{_errstr} ) {
			$self->rawinfo =~ /s$index\W+(\w+)\W+/;
			$self->{segreg}[$index] = $1;
		}
	}

	if ( ( substr $self->{segreg}[$index], -8, 8 ) ne '007FFFFF' ) {
		return 1;
	}
	else {
		return 0;
	}
}


#######
#
# mem
#
#######


sub mem {

	my $self = shift;               ### First argument is always the class

	return undef unless (@_);       ### an argument is expected

	return $Memory->xword_view( shift );
}


1;

