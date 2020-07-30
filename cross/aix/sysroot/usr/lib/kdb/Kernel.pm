# @(#)41        1.2  src/bos/usr/lib/kdb/Kernel.perlmod, cmdkdb, bos530 3/15/00 06:21:19
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/Kernel.perlmod 1.2 
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
#   FUNCTIONS: Kernel CLASS
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


			package Kernel;


################################################################



#########################################
#                                       #
#       CLASS ATTRIBUTES AND DEFINE     #
#                                       #
#########################################


my %fields = (		### Cache for exposed attributes

        thread_table => undef,
        proc_table => undef,
        cpu_table => undef,
	seg_table => undef,
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
        };

        bless $self, $class;	### Attach the object to the class
        return $self;
}


################
#
# thread_table
#
################

sub thread_table {
	return ThreadTable->new;
}


################
#
# proc_table
#
################

sub proc_table {
	return ProcTable->new;
}	


################
#
# cpu_table
#
################

sub cpu_table {
        return CpuTable->new;
}
		
################
#
# seg_table
#
################

sub seg_table {
        return SegmentTable->new;
}

1;
