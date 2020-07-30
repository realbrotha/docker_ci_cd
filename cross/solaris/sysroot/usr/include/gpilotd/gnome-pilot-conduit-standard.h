/* Generated by GOB (v2.0.11)   (do not edit directly) */

#include <glib.h>
#include <glib-object.h>
#ifndef __GNOME_PILOT_CONDUIT_STANDARD_H__
#define __GNOME_PILOT_CONDUIT_STANDARD_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#include <gnome.h>
#include "gnome-pilot-conduit.h"
#include "gnome-pilot-dbinfo.h"


/*
 * Type checking and casting macros
 */
#define GNOME_TYPE_PILOT_CONDUIT_STANDARD	(gnome_pilot_conduit_standard_get_type())
#define GNOME_PILOT_CONDUIT_STANDARD(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gnome_pilot_conduit_standard_get_type(), GnomePilotConduitStandard)
#define GNOME_PILOT_CONDUIT_STANDARD_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gnome_pilot_conduit_standard_get_type(), GnomePilotConduitStandard const)
#define GNOME_PILOT_CONDUIT_STANDARD_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gnome_pilot_conduit_standard_get_type(), GnomePilotConduitStandardClass)
#define GNOME_IS_PILOT_CONDUIT_STANDARD(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gnome_pilot_conduit_standard_get_type ())

#define GNOME_PILOT_CONDUIT_STANDARD_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gnome_pilot_conduit_standard_get_type(), GnomePilotConduitStandardClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GNOME_PILOT_CONDUIT_STANDARD__
#define __TYPEDEF_GNOME_PILOT_CONDUIT_STANDARD__
typedef struct _GnomePilotConduitStandard GnomePilotConduitStandard;
#endif
struct _GnomePilotConduitStandard {
	GnomePilotConduit __parent__;
	/*< public >*/
	char * db_name;
	guint32 creator_id;
	gboolean slow;
};

/*
 * Class definition
 */
typedef struct _GnomePilotConduitStandardClass GnomePilotConduitStandardClass;
struct _GnomePilotConduitStandardClass {
	GnomePilotConduitClass __parent__;
	/*signal*/int (* copy_to_pilot) (GnomePilotConduitStandard * self, GnomePilotDBInfo * dbinfo);
	/*signal*/int (* copy_from_pilot) (GnomePilotConduitStandard * self, GnomePilotDBInfo * dbinfo);
	/*signal*/int (* merge_to_pilot) (GnomePilotConduitStandard * self, GnomePilotDBInfo * dbinfo);
	/*signal*/int (* merge_from_pilot) (GnomePilotConduitStandard * self, GnomePilotDBInfo * dbinfo);
	/*signal*/int (* synchronize) (GnomePilotConduitStandard * self, GnomePilotDBInfo * dbinfo);
};


/*
 * Public methods
 */
GType	gnome_pilot_conduit_standard_get_type	(void);
char * 	gnome_pilot_conduit_standard_get_db_name	(GnomePilotConduitStandard * self);
void 	gnome_pilot_conduit_standard_set_db_name	(GnomePilotConduitStandard * self,
					char * val);
guint32 	gnome_pilot_conduit_standard_get_creator_id	(GnomePilotConduitStandard * self);
void 	gnome_pilot_conduit_standard_set_creator_id	(GnomePilotConduitStandard * self,
					guint32 val);
gboolean 	gnome_pilot_conduit_standard_get_slow	(GnomePilotConduitStandard * self);
void 	gnome_pilot_conduit_standard_set_slow	(GnomePilotConduitStandard * self,
					gboolean val);
GtkObject * 	gnome_pilot_conduit_standard_new	(char * db_name,
					guint32 creator_id,
					GPilotPilot * pilot);
int 	gnome_pilot_conduit_standard_copy_to_pilot	(GnomePilotConduitStandard * self,
					GnomePilotDBInfo * dbinfo);
int 	gnome_pilot_conduit_standard_copy_from_pilot	(GnomePilotConduitStandard * self,
					GnomePilotDBInfo * dbinfo);
int 	gnome_pilot_conduit_standard_merge_to_pilot	(GnomePilotConduitStandard * self,
					GnomePilotDBInfo * dbinfo);
int 	gnome_pilot_conduit_standard_merge_from_pilot	(GnomePilotConduitStandard * self,
					GnomePilotDBInfo * dbinfo);
int 	gnome_pilot_conduit_standard_synchronize	(GnomePilotConduitStandard * self,
					GnomePilotDBInfo * dbinfo);

/*
 * Signal connection wrapper macros
 */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#define gnome_pilot_conduit_standard_connect__copy_to_pilot(object,func,data)	g_signal_connect(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"copy_to_pilot",(GCallback) __extension__ ({int (* ___copy_to_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___copy_to_pilot; }), (data))
#define gnome_pilot_conduit_standard_connect_after__copy_to_pilot(object,func,data)	g_signal_connect_after(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"copy_to_pilot",(GCallback) __extension__ ({int (* ___copy_to_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___copy_to_pilot; }), (data))
#define gnome_pilot_conduit_standard_connect_data__copy_to_pilot(object,func,data,destroy_data,flags)	g_signal_connect_data(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"copy_to_pilot",(GCallback) __extension__ ({int (* ___copy_to_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___copy_to_pilot; }), (data), (destroy_data), (GConnectFlags)(flags))
#define gnome_pilot_conduit_standard_connect__copy_from_pilot(object,func,data)	g_signal_connect(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"copy_from_pilot",(GCallback) __extension__ ({int (* ___copy_from_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___copy_from_pilot; }), (data))
#define gnome_pilot_conduit_standard_connect_after__copy_from_pilot(object,func,data)	g_signal_connect_after(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"copy_from_pilot",(GCallback) __extension__ ({int (* ___copy_from_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___copy_from_pilot; }), (data))
#define gnome_pilot_conduit_standard_connect_data__copy_from_pilot(object,func,data,destroy_data,flags)	g_signal_connect_data(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"copy_from_pilot",(GCallback) __extension__ ({int (* ___copy_from_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___copy_from_pilot; }), (data), (destroy_data), (GConnectFlags)(flags))
#define gnome_pilot_conduit_standard_connect__merge_to_pilot(object,func,data)	g_signal_connect(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"merge_to_pilot",(GCallback) __extension__ ({int (* ___merge_to_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___merge_to_pilot; }), (data))
#define gnome_pilot_conduit_standard_connect_after__merge_to_pilot(object,func,data)	g_signal_connect_after(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"merge_to_pilot",(GCallback) __extension__ ({int (* ___merge_to_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___merge_to_pilot; }), (data))
#define gnome_pilot_conduit_standard_connect_data__merge_to_pilot(object,func,data,destroy_data,flags)	g_signal_connect_data(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"merge_to_pilot",(GCallback) __extension__ ({int (* ___merge_to_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___merge_to_pilot; }), (data), (destroy_data), (GConnectFlags)(flags))
#define gnome_pilot_conduit_standard_connect__merge_from_pilot(object,func,data)	g_signal_connect(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"merge_from_pilot",(GCallback) __extension__ ({int (* ___merge_from_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___merge_from_pilot; }), (data))
#define gnome_pilot_conduit_standard_connect_after__merge_from_pilot(object,func,data)	g_signal_connect_after(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"merge_from_pilot",(GCallback) __extension__ ({int (* ___merge_from_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___merge_from_pilot; }), (data))
#define gnome_pilot_conduit_standard_connect_data__merge_from_pilot(object,func,data,destroy_data,flags)	g_signal_connect_data(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"merge_from_pilot",(GCallback) __extension__ ({int (* ___merge_from_pilot) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___merge_from_pilot; }), (data), (destroy_data), (GConnectFlags)(flags))
#define gnome_pilot_conduit_standard_connect__synchronize(object,func,data)	g_signal_connect(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"synchronize",(GCallback) __extension__ ({int (* ___synchronize) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___synchronize; }), (data))
#define gnome_pilot_conduit_standard_connect_after__synchronize(object,func,data)	g_signal_connect_after(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"synchronize",(GCallback) __extension__ ({int (* ___synchronize) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___synchronize; }), (data))
#define gnome_pilot_conduit_standard_connect_data__synchronize(object,func,data,destroy_data,flags)	g_signal_connect_data(GNOME_PILOT_CONDUIT_STANDARD(__extension__ ({GnomePilotConduitStandard *___object = (object); ___object; })),"synchronize",(GCallback) __extension__ ({int (* ___synchronize) (GnomePilotConduitStandard * ___fake___self, GnomePilotDBInfo * ___fake___dbinfo, gpointer ___data ) = (func); ___synchronize; }), (data), (destroy_data), (GConnectFlags)(flags))
#else /* __GNUC__ && !__STRICT_ANSI__ */
#define gnome_pilot_conduit_standard_connect__copy_to_pilot(object,func,data)	g_signal_connect(GNOME_PILOT_CONDUIT_STANDARD(object),"copy_to_pilot",(GCallback)(func),(data))
#define gnome_pilot_conduit_standard_connect_after__copy_to_pilot(object,func,data)	g_signal_connect_after(GNOME_PILOT_CONDUIT_STANDARD(object),"copy_to_pilot",(GCallback)(func),(data))
#define gnome_pilot_conduit_standard_connect_data__copy_to_pilot(object,func,data,destroy_data,flags)	g_signal_connect_data(GNOME_PILOT_CONDUIT_STANDARD(object),"copy_to_pilot",(GCallback)(func),(data),(destroy_data),(GConnectFlags)(flags))
#define gnome_pilot_conduit_standard_connect__copy_from_pilot(object,func,data)	g_signal_connect(GNOME_PILOT_CONDUIT_STANDARD(object),"copy_from_pilot",(GCallback)(func),(data))
#define gnome_pilot_conduit_standard_connect_after__copy_from_pilot(object,func,data)	g_signal_connect_after(GNOME_PILOT_CONDUIT_STANDARD(object),"copy_from_pilot",(GCallback)(func),(data))
#define gnome_pilot_conduit_standard_connect_data__copy_from_pilot(object,func,data,destroy_data,flags)	g_signal_connect_data(GNOME_PILOT_CONDUIT_STANDARD(object),"copy_from_pilot",(GCallback)(func),(data),(destroy_data),(GConnectFlags)(flags))
#define gnome_pilot_conduit_standard_connect__merge_to_pilot(object,func,data)	g_signal_connect(GNOME_PILOT_CONDUIT_STANDARD(object),"merge_to_pilot",(GCallback)(func),(data))
#define gnome_pilot_conduit_standard_connect_after__merge_to_pilot(object,func,data)	g_signal_connect_after(GNOME_PILOT_CONDUIT_STANDARD(object),"merge_to_pilot",(GCallback)(func),(data))
#define gnome_pilot_conduit_standard_connect_data__merge_to_pilot(object,func,data,destroy_data,flags)	g_signal_connect_data(GNOME_PILOT_CONDUIT_STANDARD(object),"merge_to_pilot",(GCallback)(func),(data),(destroy_data),(GConnectFlags)(flags))
#define gnome_pilot_conduit_standard_connect__merge_from_pilot(object,func,data)	g_signal_connect(GNOME_PILOT_CONDUIT_STANDARD(object),"merge_from_pilot",(GCallback)(func),(data))
#define gnome_pilot_conduit_standard_connect_after__merge_from_pilot(object,func,data)	g_signal_connect_after(GNOME_PILOT_CONDUIT_STANDARD(object),"merge_from_pilot",(GCallback)(func),(data))
#define gnome_pilot_conduit_standard_connect_data__merge_from_pilot(object,func,data,destroy_data,flags)	g_signal_connect_data(GNOME_PILOT_CONDUIT_STANDARD(object),"merge_from_pilot",(GCallback)(func),(data),(destroy_data),(GConnectFlags)(flags))
#define gnome_pilot_conduit_standard_connect__synchronize(object,func,data)	g_signal_connect(GNOME_PILOT_CONDUIT_STANDARD(object),"synchronize",(GCallback)(func),(data))
#define gnome_pilot_conduit_standard_connect_after__synchronize(object,func,data)	g_signal_connect_after(GNOME_PILOT_CONDUIT_STANDARD(object),"synchronize",(GCallback)(func),(data))
#define gnome_pilot_conduit_standard_connect_data__synchronize(object,func,data,destroy_data,flags)	g_signal_connect_data(GNOME_PILOT_CONDUIT_STANDARD(object),"synchronize",(GCallback)(func),(data),(destroy_data),(GConnectFlags)(flags))
#endif /* __GNUC__ && !__STRICT_ANSI__ */


/*
 * Argument wrapping macros
 */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#define GNOME_PILOT_CONDUIT_STANDARD_PROP_DB_NAME(arg)    	"db_name", __extension__ ({char * z = (arg); z;})
#define GNOME_PILOT_CONDUIT_STANDARD_GET_PROP_DB_NAME(arg)	"db_name", __extension__ ({char * *z = (arg); z;})
#define GNOME_PILOT_CONDUIT_STANDARD_PROP_CREATOR_ID(arg)    	"creator_id", __extension__ ({guint32 z = (arg); z;})
#define GNOME_PILOT_CONDUIT_STANDARD_GET_PROP_CREATOR_ID(arg)	"creator_id", __extension__ ({guint32 *z = (arg); z;})
#define GNOME_PILOT_CONDUIT_STANDARD_PROP_SLOW(arg)    	"slow", __extension__ ({gboolean z = (arg); z;})
#define GNOME_PILOT_CONDUIT_STANDARD_GET_PROP_SLOW(arg)	"slow", __extension__ ({gboolean *z = (arg); z;})
#else /* __GNUC__ && !__STRICT_ANSI__ */
#define GNOME_PILOT_CONDUIT_STANDARD_PROP_DB_NAME(arg)    	"db_name",(char * )(arg)
#define GNOME_PILOT_CONDUIT_STANDARD_GET_PROP_DB_NAME(arg)	"db_name",(char * *)(arg)
#define GNOME_PILOT_CONDUIT_STANDARD_PROP_CREATOR_ID(arg)    	"creator_id",(guint32 )(arg)
#define GNOME_PILOT_CONDUIT_STANDARD_GET_PROP_CREATOR_ID(arg)	"creator_id",(guint32 *)(arg)
#define GNOME_PILOT_CONDUIT_STANDARD_PROP_SLOW(arg)    	"slow",(gboolean )(arg)
#define GNOME_PILOT_CONDUIT_STANDARD_GET_PROP_SLOW(arg)	"slow",(gboolean *)(arg)
#endif /* __GNUC__ && !__STRICT_ANSI__ */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
