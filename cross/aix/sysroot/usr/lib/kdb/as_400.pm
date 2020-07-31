# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/as_400.perlmod 1.1 
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

if ($led != 400){
	return (-1);
}

if ($led == 400) {

	infoprint(0,("This crash is an Instruction Storage Interrupt.\n\n"));
	$retstring = "\nThis crash is an Instruction Storage Interrupt.\n\n";
	printstack ($curthread);
	return ($retstring);

} 
1;