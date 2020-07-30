# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/MacroUnload.perlmod 1.1 
#  
# Licensed Materials - Property of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 2000 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
################################################################

			package MacroUnload;

################################################################


use init qw( $BaseName );

##############
#
# unimport
#
##############

### Unload the functions of this library.


sub unimport {


	do {
		eval ('for $key (keys %main::'."$BaseName".'::) {
				delete $main::'."$BaseName".'::{$key}; }');
	};

        for $key (keys %INC) {
                if ( $key =~ /^$BaseName\W+/ ) {
                        delete $INC{$key};
                }
        }

        for $key (keys %main::) {
                if ( $main::{$key} =~ /\W+$BaseName\W+/ ) {
                        delete $main::{$key};
                }
        }
}

1;
