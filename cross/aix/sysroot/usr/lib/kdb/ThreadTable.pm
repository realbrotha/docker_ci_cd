# @(#)31        1.2  src/bos/usr/lib/kdb/ThreadTable.perlmod, cmdkdb, bos530 2/29/00 09:55:46
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/ThreadTable.perlmod 1.2 
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
#   FUNCTIONS: ThreadTable CLASS
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


			package ThreadTable;


################################################################


require Table;		### This class inherits from the Table class which
			### itself inherits from the Comm class
@ISA = qw( Table );

require WaitTable;

#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = ();	### Just the inherited attributes are exposed

my %thtbuild = (
			### KDB subcommand is 'th *' 

	_rawcmd => [ ['senddata','th *'],
		     ['readdata'] ],

			### OR 'tpid' process number

	_rawcmd1 => [ ['senddata','tpid','signature'],
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

	### If argument it is assumed to be a Process and will indicate the object
	### Then replace _rawcmd with _rawcmd1 to be managed by rawinfo().

	if (@_)	{

		$self->{signature} = shift;
		$self->{_rawcmd} = $self->{_rawcmd1};
	}

	bless $self, $class;	### Attach the object to the class
	return $self;
}




###########
#
# running
#
###########

### Displays a short report of threads which 'STATE' is RUN.


sub running {

	my $self = shift;               ### First argument is always the class

	### Table display is always header followed by an empty line
	### Initialize $workstr with the header

	$self->rawinfo;
	return undef if ( defined $self->{_errstr} );

	my ($ahead,$data) = split m# ^(?=.*\w+\+\w+)#mx, $self->{rawinfo},2;

	my ($trash,$workstr) = split m# \n*(?=[^\n]+\n{2}$) #sx, $ahead, 2;

	my @lines = split m# ^ (?=\w) #mx , $data;

	for ($index = 0; $index < $#lines; $index += 1) {

		my $thstate = $self->tabfield2val($index, 'STATE');

		if ( $thstate eq 'RUN' ) {
			$workstr = join '', $workstr, $lines[$index];
		}
	}

	return $workstr;

}




###########
#
# pageins
#
###########

### Displays a short report of threads which 'STATE' is WPGIN.


sub pageins {

	my $self = shift;               ### First argument is always the class

	return WaitTable->new('WPGIN')->rawinfo;
}

1;








