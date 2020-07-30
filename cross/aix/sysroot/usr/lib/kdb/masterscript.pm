#! /usr/bin/perl  -w
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/masterscript.perlmod 1.3.1.2 
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

#########################################################
#		master script				#
#							#
#							#
#To run: Set environment variables MASTERLIST and	#
#	USERLIST to the paths where the master files	#
#	and user files are located, respectively.	#
#	masterlibrary file must be found in current	#
#	directory or in @INC path.			#
#Arguements: -P[1-9] printlevel, default=0, 9=verbose	#
#	     -D[1-9] debuglevel, " for making script/lib#
#	     -L[lib_list] override lib search		#
#	     -S[script_list] override script search	#
#	     -M[0-999] sets max number of scripts	#
#		processed before a summary will appear.	#
#		Default = 0, unless only one script is  #
#		run, then Default=1.			#
#	     -T[filename] Tells master to output to	# 
#		screen and specified file		#
#	     -F[filename] Tells master to only output	#
#		to specified file			# 
#	     -T[!filename] Forces overwrite of file if	#
#		it exists.				#
#	     -F[!filename] Forces overwrite of file if	#
#		it exists.				#
#	     -C  Runs syntax check on scripts before	#
#		processing. `perl -c filename`		#
#########################################################

sub master{

#argument list
@ARGV = @_;

undef $ms_Debug_Level;
undef $ms_Print_Level;
undef $ms_library_list;
undef $ms_script_list;
undef $ms_tee_name;
undef $ms_output_file_name;
undef $ms_max_elem;
undef $ms_check_syntax;
undef $ms_ovchoice;
$ms_finaltotsec=0;
$ms_finaltotmin =0;

undef @ms_uscripts;   		#user scripts
undef @ms_mscripts;		#master scripts 
undef @ms_ulibs;		#user libs
undef @ms_mlibs;		#master libs
undef @ms_slist;		#script list
undef @ms_llist;		#library list
undef @ms_totalscripts;		#list of all libs and scripts, in that order


###necessary initialization file needed to access kdb and adump objects
use init;
###

###file of subroutines used
require "/usr/lib/kdb/masterlibrary.pm" || die "can't access masterlibrary: $!\n";
###


###allows for argument lists like "-Sfile1 file2 -L file3 file4 -P9 -D 6"
if ($#ARGV<1){
    @ARGV = split(/[ ,]/, $ARGV[0]);
}


$ms_loc = 0;
foreach $a (@ARGV)
{
    $_ = $a;

    ###if no flag exists, append previous flag to argument
    ###-P1 2 will set level to 2, not 12 or 1.  -S file1 file2 will set -S file1 -S file2

    if ($_ eq ''){
	$ms_loc++;
	next;
    }
    ###if it doesn't start with a -
    if ($_ !~ /^-/)  
    {
	if(($ms_loc)>0){
	$ms_other_loc = $ms_loc;
	while(defined($ARGV[$ms_other_loc-1])){
	    if ($ARGV[$ms_other_loc-1] =~ /^(-\w)/){
		$ARGV[$ms_loc] = $1 . $ARGV[$ms_loc];
		last;
	    }#end if
	    else{
	  	$ms_other_loc--;
	    }#end else
	}#end while
        $_ = $ARGV[$ms_loc];
	}
	else{ ms_printusage(); }
    }
    else
    {
	/^-(\w.*)/;
	if ($1 =~ /(D|P|L|S|M|T|F)(\s+|)$/){ 
	$ms_loc++;
	next;
	}
    }


    if (/^-P(.*)/) {$ms_Print_Level = $1}
    elsif (/^-S(.+)/) {if(defined($ms_script_list)){$ms_script_list = $ms_script_list . ",". $1;}
			else{ $ms_script_list = $1;}}
    elsif (/^-F(.*)/) { $ms_output_file_name = $1}
    elsif (/^-T(.*)/) { $ms_tee_name = $1}
    elsif (/^-M(.*)/) {$ms_max_elem = $1}
    elsif (/^-L(.*)/) {if(defined($ms_library_list)){$ms_library_list = $ms_library_list . ",". $1;}
			else{ $ms_library_list = $1;}}
    elsif (/^-D(.*)/) {$ms_Debug_Level = $1}
    elsif (/^-C/)     {$ms_check_syntax = 1}
    else { ms_printusage();}
    $ms_loc++;

}

###these next two if blocks have to be placed before any infoprints, because on
###an infoprint, it writes to and therefore creates a file, and the program will exit in
###the following check.
if($ms_tee_name) {
	if ($ms_tee_name =~ /^\!\s*(\w+)/){
		$ms_tee_name = $1;
		`rm $ms_tee_name`;
	}
	elsif(-f $ms_tee_name){
	    print "Error:  File already exists.\n";
	    print "Advise removing file $ms_tee_name or use:\n";
	    print "\t()>usemaster \"-F !$ms_tee_name\" to overwrite.\n";
	    next;
	}
}


###this is else because you can only output to one of the two, not both
if($ms_output_file_name) {
	if ($ms_output_file_name =~ /^\!\s*(\w+)/){
		$ms_output_file_name = $1;
		`rm $ms_output_file_name`;
	}
	elsif(-f $ms_output_file_name){
	    print "Error:  File already exists.\n";
	    print "Advise removing file $ms_output_file_name or use:\n";
	    print "\t()>usemaster \"-F !$ms_output_file_name\" to overwrite.\n";
	    next;
	}
}
if($ms_library_list) {infoprint(6, "\nAlternate library files include: $ms_library_list...\n");}

$ms_max_elem = -1 unless defined($ms_max_elem);
if(defined($ms_script_list)) {
	if($ms_max_elem <0){$ms_max_elem=1;}	
	infoprint(6, "\nAlternate script files include: $ms_script_list...\n");
	}


#######
#check environment, if no variables there, set masterdir to default location,
#set userdir to current directory
#######

if ($ENV{"ADUMP_MASTER"})
{
    $ms_masterdir = $ENV{"ADUMP_MASTER"};
    infoprint(3, "\nImport environment variable ADUMP_MASTER...\n");
    infoprint(5, "ADUMP_MASTER = $ms_masterdir\n");
}
else
{

    $ms_masterdir = "/usr/lib/kdb";
    infoprint(3, "\nNo ADUMP_MASTER environment variable found...\n");
    infoprint(3, "Setting default master directory...\n");
    infoprint(5, "Default master directory set to $ms_masterdir...\n");
}


if ($ENV{"ADUMP_USER"})
{
    $ms_userdir = $ENV{"ADUMP_USER"};
    infoprint(3, "\nImport environment variable ADUMP_USER...\n");
    infoprint(5, "ADUMP_USER = $ms_userdir\n");
}
else
{
    chomp($ms_userdir = ".");
    infoprint(3, "\nNo ADUMP_USER environment variable found...\n");
    infoprint(3, "Setting default user directory to current directory...\n");
    infoprint(5, "Default user directory set to $ms_userdir...\n");
}




#######
#saves filenames of master scripts/libraries from respective locations
#######

infoprint(8, "Saving filenames of scripts, libraries...\n");

if(defined($ms_library_list))
{
    infoprint(2, "\nFinding alternate library files...\n");
    @ms_llist = split /,/, $ms_library_list;
    infoprint(5, "$ms_userdir is the path used...\n");


    foreach $ms_i (@ms_llist)
    {
        if($ms_i =~ /(\w+)\*/){
	    @ms_ulibs = (@ms_ulibs, ms_findallfiles($ms_userdir, "$1"));
    	}
	else{
	    @ms_ulibs = (@ms_ulibs, ms_findexactfile($ms_userdir, $ms_i));
	}
    }

    infoprint(2, "\nNo user libraries found!\n") unless (@ms_ulibs);
    infoprint(5, "$ms_masterdir is the path used...\n");


    foreach $ms_i (@ms_llist)
    {
        if($ms_i =~ /(\w+)\*/){
	    @ms_mlibs = (@ms_mlibs, ms_findallfiles($ms_masterdir, "$1"));
    	}
	else{
	    @ms_mlibs = (@ms_mlibs, ms_findexactfile($ms_masterdir, $ms_i));
	}
    }

    infoprint(2, "\nNo master libraries found!\n") unless (@ms_mlibs);
}
else
{
    infoprint(2, "\nFinding user libraries from USERLIST...\n");
    infoprint(5, "$ms_userdir is the path used...\n");

    @ms_ulibs = ms_findallfiles($ms_userdir, "ascl_");

    infoprint(2, "\nNo user libraries found!\n") unless (@ms_ulibs);
    infoprint(2, "\nFinding master libraries from MASTERLIST...\n");
    infoprint(5, "$ms_masterdir is the path used...\n");

    @ms_mlibs = ms_findallfiles($ms_masterdir, "ascl_");

    infoprint(2, "\nNo master libraries found!\n") unless (@ms_mlibs);
}


@ms_ulibs = ms_addpath($ms_userdir, @ms_ulibs);
@ms_mlibs = ms_addpath($ms_masterdir, @ms_mlibs);


if(defined($ms_script_list))
{
    infoprint(2, "\nFinding alternate user scripts...\n");

    @ms_slist = split/,/, $ms_script_list;

    infoprint(5, "$ms_userdir is the path used...\n");

    foreach $ms_i (@ms_slist)
    {
        if($ms_i =~ /(\w+)\*/){
	    @ms_uscripts = (@ms_uscripts, ms_findallfiles($ms_userdir, "$1"));
    	}
	else{
	    @ms_uscripts = (@ms_uscripts, ms_findexactfile($ms_userdir, $ms_i));
	}
    } 

    infoprint(2, "\nNo alternate user scripts found!\n") unless (@ms_uscripts);
    infoprint(2, "\nFinding alternate master scripts...\n");
    infoprint(5, "$ms_masterdir is the path used...\n");


    foreach $ms_i (@ms_slist)
    {
        if($ms_i =~ /(\w+)\*/){
	    @ms_mscripts = (@ms_mscripts, ms_findallfiles($ms_masterdir, "$1"));
    	}
	else{
	    @ms_mscripts = (@ms_mscripts, ms_findexactfile($ms_masterdir, $ms_i));
	}
    } 
    infoprint(2, "\nNo master scripts found!\n") unless (@ms_mscripts);
}

else
{
    infoprint(2, "\nFinding user scripts from USERLIST...\n");
    infoprint(5, "$ms_userdir is the path used...\n");

    @ms_uscripts = ms_findallfiles($ms_userdir, "as_");

    infoprint(2, "\nNo user scripts found!\n") unless (@ms_uscripts);
    infoprint(2, "\nFinding master scripts from MASTERLIST...\n");
    infoprint(5, "$ms_masterdir is the path used...\n");

    @ms_mscripts = ms_findallfiles($ms_masterdir, "as_");

    infoprint(2, "\nNo master scripts found!\n") unless (@ms_mscripts);
}


@ms_uscripts = ms_addpath($ms_userdir, @ms_uscripts);
@ms_mscripts = ms_addpath($ms_masterdir, @ms_mscripts);


#######
#userscripts/libs have higher priority
#these for loops check for unique elements, giving user elems higher priority
#######

infoprint(5, "\nChecking for duplicate scripts, libraries...\n");

@ms_totalscripts = @ms_uscripts;


for($ms_i=0; $ms_i<=$#ms_mscripts; $ms_i++)
{
    if (ms_notinlist($ms_mscripts[$ms_i], @ms_totalscripts))
	{
	    @ms_totalscripts = (@ms_totalscripts, $ms_mscripts[$ms_i]);
	}#end if
}#end for


@ms_totallibs = @ms_ulibs;


for($ms_i=0; $ms_i<=$#ms_mlibs; $ms_i++)
{
    if (ms_notinlist($ms_mlibs[$ms_i], @ms_totallibs))
	{
	    @ms_totallibs = (@ms_totallibs, $ms_mlibs[$ms_i]);
	}#end if
}#end for
 
#######
#makes list of all files to be included, sorting scripts in ascending order
#######

@ms_totallist = (@ms_totallibs, ms_sortname(@ms_totalscripts));

#######
#opens each library first, then each script specified  
#from USERLIST and MASTERLIST
#######

infoprint(3, "Opening library files, then script files...\n");
$ms_loc_count = 0;

foreach $ms_i (@ms_totallist)
{
    ($ms_sec, $ms_min) = (localtime)[0, 1];

    $_ = $ms_i;
    $ms_currentfilename = $ms_i;
    $ms_shortpathname = ms_strippath($ms_currentfilename); 

    if(/(ascl_)/){infoprint(8, "\nOpening library $ms_currentfilename...\n");}
    if(/(as_)/){infoprint(7, "\nOpening script $ms_currentfilename...\n");}

    ###requires current file
    if (defined($ms_check_syntax)){
	`perl -c $ms_i`;
    }

    $ms_returnvalue = do "$ms_i" || die "\nCouldn't open $ms_i: $!";
    chomp($ms_returnvalue);

    infoprint(9, "Finished opening $ms_shortpathname\n");

    ###turns return value into an integer

    $ms_bar = sprintf ("$ms_returnvalue");

    if ($ms_bar =~ /(^[-]{0,1}\d+$)/) { $ms_num_val = $1 }
    else { $ms_num_val = 1 }

    $_ = $ms_i;


    $fileobj[$ms_loc_count][0] = $ms_num_val;
    $fileobj[$ms_loc_count][1] = $ms_returnvalue;

    ###times how long each process took to run, outputs at printlevel 9

    ($ms_sec1, $ms_min1) = (localtime)[0, 1];
    $ms_totsec = $ms_sec1-$ms_sec;
    $ms_totmin = $ms_min1-$ms_min;
    if($ms_totsec<0)
    { $ms_totsec = 60+$ms_totsec; $ms_totmin--; }
    if($ms_totmin<0)
    {
        $ms_totmin = 60+$ms_totmin;
    }


    $fileobj[$ms_loc_count][2] = $ms_totsec;
    $ms_finaltotsec += $ms_totsec;
    $fileobj[$ms_loc_count][3] = $ms_totmin;
    $ms_finaltotmin += $ms_totmin;

    if(/as_/){
	$ms_temp_array_value = (ms_strippath($ms_i)." returned a positive value\n") unless ($ms_num_val<0); 
	infoprint(1, "$ms_temp_array_value");
	undef $ms_temp_array_value;
    infoprint(9, "Process $ms_shortpathname took: $ms_totsec sec, $ms_totmin min.\n");
    $ms_loc_count++;
    }#end if

    else{
	$ms_temp_array_value = (ms_strippath($ms_i)." returned a positive value\n") unless ($ms_num_val<0); 
	infoprint(9, "$ms_temp_array_value");
	undef $ms_temp_array_value;

        infoprint(9, "Process $ms_shortpathname took: $ms_totsec sec, $ms_totmin min.\n");
        $ms_loc_count++;
    }#end else
    
}#end foreach





##########
# Summary# 
##########

if(($#ms_totalscripts) >= $ms_max_elem){
    my $ms_outercount = 0;
    infoprint(0, "\n\n	/-----------------------------------------/\n");
    infoprint(0, "	/					  /\n");
    infoprint(0, "	/		SUMMARY			  /\n");
    infoprint(0, "	/					  /\n");
    infoprint(0, "	/-----------------------------------------/\n\n");

    foreach $ms_i (@ms_totallist){
	$_ = $ms_totallist[$ms_outercount];
        if (/ascl_/){   ###print library info at high infoprints
	    infoprint(6, "\nLibrary " . ms_strippath($ms_i) . "\n"); 
	    infoprint(9, "Full library path is $ms_i\n");
	    infoprint(6, "Time to complete library: ");
            infoprint(6, "$fileobj[$ms_outercount][2] sec, $fileobj[$ms_outercount][3] min.\n");
	    infoprint(8, "Return value is: $fileobj[$ms_outercount][1]\n");
	    $ms_outercount++;  
	    next;
	} ###skip library files
	if($fileobj[$ms_outercount][0] >= 0){
	    infoprint(6, "\n/-----------------------------------------------------------------------/");
	    infoprint(0, "\nScript " , ms_strippath($ms_totallist[$ms_outercount]));
	    infoprint(0, " indicated positive return value.\n");
	    infoprint(1, "Full path to script is:\n$ms_totallist[$ms_outercount]\n");
	    infoprint(2, "Time to complete script: ");
	    infoprint(2, "$fileobj[$ms_outercount][2] sec, $fileobj[$ms_outercount][3] min.\n");
	    infoprint(0, "Return value is: $fileobj[$ms_outercount][1]\n");
	    infoprint(6, "/-----------------------------------------------------------------------/\n");
	    $ms_outercount++;
	}#end if
	else
	{  ###prints scripts that returned negative(no problem with them)
	    infoprint(6, "\nScript " . ms_strippath($ms_i) );
	    infoprint(6, " indicated negative return value, most likely this is not a problem.\n");
	    infoprint(8, "Full path to script is $ms_i\n");                 
	    infoprint(6, "Time to complete script: ");
	    infoprint(6, "$fileobj[$ms_outercount][2] sec, $fileobj[$ms_outercount][3] min.\n");
	    infoprint(7, "Return value is: $fileobj[$ms_outercount][1]\n");
	    $ms_outercount++;
	}

    }#end foreach 
    infoprint(5, "\nTotal execution time:  ");
    $ms_calctemp = $ms_finaltotsec % 60;
    $ms_moreminutes = $ms_finaltotsec / 60;
    $ms_moreminutes = int($ms_moreminutes);
    $ms_finaltotmin += $ms_moreminutes;
    infoprint(5, "$ms_calctemp secs, $ms_finaltotmin min\n");
    
}#end if

infoprint(0, "\n\nEnd of Automated Analysis\n\n");

}#end sub master

1;

