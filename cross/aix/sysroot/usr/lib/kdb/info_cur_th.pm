#! /usr/bin/perl
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/info_cur_th.perlmod 1.1 
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
#get cur_cpu->cur_thread->rawinfo-> tid
$thfoo = $Dump->cur_cpu->cur_thread->rawinfo;
infoprint(0,"$thfoo \n");
$_ = $thfoo;
/tid :(\w+)/ && ($thingy = $1);
infoprint(0,"$thingy is TID\n");
-1;
