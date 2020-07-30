# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Segment.perlmod 1.2 
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


			package Segment;


################################################################


require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );


#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = (		### Cache for exposed attributes

	id => undef,
	type => undef,
	inuse => undef,
	pagingdevice => undef,
);

my %sgbuild = (
			### KDB subcommand is 'scb 2 segment id'

        _rawcmd => [ ['senddata','scb 2','signature'],
		     ['readdata'] ],

			### 'id' is the set of word characters following the keyword 'Segment ID'

	_raw_id => [ 'pattern2val', 'Segment ID\W+(\w+)\W+' ],

			### 'type' is the string of characters preceding the keyword 'SEGMENT'

	_raw_type => [ 'pattern2val', '([^\n]+)\s+SEGMENT' ],

			### the 'index in pdt' indicates the PagingDevice object to be created

	_raw_pagingdevice => [ 'pattern2obj','index in pdt\W+\w+\W+(\w+)\W+','PagingDevice' ],

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
		%sgbuild,
	};

	return undef unless (@_);	### an argument is expected

	$self->{signature} = shift;

	bless $self, $class;		### Attach the object to the class
	return $self;
}



########
#
# inuse
#
########


sub inuse {

	my $self = shift;		### First argument is always the class

	if ( $self->{id} ne '007FFFFF' ) {
		return 1;
	}
	else {
		return 0;
	}
}


1;

