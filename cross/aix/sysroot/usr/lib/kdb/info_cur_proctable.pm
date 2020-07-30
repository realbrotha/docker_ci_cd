#! /usr/bin/perl
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/info_cur_proctable.perlmod 1.1 
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

#This prints the Process Table,
#same as the command   `p *`

$proctabfoo = $Kernel->proc_table->rawinfo;
infoprint(0, "Process table:  `p *`\n");
infoprint(0, "$proctabfoo\n");

-1;
