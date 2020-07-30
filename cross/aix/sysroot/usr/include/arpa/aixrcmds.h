/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/arpa/aixrcmds.h 1.3                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)35       1.3  src/bos/usr/include/arpa/aixrcmds.h, sockinc, bos530 6/11/04 18:38:37 */

#ifndef _ARPA_AIXRCMDS_H
#define _ARPA_AIXRCMDS_H

/* rportarg structure can be used for adding new arguments to
 * rresvport routines. This should avoid multiple rresvport
 * suffixed routines.
 */
struct rportarg {
	int sameaddr; /* rresvport should bind stderr socket to same
			   addr as stdin - used in case of rshd */
};

#define RPORTARG_INIT {0}

/* rcmdarg structure can be used for adding new arguments
 * to rcmd routines. This should avoid multiple rcmd suffixed
 * routines.
 */
struct rcmdarg {
	int Sameipflag; /* rsh '-S' flag set; rshd stderr IP
			    should be same as what we connected to */
};

#define RCMDARG_INIT {0}

extern int	_check_rhosts_file;
extern int 	netrc_restricted;

extern int	_checkhost(int, char *, char *, int);
extern int	_validuser(FILE *, char *, char *, char *, int);
extern int	_validuser2(int, FILE *, char *, char *, char *, int);
extern int	rcmd(char **, u_short, char *, char *, char *, int *);
extern int	rcmd_r(char **, u_short, char *, char *, char *, int *, 
		struct hostent_data *);
extern int 	rcmd2_r(int, char **, u_short, char *, char *, char *, int *, 
		struct hostent_data *);
extern int 	rcmd2(int, char **, u_short, char *, char *, char *, int *);
extern int 	rcmd3(int, char **, u_short, char *, char *, char *, int *,
		struct rcmdarg *);
extern int 	rresvport3(int, int*, struct rportarg *);
extern int 	rresvport2(int, int*);
extern int	rresvport(int *);

extern int 	ruserok2(int, char *, int , char *, char *);
extern int 	ruserok(char *, int, char *, char *);
extern void	truncate_domain(char *, char *);

extern int 	rexec(char **, int, char *, char *, char *, int *); 
extern int	rexec_r(char **, int, char *, char *, char *, int *, 
		struct hostent_data *);
extern int	check_netrc2(int, char *, char **, char **);
extern int	check_netrc(char *, char **, char **);
extern int 	ruserpass2(int, char *, char **, char **);
extern int	ruserpass(char *, char **, char **);
extern void	mkpwclear(char *, char, char *);
extern void	mkpwunclear(char *, char, char *);

extern int	bindresvport(int, struct sockaddr_in *);
extern int	alreadyreserve(int port);
extern int      rresvport_af(int*, int);
extern int      rcmd_af(char**, unsigned short, const char*, const char*,
                        const char*, int*, int);
extern int      rexec_af(char **, unsigned short, const char *,
                        const char *, const char *, int *, int);


#endif /* _ARPA_AIXRCMDS_H */
