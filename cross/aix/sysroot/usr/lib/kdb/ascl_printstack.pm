# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/ascl_printstack.perlmod 1.1 
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

sub printstack {
        my $curthread = $_[0];

	###this next line is needed, for some reason, without it the rest of the program
	###can't see any mst objects!
	$dog = $curthread->mst->registers->reg(7);
	#print "$dog is mst reg reg 7\n\n\n\n";

	$curthread->rawinfo =~ /NAME\.\W+(\w+)\W+/ && (my $threadname = $1);
	infoprint (1, "Thread slot: ", $curthread->slot, " Name: $threadname \n\n");
	if (defined $curthread->stack) {
		#  For stacks with multiple MST frames, I've needed to re-write the stack calls.
		#  A lot of this is stolen right from the adump Perl modules.
		#  We're about to do some funky stuff.  Let's not make any calls to the adump modules
		#  during it.
		my $curthreadslot = $curthread->slot;
		my $oldstar = $*;
		$* = 1;
		eval{ $Dbg->sendcmd("set 9") };
		eval{ $Dbg->sendcmd("set 10") };
		eval{ $Dbg->readcmd() };
		my $command = join(" ", "f", $curthreadslot);
		eval{ $Dbg->sendcmd($command) };
		my $rawstacksimple = eval{ $Dbg->readcmd()};
		eval{ $Dbg->sendcmd("set 9") };
		eval{ $Dbg->sendcmd("set 10") };
		eval{ $Dbg->readcmd() };
		my $newdepth = (split(/^(?=\[)/,$rawstacksimple) - 1);
		my ($trash,@frames) = split(/^(?=\[)/,$rawstacksimple);
		#  We now have a raw stack with all the frames.
		#  Now we need to determine where the breaks are.
		my @wholeframes = split(/Exception/,$rawstacksimple);
		my @framebreaks;
		my $numframebreaks = 0;
		foreach (@wholeframes) {
			$framebreaks[$numframebreaks] = (split(/^(?=\[)/,$_) - 1);
			$framebreaks[$numframebreaks] += $framebreaks[$numframebreaks-1] unless ($numframebreaks == 0);
			$numframebreaks++;
		}
		$* = $oldstar;
		eval{ $Dbg->sendcmd("f") };
		$rawstacksimple =~ /(WARNING.*)/ && (my $warn = $1);
		if (defined $warn) { infoprint (1, "$warn \n"); }

		my $numintpri = 1;
		my $intpri;
		($curthread->mst->rawinfo =~ /> sw[\n,.]*intpri\s+([0-9,A-F]+)/ ) && ($intpri = $1);
		infoprint (1, "Intpri = ", hex($intpri), "\n");
		for (my $i = 0; $i < $newdepth; $i++) {
			my $kexcmd = join(" ", "lke", $frames[$i] =~ /^\[([0-9,A-F]+)\]/ );
			eval{ $Dbg->sendcmd($kexcmd)};
			my @kex = split("\n", eval{ $Dbg->readcmd });
			$kex[3] =~ /\/.*\/(.*)/ && (my $kex = $1);
			if ($kex ne "") {
			    infoprint (1, "[$kex]:"); 
			}

			###had to change this to work with infoprint
			$_ = $frames[$i];
                        /\](\.?\w+)\+/ && ($dog1=$1);
                        /\[([0-9,A-F]+)\]/ && ($dog2 = $1);
                        /\w+\+(\w+)\W/ && ($dog3= $1);
                        infoprint(1, "$dog1: ($dog2) + $dog3");


			if (($i == 0) && (not defined $warn)) {
				infoprint (1, "     ", memdecode($frames[$i] =~ /^\[([0-9,A-F]+)\]/), "\n");
			} else { infoprint (1, "\n"); }
			foreach (@framebreaks) {
				if ( ($i == ($_ - 1)) && ($i != ($newdepth - 1))) {
					infoprint (1, "\nNext Frame\n\n");
					$wholeframes[$numintpri] =~ /intpri\s+([0-9,A-F]+)/ && ($intpri = $1);
					$numintpri++;
					infoprint (1, "Intpri = ", hex($intpri), "\n");
				}
			}
		}
	} else { infoprint (1, "Stack not defined.\n"); }
}
1;
