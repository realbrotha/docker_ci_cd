# @(#)43        1.2  src/bos/usr/lib/kdb/CpuTable.perlmod, cmdkdb, bos530 2/29/00 09:22:15
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/CpuTable.perlmod 1.2 
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
#   FUNCTIONS: CpuTable CLASS
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


			package CpuTable;


################################################################


require Table;		### This class inherits from the Table class which
			### itself inherits from the Comm class
@ISA = qw( Table );


#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = ();	### Just the inherited attributes are exposed

my %cput_build = (
			### KDB subcommand is 'ppda *'

	_rawcmd => [ ['senddata','ppda *'],
		     ['readdata'] ],

			### Table elements are Cpu instances
	_type => 'Cpu',
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
		%cput_build,
	};

			# None argument required BUT if (@_)...ignore the error!

	bless $self, $class;	### Attach the object to the class
	return $self;
}

1;








