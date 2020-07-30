# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/ascl_getthreadfromcpu.perlmod 1.1 
#  
# Licensed Materials - Property of IBM 
#  
# Restricted Materials of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 2001 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
sub getthreadfromcpu {
	my $cpu = $_[0];
	my $thread = $ct->element($cpu)->cur_thread;
	if (not defined $thread->id) {
		#  Attempting to re-access thread by slot
		( $thread->rawinfo =~ /thread.\w+\s*(\d+)/ ) && (my $curthreadslot = $1);
		my $i;
		for ($i = 0; $i < $tt->count; $i++) {
			if ((defined $tt->element($i)) && ($tt->element($i)->slot == $curthreadslot)) {
				$thread = $tt->element($i);
				last;
			}
		}
	}
	return $thread;
}
1;
