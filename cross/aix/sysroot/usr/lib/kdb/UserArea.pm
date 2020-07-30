# @(#)28        1.1  src/bos/usr/lib/kdb/UserArea.perlmod, cmdkdb, bos530 9/16/99 09:38:20
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/UserArea.perlmod 1.1 
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
#   FUNCTIONS: UserArea CLASS
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


			package UserArea;


################################################################


require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );


#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = ();	### Just the inherited attributes are exposed

my %uareabuild = (
			### KDB subcommand is 'u'

	_rawcmd => [ ['senddata','u','signature'],
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
		%uareabuild,
	};

	if (@_) {		### the method argument will indicate the object

		$self->{signature} = shift;
	}

	bless $self, $class;	### Attach the object to the class
	return $self;
}


1;








