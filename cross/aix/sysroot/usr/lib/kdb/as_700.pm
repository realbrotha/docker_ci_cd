# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/as_700.perlmod 1.1 
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
package Master;


if ($led != 700){
	return (-1);
}

if ($led == 700) {

        infoprint(0,"This crash is due to a Program Interrupt.\n");
	$retstring = "\nThis crash is due to a Program Interrupt.\n";
        # locate prog_log value
        @proglog = split("\n", $Memory->xword_view(prog_log, 8));
        @proglog = split(" ", $proglog[2]);
        $proglog = $proglog[4];
        if ($proglog == 20000) {
                infoprint(1,"A Trap Instruction was recieved.\n");
		$retstring .= "A Trap Instruction was recieved.\n";
		if ((defined $curthread->stack) && ($curthread->stack->routine(0)) eq ".panic_trap") {
			$stats =~ /PANIC MESSAGES\n(.*)\n/ && ($panicmsg = $1);
			infoprint(1,"Panic Message: $panicmsg \n");
			$retstring .= "Panic Message: $panicmsg \n";
			if ($panicmsg =~ /dms/) { 
				dmschecks();
				$nostack = 1;
			} 
		} 
        } elsif ($proglog == 80000) {
                infoprint(1, "An Illegal Opcode was detected by cpu ${curcpu}.\n");
		$retstring .= "An Illegal Opcode was detected by cpu ${curcpu}.\n";
		eval{ $Dbg->sendcmd("f") };
		$rawstack = eval{ $Dbg->readcmd };
		$rawstack =~ /WARNING: bad IAR: ([0-9]+)/ && ($iar = $1);
		if (defined $iar) {
			infoprint(1, "This IAR is bad: ${iar}.\n");
			infoprint(1, "Most likely MODS will be needed for full information.  Please investigate stack.\n");
			$retstring .= "This IAR is bad: ${iar}.\n";
			$retstring .= "Most likely MODS will be needed for full information.  Please investigate stack.\n";
		} else {
			($junk, $junk, $junk, $junk, $opcode) = split(" ", $Memory->xword_view($curthread->stack->address(0),1));
			infoprint(1, "Decoding opcode ${opcode}\n");
			$retstring .= "Decoding opcode ${opcode}\n";
			$opdecode = memdecode($curthread->stack->address(0));
			if ($opdecode eq "?") {
				infoprint(1, "This is an invalid opcode.");
				$retstring .= "This is an invalid opcode.";
			} else { 
				infoprint(1, "This opcode is valid: ${opdecode}\n");
				$retstring .= "This opcode is valid: ${opdecode}\n";
				infoprint(1, "Please investigate why cpu $curcpu rejected this opcode.\n");
				$retstring .= "Please investigate why cpu $curcpu rejected this opcode.\n";
				$nostack = 1;
			}
		}
        } else {
                infoprint(1, "Odd proglog value: ${proglog}\n");
		$retstring .= "Odd proglog value: ${proglog}\n";
        }
	print "\n";
        printstack ($curthread) unless ($nostack);
	return ($retstring);

}
1;
