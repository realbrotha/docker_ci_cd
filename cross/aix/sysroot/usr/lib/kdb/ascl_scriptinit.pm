# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/ascl_scriptinit.perlmod 1.1 
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
#First script run

#  Version 0.2.1
#
#  This script is provided as-is, etc. etc.
#  I am constantly updating this script; this may not be the most recent version.
#  As I locate a permenant place to keep this, I'll update the comments with a location.
#  Obviously, this is not meant to replace a trained investigation into a dump, but as a tool
#  for the trained investigator.
#  
#  This does require the 5.1 adump perl modules; however, with those, it can read a 43S dump using
#
#  Changes to latest version:
#  I've fixed some display issues with the I/O buf locating.



package Master;

infoprint(0,"\nAuto Debugging Dump File\n\n");
$ct = $Kernel->cpu_table;     # Getting the cpu table
$tt = $Kernel->thread_table;  # Getting the thread table
$pt = $Kernel->proc_table;    # Getting the proc table
$curcpu = $Dump->cur_cpu_id;  # Using xword_view corrupts the cur_cpu_id value, this hacks around it
$curthread = getthreadfromcpu($curcpu);
$stats = $Dump->stat;
$stats =~ /LEDs: ([0-9]{3})/ && ($led = $1);
($led = "User Forced Dump") unless $led;
infoprint(1,"LED: $led \n\n");
1;
