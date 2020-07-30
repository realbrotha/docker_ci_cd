# @(#)45        1.6  src/bos/usr/lib/kdb/Comm.perlmod, cmdkdb, bos530 12/12/00 08:06:56
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Comm.perlmod 1.6 
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
#   FUNCTIONS: Comm CLASS
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


			package Comm;


################################################################


use Carp;
use init;			### Import default symbols
use integer;


#########################################
#
#       CLASS ATTRIBUTES AND DEFINE     
#
#########################################


my %comfields = (		### Cache for exposed attributes

	rawinfo => undef,       
	_errstr => undef,
	signature => undef,
);


########################################################################
########################################################################



############
#
# AUTOLOAD
#
############

### Generic method to retrieve object attributes
### Supply the class for a _raw_xxx attribute is REQUIRED


sub AUTOLOAD {

	my $self = shift;		### First argument is always the class

					### Check for a proper reference

	my $type = ref($self) || croak "$self is not an object";
	my $name = $AUTOLOAD;

	$name =~ s/.*://;		### Strip fully-qualified portion


					### Check for the attribute in the class

	exists $self->{$name} or 
		croak "Can't access `$name' attribute in object of class $type";

					### Check it is an external attribute 

	$name =~ /^_.*/ and 
		croak "`$name' not an external attribute in object of class $type";

					### Test the cache for the required 
					### attribute OR retrieve from raw data

	unless ( cached $self->{$name} ) {

		$self->rawinfo;
		$self->{$name} = $self->infofilter($name) unless $self->{_errstr};
	}
	
	return $self->{$name};
}


##############
#
# infofilter
#
##############

### Parse _raw_xxx attribute and call the right filter with the right arguments


sub infofilter {

	my $self = shift;		### First argument is always the class

	my $name = join '','_raw_',shift;	### Which _raw_xxx to be used ?

	my $filter = $self->{$name}[0];		### Which filter to be called ?
	my $pattern = $self->{$name}[1];	### Which arguments to supply for
	my $newobj = $self->{$name}[2];

	return $self->$filter( $pattern, $newobj);	### Call the filter

}

##############
#
# pattern2obj
#
##############

### Create a class object using a pattern
### The matching pattern supplies for the value which will indicate the object.


sub pattern2obj {

	my $self = shift;		### First argument is always the class

	my $pattern = shift;		### pattern to be used ?

	my $result = $self->{rawinfo} =~ /$pattern/s;

	return undef unless ($result);

	my $create = shift;		### Which class object to be created ?


	return ($create)->new($1);	### with the backreference of the match

}


##############
#
# pattern2val
#
##############

### Return a value using a pattern


sub pattern2val {

	my $self = shift;		### First argument is always the class

        my $pattern = shift;		### pattern to be used ?
        $self->{rawinfo} =~ /$pattern/s;


	return $1;			### Backreference of the match
	
}


################
#
# tabfield2val
#
################

### Return a value using a field in a table
### This filter is used to retrieve values of attributes which are displayed 
### by the kdb command as a table format
### Note this only concerns the first line of data


sub tabfield2val {

        my $self = shift;               ### First argument is always the class
	my $field = shift;		### Field name to be retrieved

	my ($ahead,$data) = split m# ^(?=.*\w+\s*\+\s*\w+)#mx, $self->{rawinfo},2;
	($data) = split m# (?=\n) #mx, $data, 2;

	my ($trash,$header) = split m# \n*(?=[^\n]+\n{2}$) #sx, $ahead, 2;

	my $sign = $self->_searchfield( $field, $header, $data );

 
	return $sign;

}


################
#
# tabfield2obj
#
################

### Create a class object using a field in a table
### This filter is used to retrieve values of attributes which are displayed
### by the kdb command as a table format
### Note this only concerns the first line of data


sub tabfield2obj {

	my $self = shift;               ### First argument is always the class
	my $field = shift;              ### Field name to be retrieved
	my $create = shift;             ### Which class object to be created ?

	my ($ahead,$data) = split m# ^(?=.*\w+\s*\+\s*\w+)#mx, $self->{rawinfo},2;
	($data) = split m# (?=\n) #mx, $data, 2;

	my ($trash,$header) = split m# \n*(?=[^\n]+\n{2}$) #sx, $ahead, 2;
	
	my $sign = $self->_searchfield( $field, $header, $data );

	return ($create)->new($sign);      

}


sub _searchfield { 

	my $self = shift; 		### First argument is always the class
	my ( $field, $header, $data ) = @_;

		### Initialize a hash on header fields with corresponding index

	my %hashheader = ();
	$header =~ s# \n+ ##mx;
	my @fieldheader = split /\s+/,$header;

		### To distinguish between - say CPU and CPUID -
		### look for index with pattern 'field name\s'

	$header .= ' ';		### for the pattern to match the last field
	for ($i=0; $i <($#fieldheader + 1);$i++)
	{
        	$hashheader{$fieldheader[$i]} = index $header, (join '', $fieldheader[$i], ' ');
	}


		### Translate $data into a character array

	 my (@firstlchar) = unpack "C" x length $data,$data;

 
		### Initialization

	my $endline = $#firstlchar + 1;	### first index beyond the array
	my $fieldvalue ='';

	my $stop = $endline;		### stop index for a field
	for $i ( sort { $a <=> $b } values %hashheader ) {
		if ($i > $hashheader{$field}) {
			$stop = $i - 1;
			last;
		}
	}


	### Manage apart when the field is the last in header

	if  ($firstlchar[$hashheader{$field}] == 0xa ) {

		return $fieldvalue;
	}

	### EITHER the character in data standing at index in header is a space
	### THEN look forward to a first significent character
	### - The field could be empty and/or the last in header -
	### If not empty :
	###	look forward for a separator - that is a non-word character
	###	( so far could be '*' or '!' or '>' : then the order in which 
	###	it is looked up to exit the loop and improve performances )

	if  ($firstlchar[$hashheader{$field}] == 0x20) {

		$i = $hashheader{$field};
		do {
			$i++;
		} while ( $firstlchar[$i] == 0x20 && $i < $stop );

		my $deb = $i;		### index of first character of value

		while ( $firstlchar[$i] != 0x20
		     && $firstlchar[$i] != 0x2a
		     && $firstlchar[$i] != 0x21
		     && $firstlchar[$i] != 0x3e
		     && $i < $endline) {
			$i++
		};
		
		for ($k = $deb; $k < $i; $k++) {
			$fieldvalue = join '',$fieldvalue,chr $firstlchar[$k];
		}

	}

	else {

	### OR it is not a space ( and thus part of the field value ) THEN
	### Look backwards for a separator - that is a non-word character -
	### - sure to be found and cannot be beginning of a line -
	### Then look forward for subsequent characters til a separator

		$i = $hashheader{$field};
		do {
			$i--
		} while ( $firstlchar[$i] != 0x20
		       && $firstlchar[$i] != 0x2a
		       && $firstlchar[$i] != 0x21
		       && $firstlchar[$i] != 0x3e
			);


		$i += 1;
		my $deb = $i;


		do {
			$i++
		} while ( $firstlchar[$i] != 0x20
		       && $firstlchar[$i] != 0x2a
		       && $firstlchar[$i] != 0x21
		       && $firstlchar[$i] != 0x3e
		       && $i < $endline
			);



		for ($k = $deb; $k < $i; $k++) {
			$fieldvalue = join '',$fieldvalue,chr $firstlchar[$k];
		}
	}

	return $fieldvalue;

}

###########
#
# arg2obj
#
###########

### Create a class object using an attribute value
### The attribute value supplies for the value which will indicate the object.


sub arg2obj {

	my $self = shift;		### First argument is always the class

        my $clonattr = shift;		### Which attribute ?

	$create = shift;		### Which class object to be created ?


	if ( $clonattr ne 'signature' ) {
		unless ( cached $self->{$clonattr} ) {
			eval { $self->$clonattr() };
			return undef if $@;
		}
	}

        return ($create)->new( $self->{$clonattr} );

}



############
#
# senddata
#
############

### Send the kdb subcommands


sub senddata {

	my $self = shift;		### First argument is always the class

	my $tabcmd = shift;		### Reference on array 

	my $cmd = $$tabcmd[0];		### kdb subcommand to be called
	my $parms = $$tabcmd[1];	### and its argument

	my $kdbcmd = join ' ', $cmd, $self->{$parms};


	eval{ $Dbg->sendcmd($kdbcmd) };		### Ask the debugger

			### $@ should have been updated - with the die argument
	if ($@) { return -1 } else { return 0 }
	
}



############
#
# readdata
#
############

### Pick up all data in the pipe 


sub readdata {

	my $self = shift;		### First argument is always the class

	my $update = shift;		### attribute to be updated
					### should generally be 'rawinfo'

	if ($$update[0]) { 		### something specified to update ?

		$self->{$$update[0]} = eval{ $Dbg->readcmd };	### Ask debugger 
	}
	else {				### default is updating 'rawinfo'
		$self->{rawinfo} = eval{ $Dbg->readcmd }; 	### Ask debugger
	}

		### in case of error eval has set $@ and returned UNDEFINED
	if ($@) { return -1 } else { return 0 }
}



############
#
# flushdata
#
############

### Garbage all data in the pipe waiting for being picked up


sub flushdata {

        my $self = shift;		### First argument is always the class

	eval{ $Dbg->readcmd };		### Ask the debugger
	
			### $@ should have been updated - with the die argument
	if ($@) { return -1 } else { return 0 }
}



############
#
# rawinfo
#
############

### Retrieve the rawinfo attribute 


sub rawinfo {

	my $self = shift;	### First argument is always the class

				### Check the cache or get info from KDB

	unless ( cached $self->{rawinfo} ) {

		$ret = $self->_dbggetinfo;
	
		if ($ret) {	### Communication error with KDB

			### $self->{rawinfo} already UNDEFINED
			### $@ updated by eval

			$ErrFound = $self->{_errstr} = $@;	
		}
		else {		### Update error detected by KDB

			( $garbage, $self->{_errstr} ) = split /\{ \{ ERR/x, $self->{rawinfo}, 2;	

			$self->{_errstr} =~ s#({{ERR\s*|ERR}}\s*)##g;
			$ErrFound = $self->{_errstr};

			### Not a communication error then leave 'rawinfo' as is
			### that will avoid calling again if error badly managed
			### at the script level 
			### BUT the script SHALL call errorfound().
		}
	};

	return $self->{rawinfo};
}



#################
#
# _dbggetinfo
#
#################

### rawinfo is assumed to be defined - error checking is done by rawinfo
### This method should not be called directly anyway...


sub _dbggetinfo {
        
        my $self = shift;		### First argument is always the class

	### Execute the exchanges with KDB ordered by the _rawcmd attribute
	### _rawcmd looks like an array of exchanges
	### each exchange is itself an array, fitting :
	###	a flow routine
	###	a KDB subcommand
	###	the arguments of the KDB subcommands

	
	for ($i=0 ; $i<($#{$self->{_rawcmd}}+1) ; $i++) {

		my $flow = $self->{_rawcmd}[$i]->[0];

		@cmd = ( $self->{_rawcmd}[$i]->[1],
			 $self->{_rawcmd}[$i]->[2]
		);

		$ret = $self->$flow(\@cmd);


				### If flow control on error, stop processing
		last if $ret;
	}

	return $ret;
}


#################
#
# errorfound
#
#################

sub errorfound {

	my $self = shift;		### First argument is always the class

	return $self->{_errstr};
}

sub DESTROY {

	### To prevent from the 'eval' error : DESTROY not found
}




##############
#
# unimport
#
##############


### Unload the package

sub unimport {

	my $class = shift;

	for $key (keys %{"main::".$class."::"}) {
		delete ${"main::".$class."::"}{$key};
	}

        for $key (keys %INC) {
                if ( $key =~ /^$class\W+/ ) {
                        delete $INC{$key};
                }
        }

        for $key (keys %main::) {
                if ( $main::{$key} =~ /\W+$class\W+/ ) {
                        delete $main::{$key};
                }
        }
}


1;


