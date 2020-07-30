#! /usr/bin/perl
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/masterlibrary.perlmod 1.1 
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

########################################################
#
#               subroutines
#
########################################################


#######
#prints @_ if $Print_Level flag is >= $level
#######
sub infoprint
{
    $ms_level = shift(@_);
    autoflush STDOUT 1;

    #when the -F flag is called, it will only print to that file
    #and then return before printing to the screen
    if ($ms_output_file_name)
    {
        ms_printtofile(0, $ms_output_file_name, $ms_level, @_);
        return (1);
    }

    #when the -Tee flag is called, it will print to the specified file
    #and continue to print to the screen
    if($ms_tee_name)
    {
        ms_printtofile(0, $ms_tee_name, $ms_level, @_);
    }

    if(defined($ms_Print_Level))
    {
        if($ms_Print_Level >= $ms_level)
        {
           printf "%s", join ('', @_);
	autoflush STDOUT 1;
        }#ends if
    }#end outer if

    else
    {
        if($ms_level<=0)#default print level
        {
        printf "%s", join ('', @_);
	autoflush STDOUT 1;
        }#end if
	else{
	autoflush STDOUT 1;
	}
    }#end inner else
}



sub ms_printtofile{

    my $ms_which = shift(@_);  ###0 for printlevel, 1 for debug level
    my $ms_outputname = shift(@_);
    my $ms_level = shift(@_);
    if ($ms_which == 0){
	if(defined($ms_Print_Level)){$ms_checkwith = $ms_Print_Level;}	
    }
    else {
	if(defined($ms_Debug_Level)){$ms_checkwith = $ms_Debug_Level;}
    }
    open(OUT, ">>$ms_outputname");

        if(defined($ms_checkwith))
        {
            if($ms_checkwith >= $ms_level)
            {
                printf {OUT} "%s", join ('', @_);
		autoflush STDOUT 1;
            }#end if
	    else{
		autoflush STDOUT 1;
	    }
        }#end outer if
        else
        {
            if($ms_level<=0)#default print level
            {
                printf {OUT} "%s", join ('', @_);
		autoflush STDOUT 1;
            }#end if
	    else{
		autoflush STDOUT 1;
	    }
        }#end inner else

    close(OUT);

}#end sub ms_printtofile



#######
#prints @_ if $ms_Debug_Level flag is >= $ms_level
#######

sub dbgprint
{
    $ms_level = shift(@_);
    autoflush STDOUT 1;

    #when the -F flag is called, it will only print to that file
    #and then return before printing to the screen
    if ($ms_output_file_name)
    {
        ms_printtofile(1, $ms_output_file_name, $ms_level, @_);
        return (1);
    }

    #when the -Tee flag is called, it will print to the specified file
    #and continue to print to the screen
    if($ms_tee_name)
    {
        ms_printtofile(1, $ms_tee_name, $ms_level, @_);
    }

    if(defined($ms_Debug_Level))
    {
        if($ms_Debug_Level >= $ms_level)
        {
           printf "%s", join ('', @_);
        autoflush STDOUT 1;
        }#end if
    }#end outer if

    else
    {
        if($ms_level<=0)#default print level
        {
        printf "%s", join ('', @_);
        autoflush STDOUT 1;
        }#end if
        else{
        autoflush STDOUT 1;
        }
    }#end inner else
}#end dgbprint





#######
#searches $ms_dir and returns array of all files starting with $regex
#######
sub ms_findallfiles
{
    my ($ms_dir, $ms_regex) = @_;
    my $ms_i;
    local @ms_files = ();
    my $i=0;

    chomp($ms_dir);
    chomp($ms_regex);
    opendir(DIR, $ms_dir);
    @ms_files = grep{/^$ms_regex/ && -f "$ms_dir/$_"} readdir(DIR);

    closedir(DIR);
    chomp(@ms_files);
    foreach $ms_i (@ms_files)
    {
        infoprint(5, "\t$ms_i \n");
    }
    return @ms_files;
}#end findfile


#######
#finds exact file name inside $dir directory
#######
sub ms_findexactfile
{
    my ($ms_dir, $ms_filename) = @_;
    my $ms_i;
    local @ms_files = ();

    chomp($ms_dir);
    chomp($ms_filename);
    opendir(DIR, $ms_dir);
    @ms_files = grep{/^$ms_filename\b/ && "$ms_dir/$_"} readdir(DIR);
    closedir(DIR);
    chomp(@ms_files);
    foreach $ms_i (@ms_files)
    {
      infoprint(5, "\t$ms_i \n");
    }
    return @ms_files;
}#end findfile




#######
#finding difference of two arrays, second has higher priority
#need to strip off path
#######
sub ms_notinlist
{
    my ($ms_m, @ms_tot) = @_;
    my ($ms_i, $ms_mtemp, $ms_utemp);

    #strip masterelem of it's path for checking
    $ms_mtemp = ms_strippath($ms_m);

    for($ms_i=0; $ms_i<=$#ms_tot; $ms_i++)
    {
        #strip each userelem of it's path to check similarity

        $ms_utemp = ms_strippath($ms_tot[$ms_i]);

        if ($ms_mtemp eq $ms_utemp)
        {
            return(0);
        }#end if
    }#end for
    return(1);

}


#######
#sorts @ms_list of filenames by first stripping off path, comparing filenames,
#and then adding the path back onto filename to return sorted list
#######
sub ms_sortname
{
    local(@ms_list = @_);
    my ($ms_a, $ms_path, $ms_aname, @ms_name, %ms_hsh, $ms_i);

    foreach $ms_a (@ms_list)
    {
        $_ = $ms_a;
	/(.+)(\/\w*\.*\w*)$/ && ($ms_path = $1) && ($ms_aname = $2);
        chomp($ms_aname);
        chomp($ms_path);
        $ms_hsh{$ms_aname} = $ms_path;
    }#end foreach

    #sort by the name of each file, not just path

    @ms_name=keys(%ms_hsh);
    @ms_name = sort(@ms_name);

    #put path and name back together
    for($ms_i=0; $ms_i<=$#ms_list; $ms_i++)
    {
        $ms_list[$ms_i] = $ms_hsh{$ms_name[$ms_i]} . $ms_name[$ms_i];
    }#end for loop

    return @ms_list;
}


#######
#adds $ms_path to every file in @list
#######
sub ms_addpath
{
    local($ms_path, @ms_list) = @_;
    local $ms_a;

    foreach $ms_a (@ms_list)
    {
	$ms_a = $ms_path . "/" . $ms_a;
    }#end foreach

    return @ms_list;
}

#######
#strips path off of $path and returns the filename
#######
sub ms_strippath
{
    local($ms_path)= @_;
    $ms_path =~ s#.*/##;
    return($ms_path);

}
#######
#prints usage command when an invalid argument is passed
#######

sub ms_printusage{
    print "\n    USAGE: \n";
    print "\t-P[0-9]  Increase the print, or output level, default is 0. \n";
    print "\t-D[0-9]  Increase the debug level, default is 0\n"; 
    print "\t-L[library_list] Specify specific library lists to be run.\n";
    print "\t-S[script_list] Specify specific scripts to be run.\n";
    print "\t-M[0-999] Sets max number of scripts processed before a summary will appear.  Default = 0.\n";
    print "\t-T(!)[filename] Tells master to output to screen and specified file. ! will force overwrite\n";
    print "\t-F(!)[filename] Tells master to only output to specified file. ! will force overwrite\n";
    print "\t-C  Checks scripts and libraries for syntax errors by using `perl -c filename`\n";
    print "\n\tList should be specified in one of two ways.\n";
    print "\tAs a string, ie:  (0)>usemaster \"-S somefile somefile2 -P4 -T output -D 3 -Llib1 lib2\"\n";  
    print "\tAs a list, ie: (0)>usemaster (-Sfile1, -Sfile2, -P4, -Toutput, -D3, -Llib1, -Llib2)\n";
    print "\tNote the spacing restrictions on the list method:\n\t ";
    print "Invalid list will cause Adump to hang, invalid string will get you here.\n";
    exit(1);

}




1;
