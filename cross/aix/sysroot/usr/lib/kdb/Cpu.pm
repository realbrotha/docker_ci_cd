# @(#)44        1.1  src/bos/usr/lib/kdb/Cpu.perlmod, cmdkdb, bos530 9/16/99 10:19:44
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Cpu.perlmod 1.1 
#  
# Licensed Materials - Property of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 1999 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
#
#   COMPONENT_NAME: kdb
#
#   FUNCTIONS: Cpu CLASS
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


			package Cpu;


################################################################


require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );


#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = (		### Cache for exposed attributes

	cur_thread => undef,
	mst_table => undef,
	ppda => undef,
);

my %pdabuild = (
			### KDB subcommand is 'ppda'

	_rawcmd => [ [ 'senddata','ppda','signature' ],
		     [ 'readdata' ] ] ,

			### the set of word characters following curthread
			### indicates the Thread to be created

	_raw_cur_thread => [ 'pattern2obj','curthread\W+(\w+)\W+','Thread'] ,

			### CPU number indicates Ppda

	_raw_ppda => [ 'arg2obj','signature','Ppda' ],

			### CPU number indicates the MstTable to be created

	_raw_mst_table => [ 'arg2obj','signature','MstTable' ],
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
		%pdabuild,
	};

	if (@_) {	### the method argument will indicate the object

		$self->{signature} = shift;
	}

	bless $self, $class;	### Attach the object to the class
	return $self;
}


1;








