# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/SegmentTable.perlmod 1.3 
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


			package SegmentTable;


################################################################


### This class is just an artificial means to retrieve a Segment object from 
### its index. 

### BEWARE :
### This class will NOT inherit from the Table class because the whole table
### will never be recorded in the rawinfo attribute.
### The _rawcmd attribute is just supplied to supersede Segment class _rawcmd  
### but will never retrieve a segment table.


require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );

use init;		### Import default symbols


#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = (		### Cache for exposed attributes

	element => undef,	
	count => undef,
	_cur_seg => undef,
);

my %sgbuild = (
			### KDB subcommand is 'scb 1 index'

        _rawcmd => [ ['senddata','scb 1','signature'],
		     ['readdata','_cur_seg'] ],

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

	bless $self, $class;		### Attach the object to the class
	return $self;
}



##########
#
# count
#
##########


sub count {

	my $self = shift;               ### First argument is always the class

	### Send to KDB an overestimated index to get an error message and
	### extract the range

	unless ( cached $self->{count} ) {

		$self->{signature} = 'FFFFFFFF';

		$self->rawinfo;

		unless ( defined $self->{_errstr} ) {

			$self->{_cur_seg} =~ /Index must be >= 0 and < (\w+)\W+/;
			$self->{count} = $1;
		}
	}

	return $self->{count};
}



###########
#
# element
#
###########


sub element {

	my $self = shift;		### First argument is always the class

	return undef unless (@_);       ### an argument is expected

	my $index = shift;

	$self->{signature} = $index;

	### Check if the index is correct

	$self->rawinfo;

	( $trash, $self->{_errstr} ) = split /(?=Index must be >= 0 and <)/,
							$self->{_cur_seg}, 2;
	if ( defined $self->{_errstr} ) {
		$ErrFound = $self->{_errstr};
		return undef;
	}

	### Create the Segment element and update its rawinfo attribute

	$seg = Segment->new($index);
	
	$seg->{rawinfo} = $self->{_cur_seg};

	return $seg;
}


1;

