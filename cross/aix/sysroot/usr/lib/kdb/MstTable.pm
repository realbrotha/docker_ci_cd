# @(#)38        1.5  src/bos/usr/lib/kdb/MstTable.perlmod, cmdkdb, bos530 10/3/00 06:44:10
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/MstTable.perlmod 1.5 
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
#   FUNCTIONS: MstTable CLASS
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


			package MstTable;


################################################################


require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );

use init;		### Import default symbols


#################################
#                               #
#       CLASS ATTRIBUTES        #
#                               #
#################################


my %fields = (		 ### Cache for exposed attributes

	count => undef,
	element => undef,
);

my %msttbuild = (
			### KDB subcommand is 'cpu number;mst;f'

	_rawcmd => [ ['senddata','cpu','signature'],
		     ['flushdata'],
		     ['senddata','mst'],
		     ['senddata','f'],
		     ['readdata'] ] ,
);
	
########################################################################
########################################################################


##########
#
# new
#
##########

sub new {
	my $class = shift;
	my $self = {
		%fields,
		%msttbuild,
	};
	if (@_) {		### the method argument will indicate the object

		$self->{signature} = shift;
	}
	bless $self, $class;	### Attach the object to the class
	return $self;
}


##########
#
# count
#
##########

sub count {
        my $self = shift;	### First argument is always the class


	### Test the cache for 'count' OR retrieve from raw data
	###     'split' used in scalar context will return 'count'
	###     pattern :
	###             use the string as multiple lines
	###             match '{{MST' at beginning of a line 
	### Forget the first element of 'split' 


        unless ( cached $self->{count} ) {

		### Shunt the warning error returned by 'f' kdb subcommand
		### and process the significent part

		my ( $usable ) = split /(?= \{ \{ ERR)/x, $self->rawinfo, 2;

		$self->{count} = split /^\{ \{ MST /mx , $usable;
		$self->{count} -= 1;
        };

        return $self->{count};
}


############
#
# element
#
############

sub element {
        my $self = shift;	### First argument is always the class

        return undef unless (@_);	### an argument is expected

        my $index = shift;


	### Test the cache for element(index) OR retrieve from raw data
	###     'split' used in list context will return the splitted list
	###     pattern :
	###             use the string as multiple lines
	###             match '{{MST' at beginning of a line
	
	### Take the opportunity to update 'count' for performance
	### Forget the first element of 'split' and note $#array stands for the 
	### array size minus 1

	### Create the Mst object with no 'signature' but update 'rawinfo' to 
	### prevent from a subsequent call to the Kernel debugger

	### 'MST}}' delimits significent data to update 'rawinfo'

	if ( $index >= $self->count ) {
		$ErrFound = $self->{_errstr} = 'Bad index';
		return undef;
	}

        unless ( cached $self->{element}[$index] ) {

		### Shunt the warning error returned by 'f' kdb subcommand
		### and process the significent part

		my ( $usable ) = split /(?= \{ \{ ERR)/x, $self->rawinfo, 2;

		@lines = split /^\{ \{ MST /mx , $usable;

		$self->{count} = $#lines;

		if ( $index == 0 ) {
			my $th = Thread->new($Kernel->cpu_table->tabfield2val( $self->{signature}, CURTHREAD ));
			$mstelt = Mst->new( $th->slot );
		}
		else {
			my $mstelt = Mst->new();
		}

		( $mstelt->{rawinfo} ) = split /^MST}}/m , $lines[$index + 1], 2;
		$self->{element}[$index] = $mstelt;

        };

        return $self->{element}[$index];
}


1;








