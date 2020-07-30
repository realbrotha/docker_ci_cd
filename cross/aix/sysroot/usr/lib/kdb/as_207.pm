# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/as_207.perlmod 1.1 
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

if ($led != 207){
	return(-1);
}
if ($led == 207) {
	infoprint(0,"This crash is due to an unknown Machine Check.\n");
	$retstring = "\nThis crash is due to an unknown Machine Check.\n";
	return ($retstring);
} 
1;
