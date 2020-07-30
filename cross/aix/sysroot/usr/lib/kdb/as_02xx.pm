# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/as_02xx.perlmod 1.1 
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

if ($led =~ /0+2[0-9][0-9]/) {
	infoprint(0, "This crash is due to a Machine Check.\n");
	$retstring = "This crash is due to a Machine Check.\n";
	return ($retstring);
} 
else{
	return (-1);
}
1;
