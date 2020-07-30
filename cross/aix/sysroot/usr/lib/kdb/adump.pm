# @(#)48        1.1  src/bos/usr/lib/kdb/adump.perlmod, cmdkdb, bos530 9/16/99 10:42:55
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/adump.perlmod 1.1 
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
#   FUNCTIONS: AUTOMATED DUMP default script
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

print "+------------------------+\n";
print "|**   MACHINE STATUS   **|\n" ; 
print "+------------------------+\n\n";
print $Dump->stat;			# Print result of stat sub-command 
die $Dump->errorfound if $Dump->errorfound;

print "\n\n";
print "+------------------------+\n";
print "|** CURRENT CPU NUMBER **|\n" ; 
print "+------------------------+\n\n";
print $Dump->cur_cpu_id;		# Print current CPU number 
die $Dump->errorfound if $Dump->errorfound;

$tt = $Kernel->thread_table;		# Get a ThreadTable object 

print "\n\n";
print "+------------------------+\n";
print "|**    THREAD TABLE    **|\n" ; 
print "+------------------------+\n\n";
print $tt->rawinfo;			# Print result of th * sub-command
if ($tt->errorfound) {
	warn $tt->errorfound;
	goto PROCTABLE;
}

for ($index = 0; $index < $tt->count; $index += 1) {
	# Loop on each thread of thread table 

	$thread =$tt->element($index);	# Get a Thread object
	if (defined $thread) {
		print "\n\n***  Thread Slot Number: ", $thread->slot;
		print "  ***\n\n";
		# Print result of th <slot> sub-command
		print $thread->rawinfo;
		if ($thread->errorfound) {
			warn $thread->errorfound;
		}
	}
}

PROCTABLE: $pt = $Kernel->proc_table;		# Get a ProcTable object

print "\n\n";
print "+------------------------+\n";
print "|**     PROC TABLE     **|\n" ; 
print "+------------------------+\n\n";
print $pt->rawinfo;			# Print result of p * sub-command

if ($pt->errorfound) {
	warn $pt->errorfound;
	goto CPUTABLE;
}

for ($index = 0; $index < $pt->count; $index += 1) {
	# Loop on each process of proc table 

	$proc = $pt->element($index);	# Get a Process object 
	if (defined $proc) {
        	print "\n\n***  Process Slot Number: ", $proc->slot;
		print "  ***\n\n";
		print $proc->rawinfo;	# Print result of p <slot> sub-command
		if ($proc->errorfound) {
			warn $proc->errorfound;
		}
	}
}

CPUTABLE: $ct = $Kernel->cpu_table;	# Get a CpuTable object 

print "\n\n";
print "+------------------------+\n";
print "|**     CPU TABLE      **|\n" ; 
print "+------------------------+\n\n";
print $ct->rawinfo; 			# Print result of ppda * sub-command

die $ct->errorfound if $ct->errorfound;

print "\n\n";
print "+------------------------+\n";
print "|**    MST PER CPU     **|\n" ; 
print "+------------------------+\n";

for ($index1 = 0; $index1 < $ct->count; $index1 += 1) {
	# Loop on each CPU of CPU table 

        print "\n***  CPU Number: $index1  ***\n";
	$mt = $ct->element($index1)->mst_table;	# Get a MstTable object 
	if (defined $mt) {
	    for ($index2 = 0; $index2 < $mt->count; $index2 += 1) {
		# Loop on each MST of a CPU 

		$mst = $mt->element($index2);	# Get a Mst object 
		if (defined $mst) {
			# Print result of mst <slot> sub-command 
			print $mst->rawinfo;
			print "\n";
		}
	    }
	}
}

print "\n\n";
print "+------------------------+\n";
print "|**    END OF DUMP     **|\n" ; 
print "+------------------------+\n";
