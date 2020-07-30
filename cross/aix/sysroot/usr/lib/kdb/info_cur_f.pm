#! /usr/bin/perl
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/info_cur_f.perlmod 1.1 
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
#executes `f` command, same as `stack` or `where` command in adump/kdb
#finds the stack info on the problem thread
#get cur_cpu->cur_thread->stack->rawinfo


$ffoo = $Dump->cur_cpu->cur_thread->stack->rawinfo;
infoprint(0, "$ffoo\n");
-1;
