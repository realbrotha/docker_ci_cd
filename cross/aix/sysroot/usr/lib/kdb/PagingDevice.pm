# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/PagingDevice.perlmod 1.1 
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


			package PagingDevice;


################################################################


require Comm;		### This class inherits from the Comm class
@ISA = qw( Comm );


#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = (		### Cache for exposed attributes

	type => undef,
	strategy => undef,
	devmajor => undef,
	devminor => undef,
	unfinishedio => undef,
);

my %pgbuild = (
			### KDB subcommand is 'pdt index'

        _rawcmd => [ ['senddata','pdt','signature'],
		     ['readdata'] ],

			### 'type' is the set of word characters following the 
			### keywords sequence 'PDT address','entry','of','type' 
	_raw_type => [ 'pattern2val', 'PDT address\W+\w+\W+entry\W+\w+\W+of\W+\w+\W+type\W+(\w+)\W+' ],

			### 'strategy' is retrieved from the pattern 'dev_t or strategy ptr'

	_raw_strategy => [ 'pattern2val', 'dev_t or strategy ptr\W+\w+\W+(\w+)\W+' ],

			### 'unfinishedio' is retrieved from the pattern 'i/o's not finished'

	_raw_unfinishedio => [ 'pattern2val','i/o\'s not finished\W+\w+\W+(\w+)\W+' ],

			### Masks in Kernel for major an minor

			### 	_64_majormask => '00FFFFFF00000000',
			###	_64_minormask => '00000000FFFFFFFF',
			###	_32_majormask => '0FFF0000',
			###	_32_minormask => '0000FFFF',
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
		%pgbuild,
	};

	return undef unless (@_);	### an argument is expected

	$self->{signature} = shift;

	bless $self, $class;		### Attach the object to the class
	return $self;
}



############
#
# devmajor
#
############


sub devmajor {

	my $self = shift;		### First argument is always the class

	### major and minor are meaningless if type in (REMOTE,SERVER,FREE)

	if ( $self->type eq 'REMOTE' or 
			$self->type eq 'SERVER' or $self->type eq 'FREE' ) {
		return undef;
	}

	### apply a mask on 'strategy'
	### if uppest byte is 8 : 'strategy' is 64-bits long and the two uppest
	### bytes are reserved
	### if not : 'strategy' is 32-bits long and major is the upper part

	if ( ord($self->strategy) == 56 ) {	### 64-bits long
		return ( substr $self->{strategy},2,6 );
	}
	else {
		return ( substr $self->{strategy},1,3 );
	}
}


############
#
# devminor
#
############


sub devminor {

	my $self = shift;		### First argument is always the class

	### major and minor are meaningless if type in (REMOTE,SERVER,FREE)

	if ( $self->type eq 'REMOTE' or 
			$self->type eq 'SERVER' or $self->type eq 'FREE' ) {
		return undef;
	}

	### apply a mask on 'strategy'
	### if uppest byte is 8 : 'strategy' is 64-bits long 
	### if not : 'strategy' is 32-bits long and minor is the lower part

	if ( ord($self->strategy) == 56 ) {     ### 64-bits long
		return ( substr $self->{strategy},8 );
	}
	else {
		return ( substr $self->{strategy},4 );
	}
}

1;

