#! /usr/bin/perl
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/info_cur_proc.perlmod 1.2 
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

#This prints the current process, or the one it hung on.
#Just like the   `p` command in adump/kdb

$proccount=-1;
$procorigfoo = $Kernel->proc_table;
$procfoo = $procorigfoo->rawinfo;
@procfoo = split "\n", $procfoo;
foreach $proca (@procfoo){
    $_ = $proca;
    if((/^proc/) || (/^pvproc/)){
	$proccount++;
    }
    if(/(\d+)\*/){
	infoprint(0,$proca,"\n");
	$proctemp=$procorigfoo->element($proccount)->rawinfo;
	infoprint(0, $proctemp);
	undef($proctemp);
    }
}


-1;
