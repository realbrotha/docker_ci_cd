# @(#)35        1.1  src/bos/usr/lib/kdb/Process.perlmod, cmdkdb, bos530 9/16/99 10:13:29
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Process.perlmod 1.1 
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
#   FUNCTIONS: Process CLASS
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


			package Process;


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
	slot => undef,
	nb_thread => undef,
	primary_thread => undef,
	thread_table => undef,
	user_area => undef,
);

my %procbuild = (
			### KDB subcommand is 'p'

	_rawcmd => [ ['senddata','p','signature'],
		     ['readdata'] ] ,

			### 'id' retrieved by PID in TABLE 

	_raw_id => [ 'tabfield2val', 'PID' ],

			### 'slot' retrieved by SLOT in TABLE

	_raw_slot => [ 'tabfield2val', 'SLOT' ],

			### 'nb_thread' is the set of word characters following
			### the search of the keywords 'THREAD' and 'threadcount'
			### whatever other data between

	_raw_nb_thread => [ 'pattern2val', 'THREAD\W+.*\W+threadcount\W+(\w+)\W+' ],

			### the set of word characters following the search of 
			### the keywords 'THREAD' and 'threadlist' whatever other
			### data between indicates the Thread object to be created 
	_raw_primary_thread => [ 'pattern2obj', 'THREAD\W+.*\W+threadlist\W+(\w+)\W+' , 'Thread' ],

			### PID in TABLE indicates the ThreadTable object to be
			### created

	_raw_thread_table => [ 'tabfield2obj', 'PID', 'ThreadTable' ],

			### the set of word characters following the search of
			### keywords 'THREAD' and 'threadlist' whatever other data
			### between indicates the UserArea object to be created

	_raw_user_area => [ 'pattern2obj', 'THREAD\W+.*\W+threadlist\W+(\w+)\W+' , 'UserArea' ]

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
		%procbuild,
	};

	if (@_) {		### the method argument will indicate the object

		$self->{signature} = shift;
	}

	bless $self, $class;	### Attach the object to the class
	return $self;
}


1;








