# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/WaitTable.perlmod 1.1 
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

################################################################


			package WaitTable;


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

my %thtbuild = (
			### KDB subcommand is 'th -w' 

	_rawcmd => [ ['senddata','th -w','signature'],
		      ['readdata'] ],

			### Table elements are Thread instances
	_type => 'Thread',
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
		%thtbuild,
	};

	return undef unless (@_);       ### at least one argument expected

	$self->{signature} = shift;

	bless $self, $class;	### Attach the object to the class
	return $self;
}

1;
