# @(#)33        1.4  src/bos/usr/lib/kdb/Table.perlmod, cmdkdb, bos530 10/3/00 07:35:01
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Table.perlmod 1.4 
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
#   FUNCTIONS: Table CLASS
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


			package Table;


################################################################



require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );

use init;		### Import default symbols


#################################
#                               #
#       CLASS ATTRIBUTES 	#
#                               #
#################################


my %fields = (		### Cache for exposed attributes

	count => undef,
	element => undef,
);


########################################################################
########################################################################


##########
#
# count
#
##########

sub count {
        my $self = shift;	### First argument is always the class


	### Test the cache for 'count' OR retrieve from raw data
	###	'split' used in list context will return the splitted list
	###	pattern :
	###             use the string as multiple lines
	###		match the beginning of a line with contains the pattern
	###		(string characters + offset)

	### First element of 'split' is the header
	### $#array stands for the array size minus 1

	unless ( cached $self->{count} ) {

		$self->rawinfo;

		unless ( defined $self->{_errstr} ) {
			@lines = split m# ^(?=.*\w+\s*\+\s*\w+) #mx, $self->{rawinfo};
                	$self->{count} = $#lines;

		};
	}

	return $self->{count};
}


############
#
# element
#
############

sub element {
	my $self = shift;		### First argument is always the class

	return undef unless (@_);	### an argument is expected
	
	my $index = shift;	


	### Test the cache for element(index) OR retrieve from raw data
	### 	'split' used in list context will return the splitted list
	### 	pattern :
	###		use the string as multiple lines
	###		the match is beginning of a line with contains the 
	###		pattern (string characters + offset)


	### First element of 'split' is the header
	### $#array stands for the array size minus 1

	### The 'signature' of the 'element' to be created is retrieved in table
	### as EITHER the first field after the address
	### 	pattern :
	###		address is displayed as string+offset
	###		the match is the set of digits which follows (ex.SLOT)
	### OR the first field, which preceeds the address ( future extensions )
	###	pattern :
	###		address is displayed as string+offset
	###		the match is the set of digits ahead

	if ( $index >= $self->count ) {
		$ErrFound = $self->{_errstr} = 'Bad index';
		return undef;
	}
	
	unless ( cached $self->{element}[$index] ) {

		$self->rawinfo;

		unless ( defined $self->{_errstr} ) {

			@lines = split m# ^(?=.*\w+\s*\+\s*\w+) #mx, $self->{rawinfo},$index + 2;
			my $rep = $lines[$index + 1] =~ m# ^\w+\s*\+\s*\w+ \s+ (\d+) #x;
			$lines[$index + 1] =~ m# ^ \s* (\d+) \s+ #x unless $rep;
	
			$self->{element}[$index] = $self->{_type}->new($1);

		};
	};

	return $self->{element}[$index];
}
		
		
###############
#
# tabfield2val
#
###############

### This method overwrites the tabfield2val() method of the Comm class
### which is used to retrieve fields on an element report.
### The enhancement is to be usable on the table report itself and allows to
### specify which element it has to be applied on.

sub tabfield2val {

	my $self = shift;               ### First argument is always the class
	my $index = shift;		### 'index' in Table 
	my $field = shift;              ### Field name to be retrieved

	### count() will call rawinfo() anyway

	if ( $index >= $self->count ) {
		$ErrFound = $self->{_errstr} = 'Bad index';
		return undef;
	}

	### Save the data - starting at the pattern - apart 
        ###     'split' used in list context will return the splitted list
        ###     pattern :
        ###             use the string as multiple lines
        ###             match a beginning of line with contains the pattern
        ###             (string characters + offset)

	my ($ahead,$data) = split m# ^(?=.*\w+\s*\+\s*\w+) #mx, $self->{rawinfo},2;

	### Save the header apart
	### Table display is always header followed by an empty line

	my ($trash,$header) = split m# \n*(?=[^\n]+\n{2}$) #sx, $ahead, 2;
	
	### Get the element 

	my @lines = split m# ^(?=.*\w+\s*\+\s*\w+) #mx , $data, $index + 2;


	my $value = $self->_searchfield( $field, $header, $lines[$index] );

	return $value;


}
	

1;








