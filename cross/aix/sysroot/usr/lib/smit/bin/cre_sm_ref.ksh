#!/bin/ksh
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/bin/smit/libsmhelp/cre_sm_ref.ksh 1.1 
#  
# Licensed Materials - Property of IBM 
#  
# Restricted Materials of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 1997 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
BIN="/usr/bin"
CD="${BIN}/cd"
FIND="${BIN}/find"
MKDIR="${BIN}/mkdir"
HELP_BIN="/usr/lib/smit/bin"
#Create the FILELIST file which contains all
#existing SM HTML help files for the language $LANGUAGE
#specified.

CUR=$(pwd)

if [[ $# -ne 3 ]];then
  print ""
  print "Usage: cre_sm_ref.ksh LANGUAGE FILESET_NAME DOC_PATH"
  print "   where LANG = Locale"
  print "         FILESET_NAME = Name of fileset"
  print "         DOC_PATH = Path name where actual help files reside"
  print "                    starting after the top path name:"
  print "                    /usr/share/man/info/\${LANG}\n"
  print "   e.g:  cre_sm_ref.ksh en_US aix a_doc_lib/WebSM_context_help\n"
  exit 1
fi

LANGUAGE=$1
LPP=$2
DOC_PATH=$3

FILE="/tmp/"${LANGUAGE}"_"${LPP}".list"
FIXED_DOC_PATH="/usr/share/man/info/${LANGUAGE}"
HELP_FILE_PATH=${FIXED_DOC_PATH}/${DOC_PATH}

REG_PATH="/usr/share/man/info/${LANGUAGE}/doc_registry"

if [[ ! -d ${HELP_FILE_PATH} ]];then
    print "Error: ${HELP_FILE_PATH} does not exist"
    exit 1
fi

$CD ${HELP_FILE_PATH}
$FIND ${HELP_FILE_PATH} -type f -print> ${FILE}

if [[ ! -d ${REG_PATH} ]];then
  $MKDIR -p ${REG_PATH}
fi 

REF_FILE=${REG_PATH}/${LPP}.ref

${HELP_BIN}/cre_sm_ref ${REF_FILE} ${FILE} 

if [[ -f ${REF_FILE} ]];then
  sort -d +1 ${REF_FILE} > /tmp/help_ref.xxxx
  mv /tmp/help_ref.xxxx ${REF_FILE}
fi


