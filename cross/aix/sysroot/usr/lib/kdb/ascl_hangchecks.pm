# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/ascl_hangchecks.perlmod 1.2 
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
#package Master;
sub hangchecks {
	#  Hangs are very complicated.  This script is attempting to do some
	#  determination of what may be hanging the machine; be it memory, paging, mbufs,
	#  code looping on cpus, or I/O.  
	#
	#  First, we should check how memory is doing.

	infoprint (1, "\n***** Memory Checks *****\n");
	my @allocated = split(" ",$Memory->xword_view(allocated, 1));
	my @thewall = split(" ",$Memory->xword_view(thewall, 1));
	infoprint (1, "Mbufs allocated  :", hex($allocated[4])," KB.\n");
	infoprint (1, "Total Mbuf memory:", hex($thewall[4]) * 1024," KB.\n");

	if($thewall[4]>0.0){
	    infoprint (1, "Mbufs allocations at ");
	    infoprint(1, sprintf ("%5.2f", (hex($allocated[4]) / (hex($thewall[4]) * 1024) * 100)) );
	    infoprint(1, "%.\n");
	    if ( (hex($allocated[4]) / (hex($thewall[4]) * 1024)) > 0.85 ) {
		infoprint (1, "\n***** Mbuf usage is very high.\n");
		infoprint (1, "Either increase thewall or investigate who is using all the mbufs.\n\n");
	    }
	}#this is to prevent division by zero
	eval{ $Dbg->sendcmd("vmker") };
	my $vmker_raw = eval{ $Dbg->readcmd };
	$vmker_raw =~ /psfreeblks\) : ([0-9,A-Z]+)/ && (my $psfreeblks = $1);
	$vmker_raw =~ /numpsblks\)  : ([0-9,A-Z]+)/ && (my $numpsblks = $1);
	infoprint (1, "Paging free : ", hex($psfreeblks)," KB.\n");
	infoprint (1, "Total Paging: ", hex($numpsblks)," KB.\n");

	infoprint (1, "Paging is ", sprintf("%4.1f", hex($psfreeblks) / hex($numpsblks) * 100));
	infoprint (1,  "% free.\n");
	if (hex($psfreeblks) / hex($numpsblks) < .05) {
 	    infoprint (1, "\n***** Paging usage is very high.\n");
	   infoprint (1, "Either increase paging, or determine what process is using too much memory.\n\n");
		#  
		#  Print out a list of all the processes, and show how much memory they are using.
		#  Perhaps create a subroutine.
		#
		return;
	}
	#
	#  KDB does not seem to have a way to show numfree!
	#  So, currently, real memory checks are out.
	#
	infoprint (1, "Real memory is uncheckable at this time, please check manually.\n");
	#  Now let's check the cpu status
	infoprint (1, "\n***** Cpu status check\n\n");
	my @cpustate;
	my $freecpu = 0;
	my %tidstoprint;
	#  Determine the state of each cpu
	for ($i = 0; $i < $ct->count; $i++) {
		my $curthread = getthreadfromcpu($i);
		if ( $curthread->stack->routine(0) =~ /disable_lock/ ) {
			#  CPU is waiting
			$cpustate[$i] = $curthread->mst->registers->reg(7);
			if ($cpustate[$i] == $curthread->id) {
			$cpustate[$i] = join(", ", $curthread->id, "L", $curthread->mst->registers->reg(7)); 
				infoprint (1, "CPU $i is deadlocked on itself.\n\n");
				printstack($curthread);
				infoprint (1, "\n");
			} else {
 				infoprint (1, "CPU $i is waiting on thread TID $cpustate[$i].\n");
			$cpustate[$i] = join(", ", $curthread->id, "U", $curthread->mst->registers->reg(7));
				printstack($curthread);
				infoprint (1, "\n");
				$tidstoprint{$curthread->mst->registers->reg(7)}++;
			} 
		} elsif ($curthread->stack->routine(0) =~ /simple_lock/ ) {
			#  CPU may be waiting; check r3 for held lock 
			$command = join(" ", "slk", $curthread->mst->registers->reg(3));
			eval{ $Dbg->sendcmd($command) };
			$slkout = eval{ $Dbg->readcmd };
			if ($slkout =~ /thread_owner\W+([0-9,A-F]+)/) {
				$cpustate[$i] = $1;
				if ($cpustate[$i] == $curthread->id) {
					$cpustate[$i] = join(", ", $curthread->id, "L", $cpustate[$i]);
					infoprint (1, "CPU $i is deadlocked on itself.\n\n");
					printstack($curthread);
					infoprint (1, "\n");
				} else {
					infoprint ("CPU $i is waiting on thread TID $cpustate[$i].\n");
					$cpustate[$i] = join(", ", $curthread->id, "U", $cpustate[$i]);
					printstack($curthread);
					infoprint (1, "\n");
					$tidstoprint{$curthread->mst->registers->reg(7)}++;
				}
			} else {
				$freecpu++;
				infoprint (1, "CPU $i seems to be running freely.\n");
				$cpustate[$i] = join(", ", $curthread->id, "F");
			}
		} else { 
			$freecpu++;
			infoprint (1, "CPU $i seems to be running freely.\n");
			$cpustate[$i] = join(", ", $curthread->id, "F");
		}
	}
	#  If all CPUs are locked, the system is hung.  Get a stack trace of each cpu and each wait TID.
	if ($freecpu == 0) {
    	   infoprint (1, "All the CPUs are waiting.  Printing stacks of all the TIDs being waited on.\n\n");
		foreach $key (keys(%tidstoprint)) {
			my $okaytoprint = 1;
			for ($i = 0; $i < $ct->count; $i++) {
			  $okaytoprint = 0 if (($cpustate[$i] =~ /^$key/) && ($cpustate[$i] =~ /, [L,U] /));
			}
			#  This is really slow and should be rewritten a little better
			if ($okaytoprint) {
				for ($i = 0; $i < $tt->count; $i++) {
					if ((defined $tt->element($i)) && ($tt->element($i)->id == $key)) {
						my $waittype;
			( $tt->element($i)->rawinfo =~ m# WTYPE \W+ (\w+) \W+ #x) && ($waittype = $1);
						infoprint (1, "TID $key is waiting on ${waittype}.\n");
						printstack ($tt->element($i));
						infoprint (1, "\n");
						last;
					}
				}
			}
		}
		return;
	} elsif ($freecpu == $ct->count) {
  	    infoprint (1, "DEBUG:  All the cpus are free.  Further hang debugging is a future feature.\n");
		
	} else {
		#  For each cpu waiting, display the stack of the thread it's waiting on, unless it was
		#  previously displayed as a waiting cpu stack.
		infoprint (1, "At least one CPU is spinning on a lock.");
		infoprint (1, "  Printing stacks for all the TIDs being waited on.\n\n");
		foreach $key (keys(%tidstoprint)) {
			my $okaytoprint = 1;
			for ($i = 0; $i < $ct->count; $i++) {
		  	  $okaytoprint = 0 if (($cpustate[$i] =~ /^$key/) && ($cpustate[$i] =~ /, [L,U] /));
			}
			if ($okaytoprint) {
				for ($i = 0; $i < $tt->count; $i++) {
					if ((defined $tt->element($i)) && ($tt->element($i)->id == $key)) {
						my $waittype;
			      ( $tt->element($i)->rawinfo =~ m# WTYPE \W+ (\w+) \W+ #x) && ($waittype = $1);
						infoprint (1, "TID $key is waiting on ${waittype}.\n");
						printstack ($tt->element($i));
						infoprint (1, "\n");
						last;
					}
				}
			}
		}
		return;
	}
	#  We've gotten this far.  Let's do a pdt *, and print out the buf info on any VG that has
	#  waiting I/O.
	$command = "pdt *";
	eval{ $Dbg->sendcmd($command) };
	my $rawpdt = eval{ $Dbg->readcmd() };
	my @pdt = split("\n", $rawpdt);
	my %vgmaj;
	foreach $pdtline (@pdt) {
		if ($pdtline =~ /^vmmd/) {
			$pdtline =~ /vmmdseg\+[0-9,A-F]+\s+(\w+)/ && (my $pdtidx = $1);
			my $pd = PagingDevice->new($pdtidx);
			if (($pd->unfinishedio != "00000000") && (defined $pd->devmajor)) {
				infoprint (1, "Device Type ", $pd->type, " has ");
				infoprint(1, hex($pd->unfinishedio), " unfinished I/Os.  Major/Minor: (");
				infoprint(1, hex($pd->devmajor), "/", hex($pd->devminor), ")\n");
				if (not defined $vgmaj{$pd->devmajor} ) {
					$command = "devsw 0x" . $pd->devmajor;
					eval{ $Dbg->sendcmd($command) };
					my $rawdevsw = eval{ $Dbg->readcmd() };
					@linesdevsw = split("\n",$rawdevsw);
					( $linesdevsw[9] =~ /\W+\w+\W+(\w+)/ ) && (my $dsd = $1);
			 	       infoprint (1, "Printing buf structures for bufs in all work queues");
					infoprint(1, " in VG Major ", hex($pd->devmajor), "\n");
					iobufsforvg($dsd);
					infoprint (1, "\n");
					$vgmaj{$pd->devmajor} = "done";
				}
			}
		}
	}
}
1;
