# @(#)37        1.1  src/bos/usr/lib/kdb/Ppda.perlmod, cmdkdb, bos530 9/16/99 10:14:41
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Ppda.perlmod 1.1 
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
#   FUNCTIONS: Ppda CLASS
#
#   ORIGINS: 83
#
#
#   (C) COPYRIGHT International Business Machines Corp. 1999
#   All Rights Reserved
#   Licensed Materials - Property of IBM
#   US Government Users Restricted Rights - Use, duplication or
#   

################################################################


			package Ppda;


################################################################


require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );


#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = ();	### Just the inherited attributes are exposed

my %pdabuild = (
			### KDB subcommand is 'ppda'

	_rawcmd => [ ['senddata','ppda','signature'],
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
		%pdabuild,
	};

	if (@_) {		### the method argument will indicate the object

		$self->{signature} = shift;
	}

	bless $self, $class;	### Attach the object to the class
	return $self;
}


1;








