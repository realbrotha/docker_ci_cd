# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/ascl_dmschecks.perlmod 1.1 
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
sub dmschecks {
	infoprint (1, "\n***** HACMP DMS Timeout debugging\n");
	# Try to determine if it is a true hang or a clstrmgr problem
	my $hang = 0;
	my $dmsconfig = 0;
	my $clstrmgr = undef;
	for (my $i = 0; $i < $tt->count; $i++) {
		if (defined $tt->element($i)) {
			$tt->element($i)->rawinfo =~ /(^NAME.*)/;
			if ( $tt->element($i)->rawinfo =~ /clstrmgr/ ) {
				$clstrmgr = $tt->element($i);
				last;
			}
		}
	}
	unless (defined $clstrmgr) {
		infoprint (1, "The Cluster manager thread is not running.\n");
		return;
	}
	($clstrmgr->rawinfo =~ m# WTYPE \W+ (\w+) \W+ #x) && (my $clstrwtype = $1);
	infoprint (1, "The cluster manager thread is waiting on ");
	if ($clstrwtype eq "WPGIN") { 
		infoprint (1, "paging.\n");
		my $pdt;
		$clstrmgr->rawinfo =~ m# \W+ wchan2 \W+ (\w+) \W+ #x;
		my $command = join(" ", "vmwait", $1);
		if ($1 =~ /[^0]+/) { 
			eval{ $Dbg->sendcmd($command) };
			$seginfo = eval{ $Dbg->readcmd };
		} else { $seginfo = "sidx"; }
		if ($seginfo =~ /sidx/) {
			$pdt = $clstrmgr->waitseg->pagingdevice;
		} else {
			#  the wait info is not giving a sidx, as the waitseg method expects.
			my $pfn;
			( $seginfo =~ /number ([0-9,A-F]*)/ )  && ($pfn = $1);
			$command = join(" ", "pft", "1", $pfn);
			eval{ $Dbg->sendcmd($command)};
			my $pfnraw = eval{ $Dbg->readcmd };
			( $pfnraw =~ /\(devid\)  : (\d+)/) && (my $pdtidx = $1);
			$pdt = PagingDevice->new( $pdtidx ) if (defined $pdtidx);
		}
		if (defined $pdt) {
			infoprint (1, "It is waiting on I/O for device (major, minor) (hex($pdt->devmajor), hex($pdt->devminor)), which has ", hex($pdt->unfinishedio)," unfinished I/O");
			if (hex($pdt->unfinishedio) == 1) {
				infoprint (1, ".\n");
			} else {
				infoprint (1, "s.\n");
			}
			if (hex($pdt->unfinishedio) <= 10) {
				infoprint(1, "This may not be an I/O problem.  Doing normal hang checks.\n");
				hangchecks();
				infoprint(1, "\n");
			}
		} else {
			infoprint (1, "Unable to determine the device being waited for.\n");
		}
		infoprint (1, "Please also follow the standard HACMP tuning considerations:\n\n");
		$dmsconfig = 1;
	} elsif ($clstrwtype eq "NOWAIT") {
		infoprint (1, "nothing; it's on a cpu.\n");
		$hang = 1;
		$dmsconfig = 1;
	} elsif ($clstrwtype eq "WEVENT") {
		infoprint (1, "an event.\n");
		$dmsconfig = 1;
		infoprint (1, "Cluster Manager stack trace: \n\n");
		printstack ($clstrmgr);
		infoprint (1, "\n");
	} elsif ($clstrwtype eq "WLOCK") {
		infoprint (1, "a lock.\n");
		# Determine who is holding the lock, and that is the true source of the problem.
		$hang = 1;
	} elsif ($clstrwtype eq "WCPU") {
		infoprint (1, "a cpu.\n");
		$hang = 1;
		$dmsconfig = 1;
	} else {
		infoprint (1, "Something unusual: $clstrwtype \n");
		$dmsconfig = 1;
		infoprint (1, "\n");
		printstack ($clstrmgr);
		infoprint (1, "\n");
	}
	if ($dmsconfig) {
		# These can't be checked within the dump, just warn 
		infoprint (1, "Please insure the customer has changed syncd to 10 and has the Failure Detection Rate set to Slow.\n");
		# Check AIX Power Management
		for ($i = 0; $i < $pt->count; $i++) {
			my $proc = $pt->element($i);
			if ((defined $proc) && ($proc->rawinfo =~ /AIXPowerMgtDaemon/)) {
				infoprint (1, "Please have the customer disable Power Management; it was running at the time of the DMS Timeout.\n");
				last;
			}
		}
		# Check I/O pacing
		my @watermarks = split("\n", $Memory->xword_view(v, B));
		@watermarks = split(" ", $watermarks[3]);
		infoprint (1, "High water mark: ", hex($watermarks[2]),"     Low water mark: ", hex($watermarks[3]),"\n");
		if ((hex($watermarks[2]) == 0) || (hex($watermarks[3]) == 0)) {
			infoprint (1, "I/O pacing is not enabled.  Please enable.\n");
		}
	}
	if ($hang) {
		hangchecks();
	}
	return;
}
1;
