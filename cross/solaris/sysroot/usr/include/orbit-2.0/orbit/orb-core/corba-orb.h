#ifndef CORBA_ORB_H
#define CORBA_ORB_H 1

#include <orbit/orb-core/orb-types.h>
#include <orbit/orb-core/corba-orb-type.h>
#include <orbit/orb-core/corba-typecode-type.h>

G_BEGIN_DECLS

CORBA_ORB CORBA_ORB_init (int                *argc,
			  char              **argv,
			  CORBA_ORBid         orb_identifier,
			  CORBA_Environment  *ev);

#ifdef ORBIT2_INTERNAL_API

void      ORBit_ORB_forw_bind (CORBA_ORB                   orb,
			       CORBA_sequence_CORBA_octet *okey,
			       CORBA_Object                oref,
			       CORBA_Environment          *ev);

guint     ORBit_ORB_idle_init     (CORBA_ORB orb);

void      ORBit_ORB_start_servers (CORBA_ORB orb);

#endif /* ORBIT2_INTERNAL_API */

G_END_DECLS

#endif
