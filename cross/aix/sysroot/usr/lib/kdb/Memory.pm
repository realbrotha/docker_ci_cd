# @(#)40        1.3  src/bos/usr/lib/kdb/Memory.perlmod, cmdkdb, bos530 3/15/00 11:40:33
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Memory.perlmod 1.3 
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
#   FUNCTIONS: Memory CLASS
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


			package Memory;


################################################################



require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );

use init qw( $ErrFound );	### Import


#################################
#                               #
#       CLASS ATTRIBUTES 	#
#                               #
#################################


my %fields = (		### Cache for exposed attributes

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
	my $self = {};

	bless $self, $class;    ### Attach the object to the class
	return $self;
}


###############
#
# xbyte_view
#
###############

sub xbyte_view {

        my $self = shift;		### First argument is always the class

	return undef unless (@_);       ### at least one argument expected

	my $symb = shift;               ### symb/addr
	my $count = shift;              ### [count] for KDB command

	### Get info from KDB via the interface 'senddata' and 'readdata'
	### Use 'signature' to build arguments for 'senddata'
	### Reply will be stored in 'rawinfo'

	$self->{signature} = join ' ', $symb, $count;
	my $ret = $self->senddata( [ 'd','signature' ] );
	if ($ret) {
		$ErrFound = $self->{_errstr} = $@;
		return undef;
	}
	else {
		$ret = $self->readdata( [ 'rawinfo' ] );
		if ($ret) {
			$ErrFound = $self->{_errstr} = $@;
			return undef;
		}
		else {
			( $garbage, $self->{_errstr} ) = split /\{ \{ ERR/x, $self->{rawinfo}, 2;
			$self->{_errstr} =~ s#({{ERR\s*|ERR}}\s*)##g;
			$ErrFound = $self->{_errstr};

			return undef if ( $ErrFound );
		}
	}
	
	return $self->{rawinfo};
	
}


###############
#
# xword_view
#
###############

sub xword_view {

	my $self = shift;		### First argument is always the class

	return undef unless (@_);	### at least one argument expected
	
	my $symb = shift;		### symb/addr
	my $count = shift;		### [count] for KDB command

	### Get info from KDB via the interface 'senddata' and 'readdata'
	### Use 'signature' to build arguments for 'senddata'
	### Reply will be stored in 'rawinfo'

	$self->{signature} = join ' ', $symb, $count;
	my $ret = $self->senddata( [ 'dw','signature' ] );
	if ($ret) {
		$ErrFound = $self->{_errstr} = $@;
		return undef;
	}
	else {
		$ret = $self->readdata( [ 'rawinfo' ] );
		if ($ret) {
			$ErrFound = $self->{_errstr} = $@;
			return undef;
		}
		else {
			( $garbage, $self->{_errstr} ) = split /\{ \{ ERR/x, $self->{rawinfo}, 2;
			$self->{_errstr} =~ s#({{ERR\s*|ERR}}\s*)##g;
			$ErrFound = $self->{_errstr};

			return undef if ( $ErrFound );
		}
	}

	return $self->{rawinfo};

}


		
################
#
# xdword_view
#
################

sub xdword_view {

        my $self = shift;       	### First argument is always the class

	return undef unless (@_);       ### at least one argument expected

	my $symb = shift;               ### symb/addr
	my $count = shift;              ### [count] for KDB command

	### Get info from KDB via the interface 'senddata' and 'readdata'
	### Use 'signature' to build arguments for 'senddata'
	### Reply will be stored in 'rawinfo'

	$self->{signature} = join ' ', $symb, $count;
	my $ret = $self->senddata( [ 'dd','signature' ] );
	if ($ret) {
		$ErrFound = $self->{_errstr} = $@;
		return undef;
	}
	else {
		$ret = $self->readdata( [ 'rawinfo' ] );
		if ($ret) {
			$ErrFound = $self->{_errstr} = $@;
			return undef;
		}
		else {
			( $garbage, $self->{_errstr} ) = split /\{ \{ ERR/x, $self->{rawinfo}, 2;
			$self->{_errstr} =~ s#({{ERR\s*|ERR}}\s*)##g;
			$ErrFound = $self->{_errstr};

			return undef if ( $ErrFound );
		}
	}

	return $self->{rawinfo};

}

1;








