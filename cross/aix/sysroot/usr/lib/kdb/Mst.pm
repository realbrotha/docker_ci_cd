# @(#)39        1.2  src/bos/usr/lib/kdb/Mst.perlmod, cmdkdb, bos530 2/29/00 09:35:41
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Mst.perlmod 1.2 
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
#   FUNCTIONS: Mst CLASS
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


			package Mst;


################################################################


require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );


#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = (		### Cache for exposed attributes

	iar => undef,
	lr => undef,
	msr => undef,
	cr => undef,
	adspace => undef,
	registers => undef,
);

my %mstbuild = (
			### KDB subcommand is 'sw thread;mst'

	_rawcmd => [ ['senddata','sw','signature'],
		     ['senddata','mst'],
		     ['readdata'] ] ,

			### 'iar' is the value following the pattern 'iar' 

	_raw_iar => [ 'pattern2val', 'iar\W+(\w+)\W+' ],

			### 'lr' is the value following the pattern 'lr'

	_raw_lr => [ 'pattern2val', 'lr\W+(\w+)\W+' ],

			### 'msr' is the value following the pattern 'msr'

	_raw_msr => [ 'pattern2val', 'msr\W+(\w+)\W+' ],

			### 'cr' is the value following the pattern 'cr'

	_raw_cr => [ 'pattern2val', 'cr\W+(\w+)\W+' ],

			### 'signature' attr indicates the AdSpace object to be created 

	_raw_adspace => [ 'arg2obj','signature','AdSpace' ],

			### 'signature' attr indicates the Registers object to be created			

	_raw_registers => [ 'arg2obj','signature','Registers' ],

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
		%mstbuild,
	};

	if (@_) {		### the method argument will indicate the object

		$self->{signature} = shift;
	}

	bless $self, $class;	### Attach the object to the class
	return $self;
}

########
#
# reg
#
########

### this method is an alias of the Registers class reg(index) method 

*reg = \&Registers::reg;


1;








