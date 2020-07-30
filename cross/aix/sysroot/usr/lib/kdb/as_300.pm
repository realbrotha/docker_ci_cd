# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/as_300.perlmod 1.1 
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

if ($led != 300){
	return (-1);
}
if ($led == 300) {
	infoprint (0, "This crash is due to a Data Storage Interrupt.\n");	
	$retstring = "\nThis crash is due to a Data Storage Interrupt.\n";
        # locate vmmerrlog value
	@vmmerrlog = split("\n", $Memory->xword_view(vmmerrlog, 9));
	@vmmerrlog = split(" ",$vmmerrlog[3]);
	$vmmerrlog = $vmmerrlog[1];
	if ($vmmerrlog == 5) { 
		for ($i = 0; $i < 10; $i++) {
			$pdt = PagingDevice($i);
			next unless $pdt->type eq "PAGING";
			($pdt->rawinfo =~ /\(bufstr\)  : (.*)/) && ($buf = $1);
			# REPLACE this with a printing of the buf and checking for error = 5
			# and report on the major/minor of that.
		}
		$nostack = 1;
	}
	elsif ($vmmerrlog eq "0000000E") {
		infoprint(1,"Bad Address\n");
		$retstring .= "Bad Address\n";
	}
	elsif ($vmmerrlog eq "0000001C") { 
		$nostack = 1;
	}
	elsif ($vmmerrlog eq "00000086") { 
		infoprint(1,"Protection Exception\n");
		$retstring .= "Protection Exception\n";	
	}
	else { infoprint (1, "\n") }
        # print stack
	printstack ($curthread) unless ($nostack);
	return ($retstring);
} 
1;
