#! /usr/bin/perl
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/info_all_f.perlmod 1.1 
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
#printing every `f` or `stack` object, not just current one

print "About to print raw info on all stack traces.\n";
print "May take up to 10 minutes.\n";
print "Advise sending output to a file using command:\n";
print "\t()>usemaster \"-S getallf -P9 -T outputfilename -M0\"\n";

$aftable = $Kernel->thread_table;
$afcount = $aftable->count;
my $i;
for($i=0; $i<$afcount; $i++){
    $afprintit = $aftable->element($i)->stack->rawinfo;
    infoprint(0, "$afprintit \n");
}
-1;
