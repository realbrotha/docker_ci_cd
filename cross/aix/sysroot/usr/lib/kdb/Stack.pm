# @(#)34        1.3  src/bos/usr/lib/kdb/Stack.perlmod, cmdkdb, bos530 10/3/00 07:21:02
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Stack.perlmod 1.3 
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
#   FUNCTIONS: Stack CLASS
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


			package Stack;


################################################################


require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );

use init;		### Import default symbols


#########################################
#					#
#	CLASS ATTRIBUTES AND DEFINE	#
#					#
#########################################


my %fields = (		### Cache for exposed attributes 

	depth => undef,
	_frame => undef,	# To improve performance 
	routine => undef,
	address => undef,
	offset => undef,
	saved_registers => undef,
);

my %stbuild = (
			### KDB subcommand is 'f'

	_rawcmd => [ ['senddata','f','signature'],
		     ['readdata'] ] ,
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
		%stbuild,
	};

	if (@_) {		### the method argument will indicate the object

		$self->{signature} = shift;
	}

	bless $self, $class;	### Attach the object to the class
	return $self;
}


###########
#
# depth
#
###########    

sub depth {

        my $self = shift;	### First argument is always the class


	### Test the cache for 'depth' OR retrieve from raw data
	###	'split' used in scalar context will return 'depth'
	### 	pattern :
	###		use the string as multiple lines
	###		match is beginning of a line starting with a'['

        unless ( cached $self->{depth} ) {

		### Shunt the warning error returned by 'f' kdb subcommand
		### and process the significent part

		my ( $usable ) = split /(?= \{ \{ ERR)/x, $self->rawinfo, 2;

		$self->{depth} = ( split m# ^ (?=\[) #mx , $usable ) - 1;
        }

        return $self->{depth};
}


###########
#
# routine
#
###########  
 
sub routine {

        my $self = shift;		### First argument is always the class

        return undef unless (@_);	### an argument is expected

        my $index = shift;


	### Test the cache for routine(index) OR retrieve from raw data
	###	Use '_frame' for performance
	###	'routine' will match the pattern :
	###	word characters which could be preceded by a dot and which
	###	is preceded by ] and followed by +
 	 

        unless ( cached $self->{routine}[$index] ) {

		$self->_frame($index);

		if ( defined $self->{_frame}[$index] ) {

			$ret = $self->{_frame}[$index] =~ m# ] (\.? \w+) \+ #x;
			$self->{_frame}[$index] =~ m# ] (\w+) \(\) #x unless $ret;
			$self->{routine}[$index] = $1;
		}
		else {
			### $self->{routine}[$index] already UNDEFINED
			return undef;

		};
        }

        return $self->{routine}[$index];
}


###########
#
# address
#
###########  

sub address {

        my $self = shift;		### First argument is always the class

        return undef unless (@_);	### an argument is expected

        my $index = shift;

	### Test the cache for address(index) OR retrieve from raw data
	###     Use '_frame' for performance
	###     'address' will match the pattern :
	###     eight word characters which are inserted between [ and ] and
	###	which stand at the beginning of the string


        unless ( cached $self->{address}[$index] ) {

		$self->_frame($index);

		if ( defined $self->{_frame}[$index] ) {

			$self->{_frame}[$index] =~ m# ^ \[ (\w+) ] #x;
			$self->{address}[$index] = $1;
		}
		else {
			### $self->{address}[$index] already UNDEFINED
			return undef;

		};
        }

        return $self->{address}[$index];
}


###########
#
# offset
#
########### 

sub offset {

        my $self = shift;		### First argument is always the class

        return undef unless (@_);	### an argument is expected

        my $index = shift;

	### Test the cache for offset(index) OR retrieve from raw data
	###     Use '_frame' for performance
	###     'offset' will match the pattern :
	###     all word characters until a nonword character and preceded by 
	###	word characters (which stand for routine) and a + character


        unless ( cached $self->{offset}[$index] ) {

		$self->_frame($index);

		if ( defined $self->{_frame}[$index] ) {

			$ret = $self->{_frame}[$index] =~ m# \w+ \+ (\w+) \W #x;
			if ($ret) {
				$self->{offset}[$index] = $1;
			}
			else {
				return undef;
			}
		}
		else {
			### $self->{offset}[$index] already UNDEFINED
			return undef;

		};
        }

        return $self->{offset}[$index];
}


######################
#
# saved_registers
#
######################

sub saved_registers {

        my $self = shift;		### First argument is always the class

        return undef unless (@_);	### an argument is expected

        my $index = shift;

	### Test the cache for saved_registers(index) OR retrieve from raw data
	###     Use '_frame' for performance
	###     pattern :
        ###             use the string as a single line
        ###     'saved_registers' will match a 'r' followed by at least one 
	###	digit ( this will point the first register )
	###	and all following characters til a '=' (end of registers) 

        unless ( cached $self->{saved_registers}[$index] ) {

		$self->_frame($index);

		if ( defined $self->{_frame}[$index] ) {

			$self->{_frame}[$index] =~ m# \) \n \s+ (r \d+ [^=]+) #sx;
			$self->{saved_registers}[$index] = $1;
		}
		else {
			### $self->{saved_registers}[$index] already UNDEFINED
			return undef;

		};
        }

        return $self->{saved_registers}[$index];
}


############
#
# _frame
#
############

sub _frame {

	my $self = shift;		### First argument is always the class

        return undef unless (@_);	### an argument is expected

        my $index = shift;

	### Test the cache for _frame(index) OR retrieve from raw data
	###     'split' used in list context will fill in the cache
	###     pattern :
	###             use the string as multiple lines
	###             match is beginning of a line starting with a'['

	### At first call take the opportunity to update the cache array
	
	if ( $index >= $self->depth ) {
		$ErrFound = $self->{_errstr} = 'Bad index';
		return undef;
	}

	unless ( cached $self->{_frame}[$index] ) {

		### Shunt the warning error returned by 'f' kdb subcommand
		### and process the significent part

		my ( $usable ) = split /(?= \{ \{ ERR)/x, $self->rawinfo, 2;

		my ( $trash, $first ) = split m# ^ (?=\[) #mx , $usable, 2;

		@{$self->{_frame}} = split m# ^ (?=\[) #mx , $first;
	}

	return $self->{_frame}[$index];
}	

1;






