/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2009          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*===========================================================================*/
/*                                                                           */
/* Module Name:  ct_mcerr.h                                                  */
/*                                                                           */
/* Description:                                                              */
/*     Definition of errors returned by the RMC Subsystem in responses       */
/*     and event notifications.                                              */
/*                                                                           */
/*     This file is formatted to be viewed with tab stops set to 4.          */
/*===========================================================================*/
/* @(#)87   1.49   src/rsct/rmc/mccommon/ct_mcerr.h, mccommon, rsct_rhay53, rhay531006a 6/13/09 23:08:40 */

#ifndef _H_CT_MCERR
#define _H_CT_MCERR

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Error codes are grouped into ranges of values. Each range represents errors
 * of a similar nature, e.g. command specification errors, errors in accessing
 * resources, etc.
 *
 *        Error Code Value                    Error Category
 *    ========================           ========================
 *     0x00000  thru  0x0ffff             Specific resource
 *     0x10000  thru  0x1ffff             Common resource
 *     0x20000  thru  0x2ffff             Reserved for internal RMC use
 *     0x30000  thru  0x3ffff             Command specification
 *     0x40000  thru  0x4ffff             Resource access or usage
 *     0x50000  thru  0x5ffff             Expression specification
 *     0x60000  thru  0x6ffff             Select string specification
 *     0x70000  thru  0x7ffff             Security
 *
 * Common resource errors can be returned by any resource and have the
 * same meaning across all resource classes. Specific resource errors are
 * only applicable to specific resource classes; these error codes can be
 * duplicated across different resource classes and have different meanings.
 *
 * When an error code is returned in a response or event notification, it is
 * accompanied by an error message and, possibly, one or more error arguments.
 * The error message is translated into the locale of the client application,
 * assuming that the correct message catalog is installed. If arguments
 * are present they are the arguments used in the returned message. The
 * error message can be returned by the application to the user or the
 * error code and arguments can be analyzed by the program in order to
 * perform error recovery.
 *
 * Along with each error code defined in this file is the specification of
 * any arguments returned and their type.
 */


/*****************************************************************************/
/**                                                                         **/
/**      Internal RMC errors                                                **/
/**                                                                         **/
/*****************************************************************************/

#define RMC_GENERR_RMC_INTERNAL	0x20000		/* Internal RMC Errors error     */
											/* category                      */

#define RMC_ENOSUPPORTEDPROTO	(1 + RMC_GENERR_RMC_INTERNAL)
								/* The RMC daemon does not support any of    */
								/* the protocol versions specified by the    */
								/* RMCAPI                                    */
								/* ... no arguments                          */

#define RMC_ERESOURCEMOVED		(2 + RMC_GENERR_RMC_INTERNAL)
								/* A resource has moved; the command must be */
								/* redirected.                               */
								/* ... no arguments                          */


/*****************************************************************************/
/**                                                                         **/
/**      Command specification errors                                       **/
/**                                                                         **/
/*****************************************************************************/

#define RMC_GENERR_CMD_SPEC		0x30000		/* Command specification error   */
											/* category                      */

#define RMC_EOKBUTOTHERERROR	(1 + RMC_GENERR_CMD_SPEC)
								/* This command was correctly specified but  */
								/* another command in the ordered command    */
								/* group was not                             */
								/* ... no arguments                          */

#define RMC_ECLASSNOTDEFINED	(2 + RMC_GENERR_CMD_SPEC)
								/* The specified class name is not defined   */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ESELSTRBADNODNUM	(17 + RMC_GENERR_CMD_SPEC)
								/* select string does not contain any node   */
								/* numbers within the range 1-N, where N is  */
								/* the highest configured cluster node number*/
								/* ... arg1 = highest configured node number */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = highest configured node number */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg3 = select string                  */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ESELSTRBADNODID		(18 + RMC_GENERR_CMD_SPEC)
								/* select string does not contain any        */
								/* configured node IDs                       */
								/* ... arg1 = select string                  */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */


#define RMC_ESELSTRBADNEXPR		(20 + RMC_GENERR_CMD_SPEC)
								/* select string contains an improper        */
								/* expression involving a node number, i.e.  */
								/* the node number is not an integral value  */
								/* ... arg1 = select string                  */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EMISSINGCLASSNAME	(24 + RMC_GENERR_CMD_SPEC)
								/* The class name has not been specified     */
								/* ... no arguments                          */

#define RMC_ECMDNOTSUPPORTED	(30 + RMC_GENERR_CMD_SPEC)
								/* the command is not supported by the       */
								/* specified class                           */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EDUPATTRNAM			(31 + RMC_GENERR_CMD_SPEC)
								/* attribute name is a duplicate             */
								/* ... arg1 = array index of duplicate attr  */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = attribute name                 */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EEXPRNODATTRNAME	(32 + RMC_GENERR_CMD_SPEC)
								/* expression does not contain a dynamic     */
								/* attribute name                            */
								/* ... arg1 = expression                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EEXPRMISSING		(33 + RMC_GENERR_CMD_SPEC)
								/* expression is missing from command        */
								/* ... no arguments                          */

#define RMC_ERAEXPRISNULL		(34 + RMC_GENERR_CMD_SPEC)
								/* re-arm expression is a NULL string        */
								/* ... no arguments                          */

#define RMC_EEXPRDIFFATTRS		(35 + RMC_GENERR_CMD_SPEC)
								/* expression and re-arm expression contain  */
								/* different attribute names                 */
								/* ... arg1 = attribute name                 */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = attribute name                 */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EATTRMISSING		(36 + RMC_GENERR_CMD_SPEC)
								/* an attribute name is missing from the     */
								/* attribute array                           */
								/* ... arg1 = array index of missing attr    */
								/* ... type = CU_ERROR_ARG_INT               */

#define RMC_EBADATTRNAM			(37 + RMC_GENERR_CMD_SPEC)
								/* attribute name is not defined             */
								/* ... arg1 = array index of invalid attr    */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = attribute name                 */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOREGEVENT			(38 + RMC_GENERR_CMD_SPEC)
								/* event not registered; validity check      */
								/* only requested                            */
								/* ... no arguments                          */

#define RMC_EBADREGID			(39 + RMC_GENERR_CMD_SPEC)
								/* specified registration ID does not match  */
								/* a registered event for the session        */
								/* ... no arguments                          */

#define RMC_ENOPATTRSDEFINED	(40 + RMC_GENERR_CMD_SPEC)
								/* no persistent attributes are defined for  */
								/* the specified class.                      */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENODATTRSDEFINED	(41 + RMC_GENERR_CMD_SPEC)
								/* no dynamic attributes are defined for     */
								/* the specified class.                      */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOCPATTRSDEFINED	(42 + RMC_GENERR_CMD_SPEC)
								/* no class persistent attributes are        */
								/* defined for the specified class.          */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOCDATTRSDEFINED	(43 + RMC_GENERR_CMD_SPEC)
								/* no class dynamic attributes are           */
								/* defined for the specified class.          */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EBADRSRCHANDLE		(44 + RMC_GENERR_CMD_SPEC)
								/* the specified resource handle is invalid  */
								/* ... no arguments                          */

#define RMC_ENOLOCATORATTR		(45 + RMC_GENERR_CMD_SPEC)
								/* the locator attribute was not included    */
								/* in the define resource command for the    */
								/* specified class.                          */
								/* ... arg1 = locator attribute name         */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EBADATTRTYPE		(46 + RMC_GENERR_CMD_SPEC)
								/* specified attribute type does not match   */
								/* defined type for specified attribute      */
								/* ... arg1 = array index of invalid attr    */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = attribute name                 */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENORSRCFORCMD		(47 + RMC_GENERR_CMD_SPEC)
								/* the command specified one or more         */
								/* resources but the specified class does    */
								/* not support resources                     */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EEXPRNOTFORQUANTUM	(48 + RMC_GENERR_CMD_SPEC)
								/* expression contains more than just a      */
								/* single attribute name token and the named */
								/* attribute is a quantum variable type      */
								/* ... arg1 = expression                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ERAEXPRNOTALLOWED	(49 + RMC_GENERR_CMD_SPEC)
								/* a re-arm expression was specified with    */
								/* a dynamic attribute that is a quantum     */
								/* variable type                             */
								/* ... arg1 = expression                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOQUERYQUANTUM		(50 + RMC_GENERR_CMD_SPEC)
								/* a query dynamic attribute command         */
								/* specified an attribute that is of         */
								/* quantum variable type. Quantum dynamic    */
								/* attributes cannot be queried              */
								/* ... arg1 = array index of quantum attr    */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = attribute name                 */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EALLQUANTUM			(51 + RMC_GENERR_CMD_SPEC)
								/* a query dynamic attribute command         */
								/* indicated that all attributes were to be  */
								/* returned, but all dynamic attributes are  */
								/* of quantum variable type. Quantum dynamic */
								/* attributes cannot be queried              */
								/* ... arg1 = name of associated class       */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOATTRIBUTES		(52 + RMC_GENERR_CMD_SPEC)
								/* the command specified no attributes but   */
								/* this command requires that at least one   */
								/* attribute be specified.                   */
								/* ... arg1 = name of associated class       */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EMAYNOTSETPATTRS	(53 + RMC_GENERR_CMD_SPEC)
								/* persistent attributes of a MtypDivided    */
								/* class itself cannot be set                */
								/* ... arg1 = name of class                  */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOVALOTHERERROR	(54 + RMC_GENERR_CMD_SPEC)
								/* This command could not be validated since */
								/* a previous command in the ordered         */
								/* command group was incorrectly specified   */
								/* ... no arguments                          */

#define RMC_EBADSDUSEARG		(55 + RMC_GENERR_CMD_SPEC)
								/* an invalid sd_use argument was specified  */
								/* ... no arguments                          */

#define RMC_EBADNAMECOUNT		(56 + RMC_GENERR_CMD_SPEC)
								/* a non-zero name count was specified but   */
								/* the remaining command arguments require   */
								/* that it be zero                           */
								/* ... no arguments                          */

#define RMC_ESDNOTDEFINED		(57 + RMC_GENERR_CMD_SPEC)
								/* No SDs for the use specified in the       */
								/* command are defined for this class        */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EATTRNOTSD			(58 + RMC_GENERR_CMD_SPEC)
								/* attribute name is not an SD data type     */
								/* ... arg1 = array index of invalid attr    */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = attribute name                 */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EACTIONMISSING		(59 + RMC_GENERR_CMD_SPEC)
								/* an action name is missing from the        */
								/* action array                              */
								/* ... arg1 = array index of missing action  */
								/* ... type = CU_ERROR_ARG_INT               */

#define RMC_EBADACTIONNAM		(60 + RMC_GENERR_CMD_SPEC)
								/* action name is not defined                */
								/* ... arg1 = array index of invalid action  */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = action name                    */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOACTIONSDINPUT	(61 + RMC_GENERR_CMD_SPEC)
								/* the specified action does not have a      */
								/* defined SD input                          */
								/* ... arg1 = array index of invalid action  */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = action name                    */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOACTIONSDRESPONSE	(62 + RMC_GENERR_CMD_SPEC)
								/* the specified action does not have a      */
								/* defined SD response                       */
								/* ... arg1 = array index of invalid action  */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = action name                    */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EBADVVUSEARG		(63 + RMC_GENERR_CMD_SPEC)
								/* an invalid vv_use argument was specified  */
								/* ... no arguments                          */

#define RMC_EAACNOTDEFINED		(64 + RMC_GENERR_CMD_SPEC)
								/* No attributes, actions with defined       */
								/* inputs or commands with defined inputs    */
								/* for the use specified in the command      */
								/* are defined for this class                */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EBADLOCATORVALUE	(65 + RMC_GENERR_CMD_SPEC)
								/* the locator attribute is of array type    */
								/* and does not contain just one element     */
								/* ... arg1 = locator attribute name         */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ESELSTRNOSELECT		(66 + RMC_GENERR_CMD_SPEC)
								/* select string contains attributes that    */
								/* are not all defined for any variety of    */
								/* the resource; no resources can be         */
								/* selected                                  */
								/* ... arg1 = select string                  */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ESELSTRBADNAMEXPR	(67 + RMC_GENERR_CMD_SPEC)
								/* select string contains an improper        */
								/* expression involving a node name, i.e.    */
								/* the node name is not a string value       */
								/* ... arg1 = select string                  */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EINVALSCOPE			(68 + RMC_GENERR_CMD_SPEC)
								/* Requested scope does not match curent     */
								/* daemon cluster configuration              */
								/* ... no arguments                          */

#define RMC_EINVALNODENAMEARG	(69 + RMC_GENERR_CMD_SPEC)
								/* a command argument specified a node name  */
								/* but the node name is not a configured     */
								/* node name                                 */
								/* ... arg1 = invalide node name             */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOCLUSTERNODES		(70 + RMC_GENERR_CMD_SPEC)
								/* The command specified a resource class    */
								/* that is not supported by any of the       */
								/* currently configured cluster nodes or     */
								/* there are no configured cluster nodes.    */
								/* ... no arguments                          */

#define RMC_ENOTSUBDIVIDED		(71 + RMC_GENERR_CMD_SPEC)
								/* The command specified a node name list    */
								/* argument but the specified resource class */
								/* is not of the Subdivided Management style.*/
								/* The node name list argument may only be   */
								/* used with resource classes that are       */
								/* managed using the Subdivided Management   */
								/* style.                                    */
								/* ... no arguments                          */

#define RMC_EINVALLOCATORVALUE	(72 + RMC_GENERR_CMD_SPEC)
								/* the locator attribute value is not a      */
								/* configured Node ID.                       */
								/* ... arg1 = locator attribute name         */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EACCESSFORSESSION	(73 + RMC_GENERR_CMD_SPEC)
								/* the specified resource class cannot be    */
								/* accessed from a session in Distributed    */
								/* Management scope                          */
								/* ... arg1 = resource class name            */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOAPDATTR			(74 + RMC_GENERR_CMD_SPEC)
								/* the ActivePeerDomain attribute was not    */
								/* included in the define resource command   */
								/* for the  specified class.                 */
								/* ... arg1 = APD attribute name             */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EBADAPDATTRVAL		(75 + RMC_GENERR_CMD_SPEC)
								/* the value of the ActivePeerDomain         */
								/* attribute is not a configured Peer Domain */
								/* name.                                     */
								/* ... arg1 = APD attribute name             */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOTGLOBALIZED		(76 + RMC_GENERR_CMD_SPEC)
								/* The command specified a peer domain name  */
								/* list argument but the specified resource  */
								/* class is not of the Globalized Management */
								/* style. The peer domain name list argument */
								/* may only be used with resource classes    */
								/* that are managed using the Globalized     */
								/* Management style.                         */
								/* ... no arguments                          */

#define RMC_EINVALAPDNAMEARG	(77 + RMC_GENERR_CMD_SPEC)
								/* a command argument specified a peer       */
								/* domain name but the peer domain name is   */
								/* not an active peer domain name            */
								/* ... arg1 = invalide peer domain name      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOTDMSCOPE			(78 + RMC_GENERR_CMD_SPEC)
								/* The command specified a peer domain name  */
								/* list argument but the session is not in   */
								/* Distributed Management session scope.     */
								/* The peer domain name list argument may    */
								/* only be used when the session scope is    */
								/* Distributed Management.                   */
								/* ... no arguments                          */

#define RMC_EEXPRNOATTRNAME		(79 + RMC_GENERR_CMD_SPEC)
								/* expression does not contain an            */
								/* attribute name                            */
								/* ... arg1 = expression                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EEXPRPATTRNOSUP		(80 + RMC_GENERR_CMD_SPEC)
								/* expression contains a persistent          */
								/* attribute not supported in expressions    */
								/* ... arg1 = expression                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EEXPRPTYPENOSUP		(81 + RMC_GENERR_CMD_SPEC)
								/* expression contains a persistent          */
								/* attribute of type resource handle         */
								/* ... arg1 = expression                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EINVALPERM			(82 + RMC_GENERR_CMD_SPEC)
								/* the permission argument contains no       */
								/* valid permission bits                     */
								/* ... arg1 = permission argument            */
								/* ... type = CU_ERROR_ARG_INT               */

#define RMC_EINVALLISTUSAGE		(83 + RMC_GENERR_CMD_SPEC)
								/* the list usage argument is not valid      */
								/* ... arg1 = list usage argument            */
								/* ... type = CU_ERROR_ARG_INT               */

#define RMC_EACLTYPETARGET		(84 + RMC_GENERR_CMD_SPEC)
								/* the ACL type argument is not valid for    */
								/* the target of the command                 */
								/* ... arg1 = ACL type argument              */
								/* ... type = CU_ERROR_ARG_INT               */

#define RMC_EINVALACLTYPE		(85 + RMC_GENERR_CMD_SPEC)
								/* the ACL type argument is not valid        */
								/* ... arg1 = ACL type argument              */
								/* ... type = CU_ERROR_ARG_INT               */

#define RMC_EACLFLAGTYPE		(86 + RMC_GENERR_CMD_SPEC)
								/* the ACL flag argument specifies to use    */
								/* the Resource Shared ACL, but the          */
								/* specified ACL type is not Resource nor    */
								/* Resource Initial                          */
								/* ... no arguments                          */

#define RMC_ENOACLALLOWED		(87 + RMC_GENERR_CMD_SPEC)
								/* the ACL flag argument indicates to use    */
								/* the Resource Shared ACL, but an ACL was   */
								/* also specified                            */
								/* ... no arguments                          */

#define RMC_EINVALACL			(88 + RMC_GENERR_CMD_SPEC)
								/* the specified ACL is not valid            */
								/* ... no arguments                          */

#define RMC_EQUALWITHNOEXPR		(89 + RMC_GENERR_CMD_SPEC)
								/* expression contains only a qualifier      */
								/* ... arg1 = qualifier                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EQUALWITHNOBLANK	(90 + RMC_GENERR_CMD_SPEC)
								/* expression string contains a qualifier    */
								/* but there is no white space between the   */
								/* expression and the qualifier              */
								/* ... arg1 = expression                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EUNDEFINEDQUAL		(91 + RMC_GENERR_CMD_SPEC)
								/* expression string contains an undefined   */
								/* qualifier                                 */
								/* ... arg1 = qualifier                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EINVALQUALARG		(92 + RMC_GENERR_CMD_SPEC)
								/* qualifier contains an invalid argument    */
								/* ... arg1 = qualifier                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EMISSINGQUALARG		(93 + RMC_GENERR_CMD_SPEC)
								/* qualifier is missing an argument          */
								/* ... arg1 = qualifier                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ECDAACCESS			(94 + RMC_GENERR_CMD_SPEC)
								/* Message number 2610-308                   */
								/* Permission denied to access a specified   */
								/* resource when fetching CDA definitions    */
								/* ... arg1 = Network Identity               */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = permission character           */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg3 = Resource Class name            */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg4 = node name                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg5 = Resource Handle                */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/*                                           */
								/* Message number 2610-309                   */
								/* Permission denied to access the resource  */
								/* class when fetching CDA definitions       */
								/* ... arg1 = Network Identity               */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = permission character           */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg3 = Resource Class name            */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg4 = node name                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ECDAQUERY			(95 + RMC_GENERR_CMD_SPEC)
								/* Error detected when querying CDA          */
								/* definitions. Error code values:           */
								/* 1 - xxxx                                  */
								/* ... arg1 = Error code                     */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = node name                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ECDAVALUES			(96 + RMC_GENERR_CMD_SPEC)
								/* Unexpected values returned when querying  */
								/* CDA definitions. Error code values:       */
								/* 1 - incorrect SD size                     */
								/* 2 - incorrect SD field data type          */
								/* 3 - missing CDA name                      */
								/* 4 - invalid CDA ID                        */
								/* 5 - dupilcate CDA name                    */
								/* 6 - not all obtained values match         */
								/* ... arg1 = Error code                     */
								/* ... type = CU_ERROR_ARG_INT               */

#define RMC_EEXPRMULTATTR		(97 + RMC_GENERR_CMD_SPEC)
								/* expression contains more than just one,   */
								/* distinct attribute name and the version   */
								/* of the RMCAPI does not support multiple,  */
								/* distinct attribute names in the           */
								/* expression                                */
								/* ... arg1 = expression                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EQUALNOTTERM		(98 + RMC_GENERR_CMD_SPEC)
								/* expression string contains a qualifier    */
								/* that is not properly terminated           */
								/* ... arg1 = Qualifier                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */



/*****************************************************************************/
/**                                                                         **/
/**      Resource access errors                                             **/
/**                                                                         **/
/*****************************************************************************/

#define RMC_GENERR_RESOURCE		0x40000		/* Resource access error         */
											/* category                      */

#define RMC_ERSRCNOTDEFINED		(1 + RMC_GENERR_RESOURCE)
								/* The resource indicated by the resource    */
								/* handle in the response is not defined     */
								/* ... no arguments                          */

#define RMC_ERSRCUNDEFINED		(2 + RMC_GENERR_RESOURCE)
								/* The resource indicated by the resource    */
								/* handle in the response has been undefined */
								/* ... no arguments                          */

#define RMC_ESHAREDMEMORY		(3 + RMC_GENERR_RESOURCE)
								/* The shared memory used to monitor the     */
								/* resource specified by the resource handle */
								/* in the response is no longer valid        */
								/* ... no arguments                          */

#define RMC_ERSRCSTALE			(4 + RMC_GENERR_RESOURCE)
								/* The resource indicated by the resource    */
								/* handle in the response is stale; the      */
								/* resource manager supplying the resource   */
								/* has terminated. The remaining data in the */
								/* response represents the last known values */
								/* ... no arguments                          */

#define RMC_EEVALUATIONERROR	(5 + RMC_GENERR_RESOURCE)
								/* The evaluation of the dynamic attribute   */
								/* of the resource specified by the resource */
								/* handle resulted in an error               */
								/* ... arg1 = expr evaluation error number   */
								/* ...        1 = divide by 0                */
								/* ...        2 = invalid SD array index     */
								/* ...        3 = array index is out of      */
								/* ...            bounds                     */
								/* ...        4 = SD element ID is greater   */
								/* ...            than the number of         */
								/* ...            elements present           */
								/* ...        5 = ".." operator used where   */
								/* ...            the left oparand is        */
								/* ...            greater than the right     */
								/* ...     >100 = unexpected evaluation      */
								/* ...            error                      */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = attribute name                 */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */


#define RMC_EMISSINGPATTRVALUES	(6 + RMC_GENERR_RESOURCE)
								/* Not all of the requested persistent       */
								/* attribute values could be obtained from   */
								/* the resource specified by the resource    */
								/* handle or from the class specified by the */
								/* class name. The count in the response     */
								/* specifies how many are returned           */
								/* ... arg1 = number of attribute values     */
								/* ...        not returned                   */
								/* ... type = CU_ERROR_ARG_INT               */

#define RMC_ENODENOTAVAILABLE	(7 + RMC_GENERR_RESOURCE)
								/* The command for the resource or resource  */
								/* class specified in the response could not */
								/* be executed on the node specified by      */
								/* error arg1; the node is not currently in  */
								/* the cluster.                              */
								/* ... arg1 = name of unavailable node       */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENORSRCSFOUND		(8 + RMC_GENERR_RESOURCE)
								/* No resources could be found using the     */
								/* select string specified in the command    */
								/* ... no arguments                          */

#define RMC_ENOSELECTDONE		(9 + RMC_GENERR_RESOURCE)
								/* Resource selection could not be           */
								/* performed using the select string         */
								/* specified in the command                  */
								/* ... no arguments                          */

#define RMC_ERMNOTAVAILABLE		(10 + RMC_GENERR_RESOURCE)
								/* In cluster mode:                          */
								/* The command for the resource or resource  */
								/* class specified in the response could not */
								/* be executed on the node specified by      */
								/* error arg2; the Resource Manager named    */
								/* by arg1 is not available.                 */
								/* ... arg1 = Resource Manager name          */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = number or name of unavailable  */
								/*            node                           */
								/* ... type = CU_ERROR_ARG_INT or            */
								/*            CU_ERROR_ARG_CHAR_STR          */
								/*                                           */
								/* In stand-alone mode:                      */
								/* The command for the resource or resource  */
								/* class specified in the response could not */
								/* be executed; the Resource Manager named   */
								/* by arg1 is not available.                 */
								/* ... arg1 = Resource Manager name          */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ERMTERMWITHRSP		(11 + RMC_GENERR_RESOURCE)
								/* In cluster mode:                          */
								/* The command for the resource or resource  */
								/* class specified in the response could not */
								/* be completed on the node specified by     */
								/* error arg2; the Resource Manager named    */
								/* by arg1 has terminated. A partial         */
								/* response was previously returned.         */
								/* ... arg1 = Resource Manager name          */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = number or name of unavailable  */
								/*            node                           */
								/* ... type = CU_ERROR_ARG_INT or            */
								/*            CU_ERROR_ARG_CHAR_STR          */
								/*                                           */
								/* In stand-alone mode:                      */
								/* The command for the resource or resource  */
								/* class specified in the response could not */
								/* be completed; the Resource Manager named  */
								/* by arg1 has terminated. A partial         */
								/* response was previously returned.         */
								/* ... arg1 = Resource Manager name          */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ERMTERMWITHNORSP	(12 + RMC_GENERR_RESOURCE)
								/* In cluster mode:                          */
								/* The command for the resource or resource  */
								/* class specified in the response could not */
								/* be completed on the node specified by     */
								/* error arg2; the Resource Manager named    */
								/* by arg1 has terminated. While no response */
								/* was returned, the command may have        */
								/* executed prior to RM termination.         */
								/* ... arg1 = Resource Manager name          */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = number or name of unavailable  */
								/*            node                           */
								/* ... type = CU_ERROR_ARG_INT or            */
								/*            CU_ERROR_ARG_CHAR_STR          */
								/*                                           */
								/* In stand-alone mode:                      */
								/* The command for the resource or resource  */
								/* class specified in the response could not */
								/* be completed; the Resource Manager named  */
								/* by arg1 has terminated. While no response */
								/* was returned, the command may have        */
								/* executed prior to RM termination.         */
								/* ... arg1 = Resource Manager name          */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOENUMRSP			(13 + RMC_GENERR_RESOURCE)
								/* A Resource Manager terminated while       */
								/* attempting to enumerate resources for     */
								/* this command. If an FFDC ID is present it */
								/* can be used to obtain more information    */
								/* about the error. Additional responses may */
								/* still be returned for this command.       */
								/* ... no arguments                          */

#define RMC_EENUMERROR			(14 + RMC_GENERR_RESOURCE)
								/* An error was detected when attempting to  */
								/* enumerate resources for this command.     */
								/* If an FFDC ID is present it can be used   */
								/* to obtain more information about the      */
								/* error. Additional responses may still be  */
								/* returned for this command.                */
								/* ... no arguments                          */

#define RMC_ENODESCRIPTIONS		(15 + RMC_GENERR_RESOURCE)
								/* Descriptions were requested by this       */
								/* command for the specified resource class  */
								/* but cannot be returned; descriptions are  */
								/* not currently available. All other        */
								/* requested information is in the response. */
								/* ... arg1 = Resource Class name            */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EACCESS				(16 + RMC_GENERR_RESOURCE)
								/* Message number 2610-418 (deprecated)      */
								/* Permission denied to access the resources */
								/* or resource class specified in this       */
								/* command.                                  */
								/* ... no arguments                          */
								/*                                           */
								/* Message number 2610-440                   */
								/* Permission denied to access a resource    */
								/* specified in this command                 */
								/* ... arg1 = Network Identity               */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = permission character           */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg3 = Resource Class name            */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg4 = node name                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg5 = Resource Handle                */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/*                                           */
								/* Message number 2610-441                   */
								/* Permission denied to access the resource  */
								/* class specified in this command           */
								/* ... arg1 = Network Identity               */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = permission character           */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg3 = Resource Class name            */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg4 = node name                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENODEOUT			(17 + RMC_GENERR_RESOURCE)
								/* The resource or resource class specified  */
								/* in the response is no longer available on */
								/* the node specified by error arg1; the     */
								/* node has left the cluster                 */
								/* ... arg1 = name of node                   */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EDATTRNOTSUPPORTED	(18 + RMC_GENERR_RESOURCE)
								/* The dynamic attribute specified in the    */
								/* expression(s) supplied in the event       */
								/* registration command is not supported in */
								/* the resource specified by the resource    */
								/* handle or in the class specified by the   */
								/* class name.                               */
								/* ... no arguments                          */

#define RMC_EMISSINGDATTRVALUES	(19 + RMC_GENERR_RESOURCE)
								/* Not all of the requested dynamic          */
								/* attribute values could be obtained from   */
								/* the resource specified by the resource    */
								/* handle or from the class specified by the */
								/* class name. The count in the response     */
								/* specifies how many are returned.          */
								/* ... arg1 = number of attribute values     */
								/* ...        not returned                   */
								/* ... type = CU_ERROR_ARG_INT               */

#define RMC_ERSRCNOTAVAILABLE	(20 + RMC_GENERR_RESOURCE)
								/* The resource or resource class specified  */
								/* in the response is not currently          */
								/* available on the node specified by error  */
								/* arg1.                                     */
								/* ... arg1 = name of node                   */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EMONITRINGSUSPENDED	(21 + RMC_GENERR_RESOURCE)
								/* Monitoring of the resource indicated by   */
								/* the resource handle in the response is    */
								/* temporarily suspended; the monitoring     */
								/* location is changing.                     */
								/* ... no arguments                          */

#define RMC_EMONITRINGNOTSTARTD	(22 + RMC_GENERR_RESOURCE)
								/* Monitoring of the resource indicated by   */
								/* the resource handle in the response has   */
								/* not yet started; a response is pending    */
								/* from the resource manager.                */
								/* ... no arguments                          */

#define RMC_ECLASSNOTINSTALLED	(23 + RMC_GENERR_RESOURCE)
								/* The resource class specified, explicitly  */
								/* or implicitly, in the response is not     */
								/* installed on the node specified by error  */
								/* arg1.                                     */
								/* ... arg1 = name of node                   */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ENOENUMNODE			(24 + RMC_GENERR_RESOURCE)
								/* Cannot enumerate resources for this       */
								/* command on the node specified by arg1;    */
								/* the node is not currently in the cluster. */
								/* Additional responses may  still be        */
								/* returned for this command.                */
								/* ... arg1 = name of unavailable node       */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EMONITRINGNODATA	(25 + RMC_GENERR_RESOURCE)
								/* Monitoring of the resource indicated by   */
								/* the resource handle in the response has   */
								/* started but data is not yet available     */
								/* from the resource manager.                */
								/* ... no arguments                          */

#define RMC_EATTRNOTSUPPORTED	(26 + RMC_GENERR_RESOURCE)
								/* The attribute specified in the            */
								/* expression(s) supplied in the event       */
								/* registration command is not supported in  */
								/* the resource specified by the resource    */
								/* handle or in the class specified by the   */
								/* class name.                               */
								/* ... no arguments                          */

#define RMC_ENODEFUNCLEVEL		(27 + RMC_GENERR_RESOURCE)
								/* The resource or resource class specified  */
								/* in the response cannot be accessed on     */
								/* the node specified by error arg1; the     */
								/* node is not operating at the necessary    */
								/* functional level for this command.        */
								/* ... arg1 = name of node                   */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EDOMAINFUNCLEVEL	(28 + RMC_GENERR_RESOURCE)
								/* The resource or resource class specified  */
								/* in the response cannot be accessed; the   */
								/* domain is not operating at the necessary  */
								/* functional level for this command.        */
								/* ... arg1 = name of peer domain            */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_ESETACLONDEFINE		(29 + RMC_GENERR_RESOURCE)
								/* The resource was successfully defined but */
								/* the Resource Initial ACL could not be set */
								/* on the resource specified by the resource */
								/* handle in the response. The caller must   */
								/* undefine this resource immediately !!!    */
								/* ... no arguments                          */

#define RMC_EGETACL				(30 + RMC_GENERR_RESOURCE)
								/* The ACL specified by the command          */
								/* arguments could not be obtained from      */
								/* either the resource indicated by the      */
								/* resource handle in the response or from   */
								/* the resource class indicated by the class */
								/* name in the response.                     */
								/* ... no arguments                          */

#define RMC_ESETACL				(31 + RMC_GENERR_RESOURCE)
								/* The ACL specified by the command          */
								/* arguments could not be set into           */
								/* either the resource indicated by the      */
								/* resource handle in the response or into   */
								/* the resource class indicated by the class */
								/* name in the response.                     */
								/* ... no arguments                          */

#define RMC_EACTIONNOTDEFINED	(32 + RMC_GENERR_RESOURCE)
								/* Message number 2610-442                   */
								/* Resource action specified in this command */
								/* is not defined on the indicated node      */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = node name                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/*                                           */
								/* Message number 2610-443                   */
								/* Class action specified in this command    */
								/* is not defined on the indicated node      */
								/* ... arg1 = class name                     */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = node name                      */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */

#define RMC_EDATTRVALUESMISSING	(33 + RMC_GENERR_RESOURCE)
								/* Not all of the requested dynamic          */
								/* attribute values could be obtained from   */
								/* the resource specified by the resource    */
								/* handle or from the class specified by the */
								/* class name. Either the number of          */
								/* indicated attributes are not being        */
								/* monitored or the number of indicated      */
								/* attributes have data pending. The count   */
								/* in the response specifies how many are    */
								/* returned.                                 */
								/* ... arg1 = number of attributes not being */
								/* ...        monitored                      */
								/* ... type = CU_ERROR_ARG_INT               */
								/* ... arg2 = number of attributes with data */
								/* ...        pending                        */
								/* ... type = CU_ERROR_ARG_INT               */


/*****************************************************************************/
/**                                                                         **/
/**      Errors in expression specification                                 **/
/**                                                                         **/
/**      N.B. the lower 16 bits of an error in this category is             **/
/**      specified by one of the CU_E* error code definitions found         **/
/**      in the ct_cu.h header file                                         **/
/**                                                                         **/
/*****************************************************************************/

#define RMC_GENERR_EXPR			0x50000		/* expression specification      */
											/* error category                */

/*****************************************************************************/
/**                                                                         **/
/**      Errors in select string specification                              **/
/**                                                                         **/
/**      N.B. the lower 16 bits of an error in this category is             **/
/**      specified by one of the CU_E* error code definitions found         **/
/**      in the ct_cu.h header file                                         **/
/**                                                                         **/
/*****************************************************************************/

#define RMC_GENERR_SELECT		0x60000		/* Select string specification   */
											/* error category                */


/*****************************************************************************/
/**                                                                         **/
/**      Security errors                                                    **/
/**                                                                         **/
/**      N.B. These error codes are not seen by RMCAPI clients.  Also,      **/
/**      an error message format string need not be returned by the daemon  **/
/**      for these error codes.                                             **/
/**                                                                         **/
/*****************************************************************************/

#define RMC_GENERR_SECURITY		0x70000		/* Security error                */
											/* category                      */

#define RMC_ESUBSECURITY		(1 + RMC_GENERR_SECURITY)
								/* Security service error encountered        */
								/* ... arg1 = security library routine name  */
								/* ... type = CU_ERROR_ARG_CHAR_STR          */
								/* ... arg2 = security library error code    */
								/* ... type = CU_ERROR_ARG_INT               */

#define RMC_EAUTHENTICATE		(2 + RMC_GENERR_SECURITY)
								/* Could not authenticate user               */
								/* ... no arguments                          */

#define RMC_EAUTHORIZATION		(3 + RMC_GENERR_SECURITY)
								/* User not authorized to use RMC            */
								/* ... no arguments                          */

#ifdef __cplusplus
} // end extern "C"
#endif /* __cplusplus */

#endif	/* _H_CT_MCERR */
