# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/as_user_forced_dump.perlmod 1.1 
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

if ($led ne "User Forced Dump"){
	return (-1);
}

if ($led eq "User Forced Dump") {
	
        infoprint(0,("This crash is a Forced Dump.\n"));
	$retstring = "\nThis crash is a Forced Dump.\n";
        # Standard hang procedures.
	hangchecks();

	return ($retstring);
} 
1;
