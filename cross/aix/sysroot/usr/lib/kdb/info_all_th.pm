#! /usr/bin/perl
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/info_all_th.perlmod 1.2 
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
print "About to print raw info on all threads.\n";
print "May take up to an hour.\n";
print "Advise sending output to a file using command:\n";
print "\t()>usemaster \"-S info_all_th.pm -P9 -T outputfilename -M0\"\n";
my $thobj = $Kernel->thread_table;
my $thcount = $thobj->count;
for($i=0; $i<$thcount; $i++){
    infoprint(0, "Thread number $i\n");
    $th_bigthing = $thobj->element($i)->rawinfo;
    infoprint(0, "$th_bigthing \n");
}
-1;
