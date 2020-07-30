# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/MacroTemplate.perlmod 1.2 
#  
# Licensed Materials - Property of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 1999,2000 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 

################################################################

			package MacroTemplate;

################################################################


use init qw( $BaseName );

$template = "
################################################################

			package $BaseName;

################################################################


".'
use init; 		### import is required

BEGIN {
	require MacroUnload;
	@ISA = qw( MacroUnload );
}

for $key (sort keys %main::'."$BaseName".'::) {

        local *sym=$main::'."$BaseName".'::{$key};

        if ( defined &sym && $key ne \'unimport\' ) {
                $main::{$key} = $main::'."$BaseName".'::{$key};
        }
};



#######################################################
### WRITE YOUR OWN MACRO AS a Perl subroutine
### sub yourmacro { 
### 		yourmacro body 
### } 
#######################################################







########################################################



1;
';

print $template;


1;
