#if !defined(IIIMP_DATA_H)
#define IIIMP_DATA_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <sys/types.h>

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

#if defined(linux) || defined(__FreeBSD__) || defined(__APPLE__)
typedef unsigned char	uchar_t;
typedef unsigned int	uint_t;
#endif /* linux || freebsd */

#include <iiimp-opcode.h>
#include <iiimp-file-operation.h>


#ifdef	__cplusplus
extern "C" {
#endif

#define iiimp_MESSAGE_SIZE_MAX_4 ((1 << 24) - 1)

/* primitive data type */
typedef uint8_t			IIIMP_card7;
typedef uint8_t			IIIMP_card8;
typedef uint16_t		IIIMP_card16;
typedef uint32_t		IIIMP_card32;
typedef uint64_t		IIIMP_card64;
typedef int8_t			IIIMP_int8;
typedef int16_t			IIIMP_int16;
typedef int32_t			IIIMP_int32;

typedef struct {
    size_t		nbyte;
    int			count;
    IIIMP_card16 *	ptr;
} IIIMP_card16_list;

typedef struct {
    size_t		nbyte;
    int			count;
    IIIMP_card32 *	ptr;
} IIIMP_card32_list;


/* composite data type */

typedef struct {
    size_t		nbyte;
    uchar_t *		ptr;
} IIIMP_byte_stream;

typedef struct iiimp_string {
    size_t			nbyte;
    size_t			len;
    IIIMP_card16 *		ptr;
    struct iiimp_string *	next;
} IIIMP_string;

#if defined(USE_OBSOLETE_NS_CODE)
/* obsolete data type -- start */
typedef struct iiimp_utf8string {
    size_t			nbyte;
    size_t			len;
    IIIMP_card8 *		ptr;
    struct iiimp_utf8string *	next;
} IIIMP_utf8string;
/* obsolete data type -- end */
#endif /* USE_OBSOLETE_NS_CODE */

typedef struct {
    size_t		nbyte;
    IIIMP_card32	id;
    IIIMP_card32	feedback;
} IIIMP_feedback_attr;

typedef struct {
    size_t			nbyte;
    int				count;
    IIIMP_feedback_attr *	ptr;
} IIIMP_feedback_attr_list;

typedef struct iiimp_char_with_feedback {
    size_t				nbyte;
    IIIMP_card16			code;
    IIIMP_feedback_attr_list *		feedback_attr;
    struct iiimp_char_with_feedback *	next;
} IIIMP_char_with_feedback;

typedef struct iiimp_operation {
    size_t			nbyte;
    IIIMP_string *		id;
    IIIMP_byte_stream		value;
    struct iiimp_operation *	next;
} IIIMP_operation;

typedef struct iiimp_text	IIIMP_text;

typedef struct iiimp_annotation_value {
    size_t				nbyte;
    IIIMP_int32				start_index;
    IIIMP_int32				end_index;
    IIIMP_int32				length;
    union {
	IIIMP_text *	text;
	IIIMP_string *	string;
    }					v;
    struct iiimp_annotation_value *	next;
} IIIMP_annotation_value;

typedef struct iiimp_annotation {
    size_t			nbyte;
    IIIMP_card32		id;
    size_t			value_nbyte;
    IIIMP_annotation_value *	value;
    struct iiimp_annotation *	next;
} IIIMP_annotation;

struct iiimp_text {
    size_t			nbyte;
    size_t			char_with_feedback_nbyte;
    IIIMP_char_with_feedback *	char_with_feedback;
    size_t			annotation_nbyte;
    IIIMP_annotation *		annotation;
    struct iiimp_text *		next;
};

typedef struct iiimp_imattribute	IIIMP_imattribute;

typedef struct {
    size_t		nbyte;
    IIIMP_string *	type;		/* Application type */
    IIIMP_string *	os_name;	/* Operating system name */
    IIIMP_string *	arch;		/* Operating system architecture */
    IIIMP_string *	version;	/* Operating system version */
    IIIMP_string *	X_display_name;	/* X display name */
    IIIMP_string *	X_server_vendor;/* X service vendor */
} IIIMP_client_descriptor;

typedef struct iiimp_object_descriptor {
    size_t		nbyte;
    int			category;	/* object category */
    size_t		size;		/* object size */
    int			id_pre;		/* predefined attribute id */
    int			id_dyn;		/* dynamically assigned id */
    IIIMP_string *	rdun;		/* reverse domain unique name */
    IIIMP_string *	hrn;		/* human readable name */
    IIIMP_string *	signature;	/* signature */
    IIIMP_string *	user;		/* object user */
    struct iiimp_object_descriptor *		next;
} IIIMP_object_descriptor;

typedef struct {
    size_t		nbyte;
    IIIMP_string *	contents;	/* contents of CCDEF */
} IIIMP_ccdef;

typedef struct iiimp_language {
    size_t			nbyte;
    IIIMP_string *		hrn;	/* human readable name */
    IIIMP_string *		id;	/* language identifier */
    struct iiimp_language *	next;
} IIIMP_language;

/* struct to hold the information of Input Method Engine */
typedef struct iiimp_imeinfo {
    size_t		nbyte;
    IIIMP_card32	enable;		/* identify the status of the ime:
					   enable/disable */
    IIIMP_string *	ime_id;		/* unique identification for the ime
					   (in ASCII) */
    IIIMP_string *	imename;	/* the name of ime */
    IIIMP_string *	version;
    IIIMP_string *	description;	/* can hold the hinting information */
    IIIMP_string *	author;
    IIIMP_string *	copyright;
    IIIMP_string *	reserved1;	/* Padding for future expansion */
    IIIMP_string *	reserved2;
    struct iiimp_imeinfo *	next;
} IIIMP_imeinfo;

typedef struct {
    size_t		nbyte;
    size_t		class_names_nbyte;
    IIIMP_string *	class_names;	/* class_names */
    IIIMP_byte_stream	value;		/* jar file byte stream */
} IIIMP_jarfile_object;

typedef struct iiimp_inputmethod_descriptor {
    size_t		nbyte;
    int			id;		/* Input Method Identifier */
    IIIMP_string *	idname;		/* Input Method name */
    IIIMP_string *	hrn;		/* human readable name */
    size_t		language_nbyte;
    IIIMP_language *	language;	/* supported language list */
    IIIMP_string *	rdun;		/* reverse domain unique name */
    size_t		imeinfo_nbyte; 
    IIIMP_imeinfo *	imeinfo;	/* (Optional) the information of
					   input method engine */
    struct iiimp_inputmethod_descriptor *	next;
} IIIMP_inputmethod_descriptor;

typedef struct {
    size_t		nbyte;
    IIIMP_string *	object;		/* object */
} IIIMP_binaryfile_object;

typedef union {
    void *				any;
    IIIMP_inputmethod_descriptor *	inputmethod_descriptor;
    IIIMP_object_descriptor *		object_descriptor;
    IIIMP_client_descriptor *		client_descriptor;
    IIIMP_ccdef *			ccdef;
    IIIMP_jarfile_object *		jarfile_object;
    IIIMP_binaryfile_object *		binaryfile_object;
    IIIMP_string *			client_group;
    IIIMP_card32_list *			capability;
} IIIMP_imattribute_value;

struct iiimp_imattribute {
    size_t			nbyte;
    int				id;	/* Input Method Attribute ID */
    int				id_pre;	/* predefined attribute id */
    int				id_dyn;	/* predefined attribute id */
    size_t			value_nbyte;
    IIIMP_imattribute_value	value;	/* Input Method Attribute Value */
    struct iiimp_imattribute *	next;	/* pointer to the next attribute */
};

typedef union {
    IIIMP_string *	input_language;
    IIIMP_card32_list *	character_subsets;
    IIIMP_string *	input_method_name;
    IIIMP_card16	input_method;
} IIIMP_icattribute_value;

typedef struct iiimp_icattribute IIIMP_icattribute;

struct iiimp_icattribute {
    size_t			nbyte;
    int				id;
    size_t			value_nbyte;
    IIIMP_icattribute_value	value;	/* Input Method Attribute Value */
    struct iiimp_icattribute *	next;	/* pointer to the next attribute */
};

typedef struct {
    IIIMP_int32		keycode;
    IIIMP_int32		keychar;
    IIIMP_int32		modifier;
    IIIMP_int32		time_stamp;
} IIIMP_keyevent;

typedef struct {
    size_t		nbyte;
    int			count;
    IIIMP_keyevent *	keyevent;
} IIIMP_keyevent_list;

typedef union {
    void *			any;
    IIIMP_string *		string;
    IIIMP_text *		text;
    IIIMP_keyevent_list *	keyevent_list;
} IIIMP_contents_value;

typedef struct {
    size_t			nbyte;
    IIIMP_card32		type;
    size_t			value_nbyte;
    IIIMP_contents_value	value;
} IIIMP_contents;


/* composite data type - file operation */

typedef struct {
    IIIMP_card32		actime;
    IIIMP_card32		modtime;
} IIIMP_file_operation_utimbuf;

typedef struct {
    IIIMP_card32	 	tv_sec0;
    IIIMP_card32		tv_usec0;
    IIIMP_card32		tv_sec1;
    IIIMP_card32		tv_usec1;
} IIIMP_file_operation_timeval;

typedef union {
    IIIMP_card32	file_descriptor_flags;
    IIIMP_card32	file_status_flags;
    struct {
	IIIMP_card16		type;
	IIIMP_card16		whence;
	IIIMP_card32		start;
	IIIMP_card32		len;
    }			flock;
} IIIMP_file_operation_data_fcntl_value;

typedef struct {
    size_t					nbyte;
    IIIMP_file_operation_data_fcntl_value	value;
} IIIMP_file_operation_data_fcntl;

typedef struct {
    IIIMP_card32		tv_sec;
    IIIMP_card32		tv_nsec;
} IIIMP_file_operation_data_timespec;

typedef struct {
    size_t				nbyte;
    IIIMP_card32			mode;
    IIIMP_card32			ino;
    IIIMP_card32			dev;
    IIIMP_card32			rdev;
    IIIMP_card32			nlink;
    IIIMP_string *			user_name;
    IIIMP_card32			uid;
    IIIMP_string *			group_name;
    IIIMP_card32			gid;
    IIIMP_card32			size;
    IIIMP_file_operation_data_timespec	atime;
    IIIMP_file_operation_data_timespec	mtime;
    IIIMP_file_operation_data_timespec	ctime;
    IIIMP_card32			blksize;
    IIIMP_card32			blocks;
} IIIMP_file_operation_data_stat;

typedef struct {
    size_t			nbyte;
    IIIMP_card32		ino;
    IIIMP_card32		off;
    IIIMP_string *		name;
} IIIMP_file_operation_data_dir;

typedef struct {
    IIIMP_card32		file_descriptor;
} IIIMP_file_operation_request_close;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
    IIIMP_card32		mode;
} IIIMP_file_operation_request_creat;

typedef struct {
    IIIMP_card32		file_descriptor;
    IIIMP_card32		length;
} IIIMP_file_operation_request_ftruncate;

typedef struct {
    IIIMP_card32		file_descriptor;
    IIIMP_card32		offset;
    IIIMP_card32		whence;
} IIIMP_file_operation_request_lseek;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
    IIIMP_card32		oflag;
    IIIMP_card32		mode;
} IIIMP_file_operation_request_open;

typedef struct {
    IIIMP_card32		file_descriptor;
    IIIMP_card32		nbyte;
} IIIMP_file_operation_request_read;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
    IIIMP_card32		length;
} IIIMP_file_operation_request_truncate;

typedef struct {
    size_t			nbyte;
    IIIMP_card32		file_descriptor;
    IIIMP_byte_stream		value;
} IIIMP_file_operation_request_write;

typedef struct {
    size_t			nbyte;
    IIIMP_string *	 	existing_path;
    IIIMP_string *		new_path;
} IIIMP_file_operation_request_link;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
} IIIMP_file_operation_request_readlink;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		old_path;
    IIIMP_string *		new_path;
} IIIMP_file_operation_request_rename;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		existing_path;
    IIIMP_string *		new_path;
} IIIMP_file_operation_request_symlink;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
} IIIMP_file_operation_request_unlink;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
    IIIMP_card32		mode;
} IIIMP_file_operation_request_chmod;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
    IIIMP_string *		user_name;
    IIIMP_card32		user_id;
    IIIMP_string *		group_name;
    IIIMP_card32		group_id;
} IIIMP_file_operation_request_chown;

typedef struct {
    IIIMP_card32		file_descriptor;
    IIIMP_card32		mode;
} IIIMP_file_operation_request_fchmod;

typedef struct {
    size_t			nbyte;
    IIIMP_card32		file_descriptor;
    IIIMP_string *		user_name;
    IIIMP_card32		user_id;
    IIIMP_string *		group_name;
    IIIMP_card32		group_id;
} IIIMP_file_operation_request_fchown;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
    IIIMP_card32		mode;
} IIIMP_file_operation_request_lchmod;

typedef IIIMP_file_operation_request_chown	IIIMP_file_operation_request_lchown;

typedef struct {
    size_t				nbyte;
    IIIMP_string *			path;
    IIIMP_file_operation_utimbuf	utimbuf_data;
} IIIMP_file_operation_request_utime;

typedef struct {
    size_t				nbyte;
    IIIMP_string *			path;
    IIIMP_file_operation_timeval	timeval_data;
} IIIMP_file_operation_request_utimes;

typedef struct {
    IIIMP_card32		file_descriptor;
} IIIMP_file_operation_request_fstat;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
} IIIMP_file_operation_request_lstat;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
} IIIMP_file_operation_request_stat;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		path;
    IIIMP_card32		amode;
} IIIMP_file_operation_request_access;

typedef struct {
    IIIMP_card32		directory_handle;
} IIIMP_file_operation_request_closedir;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		dirname;
} IIIMP_file_operation_request_opendir;

typedef struct {
    IIIMP_card32		directory_handle;
} IIIMP_file_operation_request_readdir;

typedef struct {
    IIIMP_card32		directory_handle;
} IIIMP_file_operation_request_rewinddir;

typedef struct {
    IIIMP_card32		directory_handle;
    IIIMP_card32		loc;
} IIIMP_file_operation_request_seekdir;

typedef struct {
    IIIMP_card32		directory_handle;
} IIIMP_file_operation_request_telldir;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		dirname;
    IIIMP_card32		mode;
} IIIMP_file_operation_request_mkdir;

typedef struct {
    size_t			nbyte;
    IIIMP_string *		dirname;
} IIIMP_file_operation_request_rmdir;

typedef struct {
    size_t				nbyte;
    IIIMP_card32			file_descriptor;
    IIIMP_card32			cmd;
    IIIMP_file_operation_data_fcntl *	arg;
} IIIMP_file_operation_request_fcntl;

typedef struct {
    IIIMP_card32		return_value;
    IIIMP_card32		error_number;
} IIIMP_file_operation_result_simple;

typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_close;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_creat;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_ftruncate;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_lseek;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_open;

typedef struct {
    size_t			nbyte;
    IIIMP_card32		error_number;
    IIIMP_byte_stream		value;
} IIIMP_file_operation_result_read;

typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_truncate;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_write;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_link;

typedef struct {
    size_t			nbyte;
    IIIMP_card32		return_value;
    IIIMP_card32		error_number;
    IIIMP_string *		path;
} IIIMP_file_operation_result_readlink;

typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_rename;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_symlink;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_unlink;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_chmod;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_chown;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_fchmod;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_fchown;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_lchmod;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_lchown;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_utime;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_utimes;

typedef struct {
    size_t				nbyte;
    IIIMP_card32			return_value;
    IIIMP_card32			error_number;
    IIIMP_file_operation_data_stat *	stat;
} IIIMP_file_operation_result_stat;

typedef IIIMP_file_operation_result_stat	IIIMP_file_operation_result_fstat;
typedef IIIMP_file_operation_result_stat	IIIMP_file_operation_result_lstat;

typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_access;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_closedir;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_opendir;

typedef struct {
    IIIMP_card32			error_number;
    IIIMP_file_operation_data_dir *	dir;
} IIIMP_file_operation_result_readdir;

typedef struct {
    IIIMP_card32			no_data;	/* not used */
} IIIMP_file_operation_result_rewinddir;

typedef struct {
    IIIMP_card32			no_data;	/* not used */
} IIIMP_file_operation_result_seekdir;

typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_telldir;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_mkdir;
typedef IIIMP_file_operation_result_simple	IIIMP_file_operation_result_rmdir;

typedef struct {
    size_t				nbyte;
    IIIMP_card32			return_value;
    IIIMP_card32			error_number;
    IIIMP_card32			cmd;
    IIIMP_file_operation_data_fcntl * 	arg;
} IIIMP_file_operation_result_fcntl;

typedef union {
    IIIMP_file_operation_request_close		close;
    IIIMP_file_operation_request_creat		creat;
    IIIMP_file_operation_request_ftruncate	ftruncate;
    IIIMP_file_operation_request_lseek		lseek;
    IIIMP_file_operation_request_open		open;
    IIIMP_file_operation_request_read		read;
    IIIMP_file_operation_request_truncate	truncate;
    IIIMP_file_operation_request_write		write;

    IIIMP_file_operation_request_link		link;
    IIIMP_file_operation_request_readlink	readlink;
    IIIMP_file_operation_request_rename		rename;
    IIIMP_file_operation_request_symlink	symlink;
    IIIMP_file_operation_request_unlink		unlink;

    IIIMP_file_operation_request_chmod		chmod;
    IIIMP_file_operation_request_chown		chown;
    IIIMP_file_operation_request_fchmod		fchmod;
    IIIMP_file_operation_request_fchown		fchown;
    IIIMP_file_operation_request_lchown		lchown;
    IIIMP_file_operation_request_utime		utime;
    IIIMP_file_operation_request_utimes		utimes;

    IIIMP_file_operation_request_fstat		fstat;
    IIIMP_file_operation_request_lstat		lstat;
    IIIMP_file_operation_request_stat		stat;
    IIIMP_file_operation_request_access		access;

    IIIMP_file_operation_request_closedir	closedir;
    IIIMP_file_operation_request_opendir	opendir;
    IIIMP_file_operation_request_readdir	readdir;
    IIIMP_file_operation_request_rewinddir	rewinddir;
    IIIMP_file_operation_request_seekdir	seekdir;
    IIIMP_file_operation_request_telldir	telldir;

    IIIMP_file_operation_request_mkdir		mkdir;
    IIIMP_file_operation_request_rmdir		rmdir;

    IIIMP_file_operation_request_fcntl		fcntl;
} IIIMP_file_operation_request_value;


typedef union {
    IIIMP_file_operation_result_simple		simple;

    IIIMP_file_operation_result_close		close;
    IIIMP_file_operation_result_creat		creat;
    IIIMP_file_operation_result_ftruncate	ftruncate;
    IIIMP_file_operation_result_lseek		lseek;
    IIIMP_file_operation_result_open		open;
    IIIMP_file_operation_result_read		read;
    IIIMP_file_operation_result_truncate	truncate;
    IIIMP_file_operation_result_write		write;

    IIIMP_file_operation_result_link		link;
    IIIMP_file_operation_result_readlink	readlink;
    IIIMP_file_operation_result_rename		rename;
    IIIMP_file_operation_result_symlink		symlink;
    IIIMP_file_operation_result_unlink		unlink;

    IIIMP_file_operation_result_chmod		chmod;
    IIIMP_file_operation_result_chown		chown;
    IIIMP_file_operation_result_fchmod		fchmod;
    IIIMP_file_operation_result_fchown		fchown;
    IIIMP_file_operation_result_lchown		lchown;
    IIIMP_file_operation_result_utime		utime;
    IIIMP_file_operation_result_utimes		utimes;

    IIIMP_file_operation_result_fstat		fstat;
    IIIMP_file_operation_result_lstat		lstat;
    IIIMP_file_operation_result_stat		stat;
    IIIMP_file_operation_result_access		access;

    IIIMP_file_operation_result_closedir	closedir;
    IIIMP_file_operation_result_opendir		opendir;
    IIIMP_file_operation_result_readdir		readdir;
    IIIMP_file_operation_result_rewinddir	rewinddir;
    IIIMP_file_operation_result_seekdir		seekdir;
    IIIMP_file_operation_result_telldir		telldir;

    IIIMP_file_operation_result_mkdir		mkdir;
    IIIMP_file_operation_result_rmdir		rmdir;

    IIIMP_file_operation_result_fcntl		fcntl;
} IIIMP_file_operation_result_value;


typedef struct iiimp_file_operation_request {
    size_t					nbyte;
    IIIMP_card32				type;
    size_t					value_nbyte;
    IIIMP_file_operation_request_value		value;
    struct iiimp_file_operation_request *	next;
} IIIMP_file_operation_request;

typedef struct iiimp_file_operation_result {
    size_t					nbyte;
    IIIMP_card32				type;
    size_t					value_nbyte;
    IIIMP_file_operation_result_value		value;
    struct iiimp_file_operation_result *	next;
} IIIMP_file_operation_result;


/* message data type */

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
} IIIMP_simple;

typedef struct {
    IIIMP_card7		opcode;
    int			byte_order;
    int			protocol_version;
    IIIMP_string *	user_name;
    IIIMP_string *	auth;
} IIIMP_connect;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_string *	language;
} IIIMP_connect_reply;

typedef IIIMP_simple	IIIMP_disconnect;

typedef IIIMP_simple	IIIMP_disconnect_reply;

typedef struct {
    IIIMP_card16                hotkey_id;
    IIIMP_card8                 state_flag;  /* #1 disabled */
                                             /* #0 enabled  */

    IIIMP_card8                 action_flag; 
    /* #2 Event forwarding toggle */
    /* #1 Event forwarding ON     */
    /* #0 Event forwarding OFF    */
} HOTKEYCTRL;

typedef struct {
    HOTKEYCTRL                  hotkeyctrl;
    size_t		        nbyte;
    IIIMP_keyevent_list *       hotkeylist;
    IIIMP_string *              label;
} HOTKEY;

typedef struct {
    size_t		nbyte;
    int			count;
    HOTKEY *	        hotkey;
} HOTKEY_LIST;

typedef struct {
    IIIMP_card7         opcode;
    IIIMP_card16        im_id;
    int                 flag;
    HOTKEY_LIST *       hotkeys; 
} IIIMP_register_hotkeys;

typedef struct {
    IIIMP_card7   opcode;
    IIIMP_card16  im_id;
    int           flag;
    HOTKEYCTRL *  hotkeyctrl;
} IIIMP_control_hotkeys;

typedef struct {
    IIIMP_card7    opcode;
    IIIMP_card16   im_id;
    IIIMP_card16   ic_id;
    IIIMP_card16   hotkey_id;
    IIIMP_card16   index;    /* Index of LISTofKEYEVENT in HOTKEY */
} IIIMP_hotkey_notify;

typedef struct {
    IIIMP_card7			opcode;
    IIIMP_card16		im_id;
    IIIMP_keyevent_list *	trigger_on;
    IIIMP_keyevent_list *	trigger_off;
} IIIMP_register_trigger_keys;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    int			flag;
} IIIMP_trigger_notify;

typedef IIIMP_simple	IIIMP_trigger_notify_reply;
typedef IIIMP_simple	IIIMP_hotkey_notify_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_imattribute *	attr_list;
} IIIMP_setimvalues;

typedef IIIMP_simple	IIIMP_setimvalues_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16_list *	attr_list;
} IIIMP_getimvalues;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_imattribute *	attr_list;
} IIIMP_getimvalues_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_icattribute *	attr_list;
} IIIMP_createic;

typedef IIIMP_simple	IIIMP_createic_reply;

typedef IIIMP_simple	IIIMP_destroyic;

typedef IIIMP_simple	IIIMP_destroyic_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_icattribute *	attr_list;
} IIIMP_seticvalues;

typedef IIIMP_simple	IIIMP_seticvalues_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_card16_list *	attr_list;
} IIIMP_geticvalues;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_icattribute *	attr_list;
} IIIMP_geticvalues_reply;

typedef IIIMP_simple	IIIMP_seticfocus;
typedef IIIMP_simple	IIIMP_seticfocus_reply;
typedef IIIMP_simple	IIIMP_unseticfocus;
typedef IIIMP_simple	IIIMP_unseticfocus_reply;
typedef IIIMP_simple	IIIMP_resetic;
typedef IIIMP_simple	IIIMP_resetic_reply;
typedef IIIMP_simple	IIIMP_preedit_start;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_int32		maximum_length;
} IIIMP_preedit_start_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_int32		caret;
    IIIMP_int32		change_first;
    IIIMP_int32		change_length;
    IIIMP_contents *	preedit;
} IIIMP_preedit_draw;

typedef IIIMP_simple	IIIMP_preedit_draw_reply;
typedef IIIMP_simple	IIIMP_preedit_done;
typedef IIIMP_simple	IIIMP_preedit_done_reply;
typedef IIIMP_simple	IIIMP_status_start;
typedef IIIMP_simple	IIIMP_status_start_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_contents *	status;
} IIIMP_status_draw;

typedef IIIMP_simple	IIIMP_status_draw_reply;
typedef IIIMP_simple	IIIMP_status_done;
typedef IIIMP_simple	IIIMP_status_done_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_contents *	contents;
} IIIMP_forward_event;

typedef IIIMP_simple	IIIMP_forward_event_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_contents *	contents;
    IIIMP_operation *	operation;
} IIIMP_forward_event_with_operations;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_operation *	operation;
} IIIMP_forward_event_with_operations_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_contents *	contents;
} IIIMP_commit_string;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    int			master;
    int			choice_per_window;
    int			rows;
    int			columns;
    int			direction;
    int			label_owner;
} IIIMP_lookup_choice_start;

typedef IIIMP_simple	IIIMP_lookup_choice_start_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    int			first;
    int			last;
    int			current;
    IIIMP_text *	choice;
    IIIMP_text *	index_label;
    IIIMP_text *	title;
} IIIMP_lookup_choice_draw;

typedef IIIMP_simple	IIIMP_lookup_choice_draw_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    int			type;
    int			value;
} IIIMP_lookup_choice_process;

typedef IIIMP_simple	IIIMP_lookup_choice_process_reply;
typedef IIIMP_simple	IIIMP_lookup_choice_done;
typedef IIIMP_simple	IIIMP_lookup_choice_done_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_card32	class_index;
    IIIMP_string *	input_method_name;
} IIIMP_aux_simple;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_card32	class_index;
    IIIMP_string *	input_method_name;
    IIIMP_card32_list *	integer_value;
    IIIMP_string *	string_value;
} IIIMP_aux_value;

#if defined(USE_OBSOLETE_NS_CODE)
/*
 * obsolete definitions -- start
 */
typedef struct {
    size_t              nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        flags;
    IIIMP_utf8string *  filename;
} IIIMP_open;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_open_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        size;
} IIIMP_read;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        size;
    void                *object;
    IIIMP_card32        ns_errno;
} IIIMP_read_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        size;
    void                *object;
} IIIMP_write;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        size;
    IIIMP_card32        ns_errno;
} IIIMP_write_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
} IIIMP_close;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_close_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        offset;
    IIIMP_card32        whence;
} IIIMP_seek;   

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        offset;
    IIIMP_card32        ns_errno;
} IIIMP_seek_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_utf8string    *dirname;
} IIIMP_opendir;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        nitems;
    IIIMP_card32        ns_errno;
    IIIMP_utf8string *  d_name;
} IIIMP_opendir_reply;
    
typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
} IIIMP_readdir;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    struct dirent       *readDir;
    IIIMP_card32        ns_errno;
} IIIMP_readdir_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
} IIIMP_closedir;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_closedir_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        mode;
    IIIMP_utf8string    *path;
} IIIMP_mkdir;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_mkdir_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_utf8string    *path;
} IIIMP_rmdir;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_rmdir_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_utf8string    *dest;
    IIIMP_utf8string    *src;
} IIIMP_symlink;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_symlink_reply;

typedef struct _iiimp_stat_struct {
    IIIMP_card32        s_mode;
    IIIMP_card32        s_nlink;
    IIIMP_card32        s_uid;
    IIIMP_card32        s_gid;
    IIIMP_card32        s_atime;
    IIIMP_card32        s_mtime;
    IIIMP_card32        s_ctime;
    IIIMP_card32        s_blksize;
    IIIMP_card32        s_attr;
    IIIMP_card64        s_dev;
    IIIMP_card64        s_rdev;
    IIIMP_card64        s_ino;
    IIIMP_card64        s_size;
    IIIMP_card64        s_blocks;
} iiimp_stat_struct;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_utf8string    *path;
} IIIMP_stat;

typedef struct {
    IIIMP_card32         nbyte;
    IIIMP_card32         ns_id;
    iiimp_stat_struct *  stat_buf;
    IIIMP_card32         ns_errno;
} IIIMP_stat_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_utf8string    *path;
} IIIMP_lstat;

typedef struct {
    IIIMP_card32         nbyte;
    IIIMP_card32         ns_id;
    iiimp_stat_struct *  stat_buf;
    IIIMP_card32         ns_errno;
} IIIMP_lstat_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
} IIIMP_fstat;

typedef struct {
    IIIMP_card32         nbyte;
    IIIMP_card32         ns_id;
    iiimp_stat_struct *  stat_buf;
    IIIMP_card32         ns_errno;
} IIIMP_fstat_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_utf8string    *path;
    IIIMP_card32        mode;
} IIIMP_creat;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_creat_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        offset;
    IIIMP_card32        whence;
} IIIMP_lseek;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        offset;
    IIIMP_card32        ns_errno;
} IIIMP_lseek_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_utf8string    *path;
} IIIMP_unlink;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_unlink_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_utf8string    *old_name;
    IIIMP_utf8string    *new_name;
} IIIMP_rename;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_rename_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        cmd;
    IIIMP_card32        arg;
} IIIMP_fcntl;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        return_value;
    IIIMP_card32        ns_errno;
} IIIMP_fcntl_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_utf8string    *path;
    IIIMP_card32        length;
} IIIMP_truncate;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_truncate_reply;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        length;
} IIIMP_ftruncate;

typedef struct {
    IIIMP_card32        nbyte;
    IIIMP_card32        ns_id;
    IIIMP_card32        ns_errno;
} IIIMP_ftruncate_reply;

/*
 * obsolete definitions -- end
 */
#endif /* USE_OBSOLETE_NS_CODE */


typedef IIIMP_aux_simple	IIIMP_aux_start;
typedef IIIMP_aux_simple	IIIMP_aux_start_reply;
typedef IIIMP_aux_value		IIIMP_aux_draw;
typedef IIIMP_aux_simple	IIIMP_aux_draw_reply;
typedef IIIMP_aux_simple	IIIMP_aux_done;
typedef IIIMP_aux_simple	IIIMP_aux_done_reply;
typedef IIIMP_aux_value		IIIMP_aux_setvalues;
typedef IIIMP_aux_simple	IIIMP_aux_setvalues_reply;
typedef IIIMP_aux_value		IIIMP_aux_getvalues;
typedef IIIMP_aux_value		IIIMP_aux_getvalues_reply;

typedef struct {
    char	dummy[1];
} IIIMP_simple_v;

typedef struct {
    int			byte_order;
    int			protocol_version;
    IIIMP_string *	user_name;
    IIIMP_string *	auth;
} IIIMP_connect_v;

typedef struct {
    IIIMP_string *	language;
} IIIMP_connect_reply_v;

typedef IIIMP_simple_v	IIIMP_disconnect_v;

typedef IIIMP_simple_v	IIIMP_disconnect_reply_v;

typedef struct {
    IIIMP_keyevent_list *	trigger_on;
    IIIMP_keyevent_list *	trigger_off;
} IIIMP_register_trigger_keys_v;

typedef struct {
    IIIMP_card16        scope_and_profile_id;
    int                 scope;
    int                 profile_id;
    HOTKEY_LIST *       hotkeys; 
} IIIMP_register_hotkeys_v;

typedef struct {
    IIIMP_card16        scope_and_profile_id;
    int                 scope;
    int                 profile_id;
} IIIMP_select_hotkey_profile_v;

typedef struct {
    int	flag;
} IIIMP_trigger_notify_v;

typedef struct {
    int	hotkey_id;
    int index;
} IIIMP_hotkey_notify_v;

typedef struct {
    int	hotkey_id;
    int	current_state_flag;
} IIIMP_hotkey_state_notify_v;

#if !defined(USE_OBSOLETE_NS_CODE)
typedef struct {
    IIIMP_file_operation_request *	request;
} IIIMP_file_operation_v;

typedef struct {
    IIIMP_file_operation_result *	result;
} IIIMP_file_operation_reply_v;

#else /* USE_OBSOLETE_NS_CODE */
typedef struct {
    IIIMP_card32  type;
    void  *       value;
} IIIMP_file_operation_v;
    
typedef struct {
    IIIMP_card32  type;
    void  *       value;
} IIIMP_file_operation_reply_v;
#endif /* USE_OBSOLETE_NS_CODE */

typedef IIIMP_simple_v	IIIMP_trigger_notify_reply_v;
typedef IIIMP_simple_v	IIIMP_hotkey_notify_reply_v;
typedef IIIMP_simple_v	IIIMP_hotkey_state_notify_reply_v;

typedef struct {
    IIIMP_imattribute *	attr_list;
} IIIMP_setimvalues_v;

typedef IIIMP_simple_v	IIIMP_setimvalues_reply_v;

typedef struct {
    IIIMP_card16_list *	attr_list;
} IIIMP_getimvalues_v;

typedef struct {
    IIIMP_imattribute *	attr_list;
} IIIMP_getimvalues_reply_v;

typedef struct {
    IIIMP_icattribute *	attr_list;
} IIIMP_createic_v;

typedef IIIMP_simple_v	IIIMP_createic_reply_v;

typedef IIIMP_simple_v	IIIMP_destroyic_v;

typedef IIIMP_simple_v	IIIMP_destroyic_reply_v;

typedef struct {
    IIIMP_icattribute *	attr_list;
} IIIMP_seticvalues_v;

typedef IIIMP_simple_v	IIIMP_seticvalues_reply_v;

typedef struct {
    IIIMP_card16_list *	attr_list;
} IIIMP_geticvalues_v;

typedef struct {
    IIIMP_icattribute *	attr_list;
} IIIMP_geticvalues_reply_v;

typedef IIIMP_simple_v	IIIMP_seticfocus_v;
typedef IIIMP_simple_v	IIIMP_seticfocus_reply_v;
typedef IIIMP_simple_v	IIIMP_unseticfocus_v;
typedef IIIMP_simple_v	IIIMP_unseticfocus_reply_v;
typedef IIIMP_simple_v	IIIMP_resetic_v;
typedef IIIMP_simple_v	IIIMP_resetic_reply_v;
typedef IIIMP_simple_v	IIIMP_preedit_start_v;

typedef struct {
    IIIMP_int32		maximum_length;
} IIIMP_preedit_start_reply_v;

typedef struct {
    IIIMP_int32		caret;
    IIIMP_int32		change_first;
    IIIMP_int32		change_length;
    IIIMP_contents *	preedit;
} IIIMP_preedit_draw_v;

typedef IIIMP_simple_v	IIIMP_preedit_draw_reply_v;
typedef IIIMP_simple_v	IIIMP_preedit_done_v;
typedef IIIMP_simple_v	IIIMP_preedit_done_reply_v;
typedef IIIMP_simple_v	IIIMP_status_start_v;
typedef IIIMP_simple_v	IIIMP_status_start_reply_v;

typedef struct {
    IIIMP_contents *	status;
} IIIMP_status_draw_v;

typedef IIIMP_simple_v	IIIMP_status_draw_reply_v;
typedef IIIMP_simple_v	IIIMP_status_done_v;
typedef IIIMP_simple_v	IIIMP_status_done_reply_v;

typedef struct {
    IIIMP_contents *	contents;
} IIIMP_forward_event_v;

typedef IIIMP_simple_v	IIIMP_forward_event_reply_v;

typedef struct {
    IIIMP_contents *	contents;
    IIIMP_operation *	operation;
} IIIMP_forward_event_with_operations_v;

typedef struct {
    IIIMP_operation *	operation;
} IIIMP_forward_event_with_operations_reply_v;

typedef struct {
    IIIMP_contents *	contents;
} IIIMP_commit_string_v;

typedef struct {
    int	master;
    int	choice_per_window;
    int	rows;
    int	columns;
    int	direction;
    int	label_owner;
} IIIMP_lookup_choice_start_v;

typedef IIIMP_simple_v	IIIMP_lookup_choice_start_reply_v;

typedef struct {
    int			first;
    int			last;
    int			current;
    IIIMP_text *	choice;
    IIIMP_text *	index_label;
    IIIMP_text *	title;
} IIIMP_lookup_choice_draw_v;

typedef IIIMP_simple_v	IIIMP_lookup_choice_draw_reply_v;

typedef struct {
    int	type;
    int	value;
} IIIMP_lookup_choice_process_v;

typedef IIIMP_simple_v	IIIMP_lookup_choice_process_reply_v;
typedef IIIMP_simple_v	IIIMP_lookup_choice_done_v;
typedef IIIMP_simple_v	IIIMP_lookup_choice_done_reply_v;

typedef struct {
    IIIMP_card32	class_index;
    IIIMP_string *	input_method_name;
} IIIMP_aux_simple_v;

typedef struct {
    IIIMP_card32	class_index;
    IIIMP_string *	input_method_name;
    IIIMP_card32_list *	integer_value;
    IIIMP_string *	string_value;
} IIIMP_aux_value_v;

typedef IIIMP_aux_simple_v	IIIMP_aux_start_v;
typedef IIIMP_aux_simple_v	IIIMP_aux_start_reply_v;
typedef IIIMP_aux_value_v	IIIMP_aux_draw_v;
typedef IIIMP_aux_simple_v	IIIMP_aux_draw_reply_v;
typedef IIIMP_aux_simple_v	IIIMP_aux_done_v;
typedef IIIMP_aux_simple_v	IIIMP_aux_done_reply_v;
typedef IIIMP_aux_value_v	IIIMP_aux_setvalues_v;
typedef IIIMP_aux_simple_v	IIIMP_aux_setvalues_reply_v;
typedef IIIMP_aux_value_v	IIIMP_aux_getvalues_v;
typedef IIIMP_aux_value_v	IIIMP_aux_getvalues_reply_v;

typedef struct {
    int	number;
} IIIMP_protocol_version_v;

typedef struct {
    int		opcode;
    uint32_t	length;	/* (byte_length << 4) */
    int		im_id;
    int		ic_id;

    union {
	IIIMP_connect_v			connect;
	IIIMP_connect_reply_v		connect_reply;
	IIIMP_disconnect_v		disconnect;
	IIIMP_disconnect_reply_v	disconnect_reply;
	IIIMP_register_trigger_keys_v	register_trigger_keys;
	IIIMP_trigger_notify_v		trigger_notify;
	IIIMP_trigger_notify_reply_v	trigger_notify_reply;
	IIIMP_register_hotkeys_v	register_hotkeys;
	IIIMP_select_hotkey_profile_v	select_hotkey_profile;
	IIIMP_hotkey_notify_v		hotkey_notify;
	IIIMP_hotkey_notify_reply_v	hotkey_notify_reply;
	IIIMP_hotkey_state_notify_v	hotkey_state_notify;
	IIIMP_hotkey_state_notify_reply_v	hotkey_state_notify_reply;
	IIIMP_setimvalues_v		setimvalues;
	IIIMP_setimvalues_reply_v	setimvalues_reply;
	IIIMP_getimvalues_v		getimvalues;
	IIIMP_getimvalues_reply_v	getimvalues_reply;
	
	IIIMP_forward_event_v		forward_event;
	IIIMP_forward_event_reply_v	forward_event_reply;
	
	IIIMP_commit_string_v		commit_string;
	
	IIIMP_forward_event_with_operations_v
	forward_event_with_operations;
	IIIMP_forward_event_with_operations_reply_v
	forward_event_with_operations_reply;

	IIIMP_createic_v		createic;
	IIIMP_createic_reply_v		createic_reply;
	IIIMP_destroyic_v		destroyic;
	IIIMP_destroyic_reply_v		destroyic_reply;
	IIIMP_seticvalues_v		seticvalues;
	IIIMP_seticvalues_reply_v	seticvalues_reply;
	IIIMP_geticvalues_v		geticvalues;
	IIIMP_geticvalues_reply_v	geticvalues_reply;
	IIIMP_seticfocus_v		seticfocus;
	IIIMP_seticfocus_reply_v	seticfocus_reply;
	IIIMP_unseticfocus_v		unseticfocus;
	IIIMP_unseticfocus_reply_v	unseticfocus_reply;
	IIIMP_resetic_v			resetic;
	IIIMP_resetic_reply_v		resetic_reply;
	IIIMP_preedit_start_v		preedit_start;
	IIIMP_preedit_start_reply_v	preedit_start_reply;
	IIIMP_preedit_draw_v		preedit_draw;
	IIIMP_preedit_draw_reply_v	preedit_draw_reply;
	IIIMP_preedit_done_v		preedit_done;
	IIIMP_preedit_done_reply_v	preedit_done_reply;
	
	IIIMP_status_start_v		status_start;
	IIIMP_status_start_reply_v	status_start_reply;
	IIIMP_status_draw_v		status_draw;
	IIIMP_status_draw_reply_v	status_draw_reply;
	IIIMP_status_done_v		status_done;
	IIIMP_status_done_reply_v	status_done_reply;

	IIIMP_lookup_choice_start_v	lookup_choice_start;
	IIIMP_lookup_choice_start_reply_v
	lookup_choice_start_reply;
	IIIMP_lookup_choice_draw_v	lookup_choice_draw;
	IIIMP_lookup_choice_draw_reply_v	lookup_choice_draw_reply;
	IIIMP_lookup_choice_done_v	lookup_choice_done;
	IIIMP_lookup_choice_done_reply_v	lookup_choice_done_reply;
	IIIMP_lookup_choice_process_v	lookup_choice_process;
	IIIMP_lookup_choice_process_reply_v
	lookup_choice_process_reply;

	IIIMP_aux_simple_v		aux_simple;
	IIIMP_aux_value_v		aux_value;

	IIIMP_aux_start_v		aux_start;
	IIIMP_aux_start_reply_v		aux_start_reply;
	IIIMP_aux_draw_v		aux_draw;
	IIIMP_aux_draw_reply_v		aux_draw_reply;
	IIIMP_aux_done_v		aux_done;
	IIIMP_aux_done_reply_v		aux_done_reply;
	IIIMP_aux_setvalues_v		aux_setvalues;
	IIIMP_aux_setvalues_reply_v	aux_setvalues_reply;
	IIIMP_aux_getvalues_v		aux_getvalues;
	IIIMP_aux_getvalues_reply_v	aux_getvalues_reply;

	IIIMP_protocol_version_v	protocol_version;

	IIIMP_file_operation_v		file_operation;
	IIIMP_file_operation_reply_v    file_operation_reply;

    }		v;

} IIIMP_message;

typedef struct iiimp_data_s	IIIMP_data_s;


/* enumeration */

typedef enum {
	IIIMP_DATA_NO_ERROR		= 0,
	IIIMP_DATA_MALLOC_ERROR		= 1,
	IIIMP_DATA_INVALID		= 2,
	IIIMP_DATA_PROTOCOL_VERSION_ERROR = 3
} IIIMP_status;


/* public interface prototype */

extern IIIMP_message *	iiimp_message_unpack(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    size_t *		nbyte,
    const uchar_t **	ptr);

extern uchar_t *	iiimp_message_pack(
    IIIMP_data_s *	data_s,
    IIIMP_message *	m,
    size_t *		nbyte);

extern FILE *	iiimp_data_print_fp(IIIMP_data_s * data_s, FILE * fp);
extern uint_t	iiimp_data_print_flag(IIIMP_data_s * data_s, uint_t log_flag);
extern int	iiimp_data_status(IIIMP_data_s * im);

extern void	iiimp_message_print(IIIMP_data_s * data_s, IIIMP_message * m);

extern const char *	iiimp_opcode_string(int num);


extern uchar_t *
iiimp_simple_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    size_t *		buf_size);

extern uchar_t *
iiimp_connect_pack(
    IIIMP_data_s *	data_s,
    IIIMP_string *	user_name,
    IIIMP_string *	auth_protocol,
    size_t *		buf_size);

extern uchar_t *
iiimp_protocol_version_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    int			protocol_version,
    size_t *		buf_size);

extern uchar_t *
iiimp_connect_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_string *	language_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_register_trigger_keys_pack(
    IIIMP_data_s *		data_s,
    IIIMP_card16		im_id,
    IIIMP_keyevent_list *	trigger_on,
    IIIMP_keyevent_list *	trigger_off,
    size_t *			buf_size);

extern uchar_t *
iiimp_register_hotkeys_pack(
    IIIMP_data_s *		data_s,
    IIIMP_card16		im_id,
    IIIMP_card16		flag,
    HOTKEY_LIST *	        hotkeys,
    size_t *			buf_size);

extern uchar_t *
iiimp_trigger_notify_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	flag,
    size_t *		buf_size);

extern uchar_t *
iiimp_hotkey_notify_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	hotkey_id,
    IIIMP_card16	index,
    size_t *		buf_size);

extern uchar_t *
iiimp_hotkey_state_notify_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	hotkey_id,
    IIIMP_card8		current_state_flag,
    size_t *		buf_size);

extern uchar_t *
iiimp_select_hotkey_profile_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	scope_and_profile_id,
    size_t *		buf_size);

extern uchar_t *
iiimp_setimvalues_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_imattribute *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_getimvalues_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16_list *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_getimvalues_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_imattribute *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_forward_event_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents,
    size_t *		buf_size);

extern uchar_t *
iiimp_commit_string_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents,
    size_t *		buf_size);

extern uchar_t *
iiimp_forward_event_with_operations_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents,
    IIIMP_operation *	operation_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_forward_event_with_operations_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_operation *	operation_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_createic_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_icattribute *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_seticvalues_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_icattribute *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_geticvalues_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16_list *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_geticvalues_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_icattribute *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_preedit_start_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_int32		maximum_length,
    size_t *		buf_size);

extern uchar_t *
iiimp_preedit_draw_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_int32		caret,
    IIIMP_int32		change_first,
    IIIMP_int32		change_length,
    IIIMP_contents *	preedit,
    size_t *		buf_size);

extern uchar_t *
iiimp_status_draw_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	status,
    size_t *		buf_size);

extern uchar_t *
iiimp_lookup_choice_start_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    int			master,
    int			choice_per_window,
    int			rows,
    int			columns,
    int			direction,
    int			label_owner,
    size_t *		buf_size);

extern uchar_t *
iiimp_lookup_choice_draw_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    int			first,
    int			last,
    int			current,
    IIIMP_text *	choice,
    IIIMP_text *	index_label,
    IIIMP_text *	title,
    size_t *		buf_size);

extern uchar_t *
iiimp_lookup_choice_process_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	type,
    IIIMP_card16	value,
    size_t *		buf_size);

extern uchar_t *
iiimp_aux_simple_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card32	class_index,
    IIIMP_string *	input_method_name,
    size_t *		buf_size);

extern uchar_t *
iiimp_aux_value_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card7		code,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card32	class_index,
    IIIMP_string *	input_method_name,
    IIIMP_card32_list *	integer_value,
    IIIMP_string *	string_value,
    size_t *		buf_size);

#if !defined(USE_OBSOLETE_NS_CODE)
extern uchar_t *
iiimp_file_operation_pack(
    IIIMP_data_s *			data_s,
    IIIMP_card16			im_id,
    IIIMP_file_operation_request *	request,
    size_t *				buf_size);

extern uchar_t *
iiimp_file_operation_reply_pack(
    IIIMP_data_s *			data_s,
    IIIMP_card16			im_id,
    IIIMP_file_operation_result *	result,
    size_t *				buf_size);

#else /* USE_OBSOLETE_NS_CODE */
extern uchar_t *
iiimp_file_operation_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16        im_id,
    IIIMP_card32        type,
    void *              object,
    size_t *		buf_size);

extern uchar_t *
iiimp_file_operation_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16        im_id,
    IIIMP_card32        type,
    void *      	object,
    size_t *		buf_size);
#endif /* USE_OBSOLETE_NS_CODE */

#define iiimp_disconnect_pack(data_s, im_id, buf_size) \
		iiimp_simple_pack(data_s, IM_DISCONNECT, im_id, 0, buf_size)
#define iiimp_disconnect_reply_pack(data_s, im_id, buf_size) \
		iiimp_simple_pack(data_s, IM_DISCONNECT_REPLY, im_id, 0, buf_size)
#define iiimp_trigger_notify_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_TRIGGER_NOTIFY_REPLY, im_id, ic_id, buf_size)
#define iiimp_hotkey_notify_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_HOTKEY_NOTIFY_REPLY, im_id, ic_id, buf_size)
#define iiimp_hotkey_state_notify_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_HOTKEY_STATE_NOTIFY_REPLY, im_id, ic_id, buf_size)
#define iiimp_setimvalues_reply_pack(data_s, im_id, buf_size) \
		iiimp_simple_pack(data_s, IM_SETIMVALUES_REPLY, im_id, 0, buf_size)
#define iiimp_forward_event_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_FORWARD_EVENT_REPLY, im_id, ic_id, buf_size)
#define iiimp_createic_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_CREATEIC_REPLY, im_id, ic_id, buf_size)
#define iiimp_destroyic_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_DESTROYIC, im_id, ic_id, buf_size)
#define iiimp_destroyic_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_DESTROYIC_REPLY, im_id, ic_id, buf_size)
#define iiimp_seticvalues_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_SETICVALUES_REPLY, im_id, ic_id, buf_size)
#define iiimp_seticfocus_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_SETICFOCUS, im_id, ic_id, buf_size)
#define iiimp_seticfocus_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_SETICFOCUS_REPLY, im_id, ic_id, buf_size)
#define iiimp_unseticfocus_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_UNSETICFOCUS, im_id, ic_id, buf_size)
#define iiimp_unseticfocus_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_UNSETICFOCUS_REPLY, im_id, ic_id, buf_size)
#define iiimp_resetic_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_RESETIC, im_id, ic_id, buf_size)
#define iiimp_resetic_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_RESETIC_REPLY, im_id, ic_id, buf_size)
#define iiimp_preedit_start_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_PREEDIT_START, im_id, ic_id, buf_size)
#define iiimp_preedit_draw_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_PREEDIT_DRAW_REPLY, im_id, ic_id, buf_size)
#define iiimp_preedit_done_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_PREEDIT_DONE, im_id, ic_id, buf_size)
#define iiimp_preedit_done_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_PREEDIT_DONE_REPLY, im_id, ic_id, buf_size)
#define iiimp_status_start_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_STATUS_START, im_id, ic_id, buf_size)
#define iiimp_status_start_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_STATUS_START_REPLY, im_id, ic_id, buf_size)
#define iiimp_status_draw_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_STATUS_DRAW_REPLY, im_id, ic_id, buf_size)
#define iiimp_status_done_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_STATUS_DONE, im_id, ic_id, buf_size)
#define iiimp_status_done_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_STATUS_DONE_REPLY, im_id, ic_id, buf_size)
#define iiimp_lookup_choice_start_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_LOOKUP_CHOICE_START_REPLY, im_id, ic_id, buf_size)
#define iiimp_lookup_choice_draw_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_LOOKUP_CHOICE_DRAW_REPLY, im_id, ic_id, buf_size)
#define iiimp_lookup_choice_done_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_LOOKUP_CHOICE_DONE, im_id, ic_id, buf_size)
#define iiimp_lookup_choice_done_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_LOOKUP_CHOICE_DONE_REPLY, im_id, ic_id, buf_size)
#define iiimp_lookup_choice_process_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_LOOKUP_CHOICE_PROCESS_REPLY, im_id, ic_id, buf_size)
#define iiimp_aux_start_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_START, im_id, ic_id, buf_size)
#define iiimp_aux_start_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_START_REPLY, im_id, ic_id, buf_size)
#define iiimp_aux_draw_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_value_pack(data_s, IM_AUX_DRAW, im_id, ic_id, buf_size)
#define iiimp_aux_draw_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_DRAW_REPLY, im_id, ic_id, buf_size)
#define iiimp_aux_done_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_DONE, im_id, ic_id, buf_size)
#define iiimp_aux_done_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_DONE_REPLY, im_id, ic_id, buf_size)
#define iiimp_aux_setvalues_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_value_pack(data_s, IM_AUX_SETVALUES, im_id, ic_id, buf_size)
#define iiimp_aux_setvalues_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_SETVALUES_REPLY, im_id, ic_id, buf_size)
#define iiimp_aux_getvalues_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_value_pack(data_s, IM_AUX_GETVALUES, im_id, ic_id, buf_size)
#define iiimp_aux_getvalues_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_value_pack(data_s, IM_AUX_GETVALUES_REPLY, im_id, ic_id, buf_size)


/* composite data interface prototype */

extern IIIMP_card16_list *
iiimp_card16_list_new(
    IIIMP_data_s *		data_s,
    int				count,
    const IIIMP_card16 *	ptr);

extern IIIMP_card32_list *
iiimp_card32_list_new(
    IIIMP_data_s *		data_s,
    int				count,
    const IIIMP_card32 *	ptr);

extern IIIMP_string *
iiimp_string_new(
    IIIMP_data_s *		data_s,
    size_t			len,
    const IIIMP_card16 *	ptr);

#if defined(USE_OBSOLETE_NS_CODE)
extern IIIMP_utf8string *
iiimp_utf8string_new(
    IIIMP_data_s *		data_s,
    size_t			len,
    const IIIMP_card8 *         ptr);
#endif /* USE_OBSOLETE_NS_CODE */

extern IIIMP_feedback_attr_list *
iiimp_feedback_attr_list_new(
    IIIMP_data_s *		data_s,
    int				count,
    const IIIMP_feedback_attr *	ptr);

extern IIIMP_char_with_feedback *
iiimp_char_with_feedback_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		code,
    IIIMP_feedback_attr_list *	feedback_attr);

extern IIIMP_operation *
iiimp_operation_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	id,
    size_t		value_nbyte,
    uchar_t *		value);

extern IIIMP_annotation_value *
iiimp_annotation_value_text_new(
    IIIMP_data_s *	data_s,
    IIIMP_int32		start_index,
    IIIMP_int32		end_index,
    IIIMP_text *	value);

extern IIIMP_annotation_value *
iiimp_annotation_value_string_new(
    IIIMP_data_s *	data_s,
    IIIMP_int32		start_index,
    IIIMP_int32		end_index,
    IIIMP_string *	value);

extern IIIMP_annotation *
iiimp_annotation_new(
    IIIMP_data_s *		data_s,
    IIIMP_card32		id,
    IIIMP_annotation_value *	value);

extern IIIMP_text *
iiimp_text_new(
    IIIMP_data_s *		data_s,
    IIIMP_char_with_feedback *	cwf,
    IIIMP_annotation *		anno);

extern IIIMP_client_descriptor *
iiimp_client_descriptor_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	type,
    IIIMP_string *	os_name,
    IIIMP_string *	arch,
    IIIMP_string *	version,
    IIIMP_string *	X_display_name,
    IIIMP_string *	X_server_vendor);

extern IIIMP_object_descriptor *
iiimp_object_descriptor_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	category,
    IIIMP_card32	object_size,
    IIIMP_card16	id_pre,
    IIIMP_card16	id_dyn,
    IIIMP_string *	rdun,
    IIIMP_string *	hrn,
    IIIMP_string *	signature,
    IIIMP_string *	user);

extern IIIMP_ccdef *
iiimp_ccdef_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	contents);

extern IIIMP_language *
iiimp_language_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	hrn,
    IIIMP_string *	id);

extern IIIMP_imeinfo *
iiimp_imeinfo_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	enable,
    IIIMP_string *	ime_id,
    IIIMP_string *	imename,
    IIIMP_string *	version,
    IIIMP_string *	description,
    IIIMP_string *	author,
    IIIMP_string *	copyright,
    IIIMP_string *	reserved1,
    IIIMP_string *	reserved2);

extern IIIMP_jarfile_object *
iiimp_jarfile_object_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	class_names,
    size_t		value_nbyte,
    const uchar_t *	value);

extern IIIMP_inputmethod_descriptor *
iiimp_inputmethod_descriptor_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	id,
    IIIMP_string *	idname,
    IIIMP_string *	hrn,
    IIIMP_language *	language,
    IIIMP_string *	rdun);

extern IIIMP_inputmethod_descriptor *
iiimp_inputmethod_descriptor2_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	id,
    IIIMP_string *	idname,
    IIIMP_string *	hrn,
    IIIMP_language *	language,
    IIIMP_string *	rdun,
    IIIMP_imeinfo *	imeinfo);

extern IIIMP_binaryfile_object *
iiimp_binaryfile_object_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	object);

extern IIIMP_imattribute *
iiimp_imattribute_inputmethod_descriptor_new(
    IIIMP_data_s *			data_s,
    IIIMP_card16			id,
    IIIMP_card16			id_dyn,
    IIIMP_inputmethod_descriptor *	value);

extern IIIMP_imattribute *
iiimp_imattribute_object_descriptor_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_object_descriptor *	value);

extern IIIMP_imattribute *
iiimp_imattribute_client_descriptor_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_client_descriptor *	value);

extern IIIMP_imattribute *
iiimp_imattribute_ccdef_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	id,
    IIIMP_card16	id_dyn,
    IIIMP_ccdef *	value);

extern IIIMP_imattribute *
iiimp_imattribute_jar_gui_object_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_jarfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_jar_light_weight_engine_object_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_jarfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_binary_gui_object_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_binary_light_weight_engine_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_script_gui_object_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_script_light_weight_engine_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_client_group_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_string *		value);

extern IIIMP_imattribute *
iiimp_imattribute_capability_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_card32_list *		value);

extern IIIMP_icattribute *
iiimp_icattribute_input_language_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	value);

extern IIIMP_icattribute *
iiimp_icattribute_character_subsets_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32_list *	value);

extern IIIMP_icattribute *
iiimp_icattribute_input_method_name_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	value);

extern IIIMP_icattribute *
iiimp_icattribute_input_method_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	value);

extern IIIMP_keyevent_list *
iiimp_keyevent_list_new(
    IIIMP_data_s *	data_s,
    int			count,
    IIIMP_keyevent *	k);

extern HOTKEY_LIST *
iiimp_hotkey_list_new(
    IIIMP_data_s *	data_s,
    int			count,
    HOTKEY *		k);

extern IIIMP_contents *
iiimp_contents_string_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	value);

extern IIIMP_contents *
iiimp_contents_text_new(
    IIIMP_data_s *	data_s,
    IIIMP_text *	value);

extern IIIMP_contents *
iiimp_contents_keyevent_list_new(
    IIIMP_data_s *		data_s,
    IIIMP_keyevent_list *	value);


/* composite data inteface prototype -- miscellaneous */

extern IIIMP_card32_list *
iiimp_card32_list_bit_set(
    IIIMP_data_s *	data_s,
    IIIMP_card32_list *	m,
    int			bit);

extern void
iiimp_card32_list_bit_clear(
    IIIMP_data_s *	data_s,
    IIIMP_card32_list *	m,
    int			bit);

extern void
iiimp_card32_list_bit_clear_all(
    IIIMP_data_s *	data_s,
    IIIMP_card32_list *	m);

extern int
iiimp_card32_list_bit_p(
    IIIMP_data_s *	data_s,
    IIIMP_card32_list *	m,
    int			bit);


/* composite data interface prototype -- file operation */

extern IIIMP_file_operation_data_fcntl *
iiimp_file_operation_data_fcntl_setfd_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	file_descriptor_flags
);

extern IIIMP_file_operation_data_fcntl *
iiimp_file_operation_data_fcntl_setfl_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	file_status_flags
);

extern IIIMP_file_operation_data_fcntl *
iiimp_file_operation_data_fcntl_flock_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	type,
    IIIMP_card16	whence,
    IIIMP_card32	start,
    IIIMP_card32	len
);

extern IIIMP_file_operation_data_stat *
iiimp_file_operation_data_stat_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	mode,
    IIIMP_card32	ino,
    IIIMP_card32	dev,
    IIIMP_card32	rdev,
    IIIMP_card32	nlink,
    IIIMP_string *	user_name,
    IIIMP_card32	uid,
    IIIMP_string *	group_name,
    IIIMP_card32	gid,
    IIIMP_card32	size,
    IIIMP_card32	atime_tv_sec,
    IIIMP_card32	atime_tv_nsec,
    IIIMP_card32	mtime_tv_sec,
    IIIMP_card32	mtime_tv_nsec,
    IIIMP_card32	ctime_tv_sec,
    IIIMP_card32	ctime_tv_nsec,
    IIIMP_card32	blksize,
    IIIMP_card32	blocks
);

extern IIIMP_file_operation_data_dir *
iiimp_file_operation_data_dir_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	ino,
    IIIMP_card32	off,
    IIIMP_string *	name
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_close_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	file_descriptor
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_creat_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path,
    IIIMP_card32	mode
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_ftruncate_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	file_descriptor,
    IIIMP_card32	length
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_lseek_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	file_descriptor,
    IIIMP_card32	offset,
    IIIMP_card32	whence
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_open_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path,
    IIIMP_card32	oflag,
    IIIMP_card32	mode
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_read_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	file_descriptor,
    IIIMP_card32	nbyte
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_truncate_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path,
    IIIMP_card32	length
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_write_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	file_descriptor,
    size_t		value_nbyte,
    const uchar_t *	value
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_link_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	existing_path,
    IIIMP_string *	new_path
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_readlink_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_rename_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	old_path,
    IIIMP_string *	new_path
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_symlink_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	existing_path,
    IIIMP_string *	new_path
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_unlink_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_chmod_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path,
    IIIMP_card32	mode
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_chown_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path,
    IIIMP_string *	user_name,
    IIIMP_card32	user_id,
    IIIMP_string *	group_name,
    IIIMP_card32	group_id
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_fchmod_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	file_descriptor,
    IIIMP_card32	mode
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_fchown_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	file_descriptor,
    IIIMP_string *	user_name,
    IIIMP_card32	user_id,
    IIIMP_string *	group_name,
    IIIMP_card32	group_id
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_lchown_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path,
    IIIMP_string *	user_name,
    IIIMP_card32	user_id,
    IIIMP_string *	group_name,
    IIIMP_card32	group_id
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_utime_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path,
    IIIMP_card32	actime,
    IIIMP_card32	modtime
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_utimes_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path,
    IIIMP_card32	tv_sec0,
    IIIMP_card32	tv_usec0,
    IIIMP_card32	tv_sec1,
    IIIMP_card32	tv_usec1
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_fstat_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	file_descriptor
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_lstat_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_stat_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_access_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	path,
    IIIMP_card32	amode
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_closedir_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	directory_handle
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_opendir_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	dirname
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_readdir_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	directory_handle
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_rewinddir_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	directory_handle
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_seekdir_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	directory_handle,
    IIIMP_card32	loc
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_telldir_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	directory_handle
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_mkdir_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	dirname,
    IIIMP_card32	mode
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_rmdir_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	dirname
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_fcntl_new(
    IIIMP_data_s *			data_s,
    IIIMP_card32			file_descriptor,
    IIIMP_card32			cmd,
    IIIMP_file_operation_data_fcntl *	arg
);

extern IIIMP_file_operation_result *
iiimp_file_operation_result_simple_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	type,
    IIIMP_card32	return_value,
    IIIMP_card32	error_number
);

extern IIIMP_file_operation_result *
iiimp_file_operation_result_void_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	type
);

#define iiimp_file_operation_result_close_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_CLOSE, \
					       return_value, error_number)

#define iiimp_file_operation_result_creat_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_CREAT, \
					       return_value, error_number)

#define iiimp_file_operation_result_ftruncate_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_FTRUNCATE, \
					       return_value, error_number)

#define iiimp_file_operation_result_lseek_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_LSEEK, \
					       return_value, error_number)

#define iiimp_file_operation_result_open_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_OPEN, \
					       return_value, error_number)

extern IIIMP_file_operation_result *
iiimp_file_operation_result_read_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	error_number,
    size_t		value_nbyte,
    const uchar_t *	value
);

#define iiimp_file_operation_result_truncate_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_TRUNCATE, \
					       return_value, error_number)

#define iiimp_file_operation_result_write_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_WRITE, \
					       return_value, error_number)

#define iiimp_file_operation_result_link_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_LINK, \
					       return_value, error_number)

extern IIIMP_file_operation_result *
iiimp_file_operation_result_readlink_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32	return_value,
    IIIMP_card32	error_number,
    IIIMP_string *	path
);

#define iiimp_file_operation_result_rename_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_RENAME, \
					       return_value, error_number)

#define iiimp_file_operation_result_symlink_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_SYMLINK, \
					       return_value, error_number)

#define iiimp_file_operation_result_unlink_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_UNLINK, \
					       return_value, error_number)

#define iiimp_file_operation_result_chmod_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_CHMOD, \
					       return_value, error_number)

#define iiimp_file_operation_result_chown_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_CHOWN, \
					       return_value, error_number)

#define iiimp_file_operation_result_fchmod_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_FCHMOD, \
					       return_value, error_number)

#define iiimp_file_operation_result_fchown_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_FCHOWN, \
					       return_value, error_number)

#define iiimp_file_operation_result_lchown_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_LCHOWN, \
					       return_value, error_number)

#define iiimp_file_operation_result_utime_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_UTIME, \
					       return_value, error_number)

#define iiimp_file_operation_result_utimes_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_UTIMES, \
					       return_value, error_number)

extern IIIMP_file_operation_result *
iiimp_file_operation_result_stat_common_new(
    IIIMP_data_s *			data_s,
    IIIMP_card32			type,
    IIIMP_card32			return_value,
    IIIMP_card32			error_number,
    IIIMP_file_operation_data_stat *	stat
);

#define iiimp_file_operation_result_fstat_new(data_s, return_value, error_number, stat) \
	iiimp_file_operation_result_stat_common_new(data_s, IIIMP_FILE_OPERATION_FSTAT, \
						    return_value, error_number, stat)

#define iiimp_file_operation_result_lstat_new(data_s, return_value, error_number, stat) \
	iiimp_file_operation_result_stat_common_new(data_s, IIIMP_FILE_OPERATION_LSTAT, \
						    return_value, error_number, stat)

#define iiimp_file_operation_result_stat_new(data_s, return_value, error_number, stat) \
	iiimp_file_operation_result_stat_common_new(data_s, IIIMP_FILE_OPERATION_STAT, \
						    return_value, error_number, stat)

#define iiimp_file_operation_result_access_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_ACCESS, \
					       return_value, error_number)

#define iiimp_file_operation_result_closedir_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_CLOSEDIR, \
					       return_value, error_number)

#define iiimp_file_operation_result_opendir_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_OPENDIR, \
					       return_value, error_number)

extern IIIMP_file_operation_result *
iiimp_file_operation_result_readdir_new(
    IIIMP_data_s *			data_s,
    IIIMP_card32			error_number,
    IIIMP_file_operation_data_dir *	dir
);

#define iiimp_file_operation_result_rewinddir_new(data_s) \
	iiimp_file_operation_result_void_new(data_s, IIIMP_FILE_OPERATION_REWINDDIR)

#define iiimp_file_operation_result_seekdir_new(data_s) \
	iiimp_file_operation_result_void_new(data_s, IIIMP_FILE_OPERATION_SEEKDIR)

#define iiimp_file_operation_result_telldir_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_TELLDIR, \
					       return_value, error_number)

#define iiimp_file_operation_result_mkdir_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_MKDIR, \
					       return_value, error_number)

#define iiimp_file_operation_result_rmdir_new(data_s, return_value, error_number) \
	iiimp_file_operation_result_simple_new(data_s, IIIMP_FILE_OPERATION_RMDIR, \
					       return_value, error_number)

extern IIIMP_file_operation_result *
iiimp_file_operation_result_fcntl_new(
    IIIMP_data_s *			data_s,
    IIIMP_card32			return_value,
    IIIMP_card32			error_number,
    IIIMP_card32			cmd,
    IIIMP_file_operation_data_fcntl *	arg
);

extern void
iiimp_file_operation_request_delete(
    IIIMP_data_s *			data_s,
    IIIMP_file_operation_request *	data
);

extern void
iiimp_file_operation_result_delete(
    IIIMP_data_s *			data_s,
    IIIMP_file_operation_result *	data
);

extern void
iiimp_file_operation_request_pack(
    IIIMP_data_s *			data_s,
    IIIMP_file_operation_request *	m,
    size_t *				nbyte,
    uchar_t **				ptr
);

extern void
iiimp_file_operation_result_pack(
    IIIMP_data_s *			data_s,
    IIIMP_file_operation_result *	m,
    size_t *				nbyte,
    uchar_t **				ptr
);

extern IIIMP_file_operation_request *
iiimp_file_operation_request_unpack(
    IIIMP_data_s *	data_s,
    size_t *		nbyte,
    const uchar_t **	ptr,
    size_t		nbyte_max
);

extern IIIMP_file_operation_result *
iiimp_file_operation_result_unpack(
    IIIMP_data_s *	data_s,
    size_t *		nbyte,
    const uchar_t **	ptr,
    size_t		nbyte_max
);

extern void
iiimp_file_operation_request_print(
    IIIMP_data_s *			data_s,
    IIIMP_file_operation_request *	data
);

extern void
iiimp_file_operation_result_print(
    IIIMP_data_s *			data_s,
    IIIMP_file_operation_result *	data
);


#if defined(USE_OBSOLETE_NS_CODE)
/* obsolete interface prototype -- start */

extern IIIMP_open *
iiimp_open_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        flags,
    IIIMP_utf8string *  filename);

extern IIIMP_open_reply *
iiimp_open_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

extern IIIMP_read *
iiimp_read_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        size);

extern IIIMP_read_reply *
iiimp_read_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno,
    IIIMP_card32        size,
    IIIMP_card32 *     	object);

extern IIIMP_write *
iiimp_write_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        size,
    void *              object);

extern IIIMP_write_reply *
iiimp_write_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno,
    IIIMP_card32        size);

extern IIIMP_close *
iiimp_close_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id);

extern IIIMP_close_reply *
iiimp_close_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

extern IIIMP_opendir *
iiimp_opendir_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_utf8string *  dirname);

extern IIIMP_opendir_reply *
iiimp_opendir_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno,
    IIIMP_card32        nitems,
    IIIMP_utf8string *  d_name);

extern IIIMP_readdir *
iiimp_readdir_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id);

extern IIIMP_readdir_reply *
iiimp_readdir_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno,
    struct dirent *     readDir);

extern IIIMP_closedir *
iiimp_closedir_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id);

extern IIIMP_closedir_reply *
iiimp_closedir_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

extern IIIMP_mkdir *
iiimp_mkdir_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        mode,
    IIIMP_utf8string *  path);

extern IIIMP_mkdir_reply *
iiimp_mkdir_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

extern IIIMP_rmdir *
iiimp_rmdir_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_utf8string *  path);

extern IIIMP_rmdir_reply *
iiimp_rmdir_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

extern IIIMP_symlink *
iiimp_symlink_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_utf8string *  dest,
    IIIMP_utf8string *  src);

extern IIIMP_symlink_reply *
iiimp_symlink_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

extern IIIMP_stat *
iiimp_stat_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_utf8string *  path);

extern IIIMP_stat_reply *
iiimp_stat_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno,
    iiimp_stat_struct * stat_buf);

extern IIIMP_lstat *
iiimp_lstat_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_utf8string *  path);

extern IIIMP_lstat_reply *
iiimp_lstat_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno,
    iiimp_stat_struct * stat_buf);

extern IIIMP_fstat *
iiimp_fstat_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id);

extern IIIMP_fstat_reply *
iiimp_fstat_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno,
    iiimp_stat_struct * stat_buf);

extern IIIMP_creat *
iiimp_creat_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        mode,
    IIIMP_utf8string *  path);

extern IIIMP_creat_reply *
iiimp_creat_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

extern IIIMP_lseek *
iiimp_lseek_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        offset,
    IIIMP_card32        whence);

extern IIIMP_lseek_reply *
iiimp_lseek_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno,
    IIIMP_card32        offset);

extern IIIMP_unlink *
iiimp_unlink_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_utf8string *  path);

extern IIIMP_unlink_reply *
iiimp_unlink_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

extern IIIMP_rename *
iiimp_rename_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_utf8string *  old_name,
    IIIMP_utf8string *  new_name);

extern IIIMP_rename_reply *
iiimp_rename_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

extern IIIMP_fcntl *
iiimp_fcntl_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        cmd,
    IIIMP_card32        arg);

extern IIIMP_fcntl_reply *
iiimp_fcntl_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno,
    IIIMP_card32        return_value);

extern IIIMP_truncate *
iiimp_truncate_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_utf8string *  path,
    IIIMP_card32        length);

extern IIIMP_truncate_reply *
iiimp_truncate_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

extern IIIMP_ftruncate *
iiimp_ftruncate_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        length);

extern IIIMP_ftruncate_reply *
iiimp_ftruncate_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card32        ns_id,
    IIIMP_card32        ns_errno);

/* obsolete interface prototype -- end */
#endif /* USE_OBSOLETE_NS_CODE */


/* public interface prototype - im_message_new */

extern IIIMP_message *
iiimp_simple_new(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id);

extern IIIMP_message *
iiimp_connect_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	user_name,
    IIIMP_string *	auth);

extern IIIMP_message *
iiimp_protocol_version_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    int			protocol_version);

extern IIIMP_message *
iiimp_connect_reply_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_string *	language_list);

#define iiimp_disconnect_new(data_s, im_id)	\
		iiimp_simple_new((data_s), IM_DISCONNECT, (im_id), 0)

#define iiimp_disconnect_reply_new(data_s, im_id)	\
		iiimp_simple_new((data_s), IM_DISCONNECT_REPLY, (im_id), 0)

extern IIIMP_message *
iiimp_register_trigger_keys_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		im_id,
    IIIMP_keyevent_list *	trigger_on,
    IIIMP_keyevent_list *	trigger_off);

extern IIIMP_message *
iiimp_trigger_notify_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	flag);

extern IIIMP_message *
iiimp_register_hotkeys_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		im_id,
    IIIMP_card16		flag,
    HOTKEY_LIST *	        hotkeys);

extern IIIMP_message *
iiimp_hotkey_notify_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	hotkey_id,
    IIIMP_card16	index);

extern IIIMP_message *
iiimp_hotkey_state_notify_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	hotkey_id,
    IIIMP_card8		current_state_flag);

extern IIIMP_message *
iiimp_select_hotkey_profile_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	scope_and_profile_id);

#if !defined(USE_OBSOLETE_NS_CODE)
extern IIIMP_message *
iiimp_file_operation_new(
    IIIMP_data_s *			data_s,
    IIIMP_card16			im_id,
    IIIMP_file_operation_request *	request);

extern IIIMP_message *
iiimp_file_operation_reply_new(
    IIIMP_data_s *			data_s,
    IIIMP_card16			im_id,
    IIIMP_file_operation_result *	result);

#else /* USE_OBSOLETE_NS_CODE */
extern IIIMP_message *
iiimp_file_operation_new(
    IIIMP_data_s *      data_s,
    IIIMP_card16        im_id,
    IIIMP_card32        type,
    void *      	object);

extern IIIMP_message *
iiimp_file_operation_reply_new(
    IIIMP_data_s *      data_s,
    IIIMP_card16        im_id,
    IIIMP_card32        type,
    void *      	object);
#endif /* USE_OBSOLETE_NS_CODE */

#define iiimp_trigger_notify_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_TRIGGER_NOTIFY_REPLY, \
				 (im_id), (ic_id))

#define iiimp_hotkey_notify_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_HOTKEY_NOTIFY_REPLY, \
				 (im_id), (ic_id))

#define iiimp_hotkey_state_notify_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_HOTKEY_STATE_NOTIFY_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_setimvalues_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_imattribute *	attr_list);

#define iiimp_setimvalues_reply_new(data_s, im_id)	\
		iiimp_simple_new((data_s), IM_SETIMVALUES_REPLY, (im_id), 0)

extern IIIMP_message *
iiimp_getimvalues_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16_list *	attr_list);

extern IIIMP_message *
iiimp_getimvalues_reply_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_imattribute *	attr_list);

extern IIIMP_message *
iiimp_forward_event_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents);

#define iiimp_forward_event_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_FORWARD_EVENT_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_commit_string_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents);

extern IIIMP_message *
iiimp_forward_event_with_operations_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents,
    IIIMP_operation *	operation);

extern IIIMP_message *
iiimp_forward_event_with_operations_reply_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_operation *	operation);


extern IIIMP_message *
iiimp_createic_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_icattribute *	attr_list);

#define iiimp_createic_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_CREATEIC_REPLY, \
				 (im_id), (ic_id))

#define iiimp_destroyic_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_DESTROYIC, \
				 (im_id), (ic_id))

#define iiimp_destroyic_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_DESTROYIC_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_seticvalues_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_icattribute *	attr_list);

#define iiimp_seticvalues_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_SETICVALUES_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_geticvalues_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16_list *	attr_list);

extern IIIMP_message *
iiimp_geticvalues_reply_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_icattribute *	attr_list);

#define iiimp_seticfocus_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_SETICFOCUS, \
				 (im_id), (ic_id))

#define iiimp_seticfocus_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_SETICFOCUS_REPLY, \
				 (im_id), (ic_id))

#define iiimp_unseticfocus_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_UNSETICFOCUS, \
				 (im_id), (ic_id))

#define iiimp_unseticfocus_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_UNSETICFOCUS_REPLY, \
				 (im_id), (ic_id))

#define iiimp_resetic_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_RESETIC, \
				 (im_id), (ic_id))

#define iiimp_resetic_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_RESETIC_REPLY, \
				 (im_id), (ic_id))

#define iiimp_preedit_start_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_PREEDIT_START, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_preedit_start_reply_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_int32		maximum_length);

extern IIIMP_message *
iiimp_preedit_draw_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_int32		aret,
    IIIMP_int32		change_first,
    IIIMP_int32		change_length,
    IIIMP_contents *	preedit);

#define iiimp_preedit_draw_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_PREEDIT_DRAW_REPLY, \
				 (im_id), (ic_id))

#define iiimp_preedit_done_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_PREEDIT_DONE, \
				 (im_id), (ic_id))

#define iiimp_preedit_done_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_PREEDIT_DONE_REPLY, \
				 (im_id), (ic_id))

#define iiimp_status_start_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_STATUS_START, \
				 (im_id), (ic_id))

#define iiimp_status_start_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_STATUS_START_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_status_draw_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	status);

#define iiimp_status_draw_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_STATUS_DRAW_REPLY, \
				 (im_id), (ic_id))

#define iiimp_status_done_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_STATUS_DONE, \
				 (im_id), (ic_id))

#define iiimp_status_done_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_STATUS_DONE_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_lookup_choice_start_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    int			master,
    int			choice_per_window,
    int			rows,
    int			columns,
    int			direction,
    int			label_owner);

#define iiimp_lookup_choice_start_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_LOOKUP_CHOICE_START_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_lookup_choice_draw_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    int			first,
    int			last,
    int			current,
    IIIMP_text *	choice,
    IIIMP_text *	index_label,
    IIIMP_text *	title);

#define iiimp_lookup_choice_draw_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_LOOKUP_CHOICE_DRAW_REPLY, \
				 (im_id), (ic_id))

#define iiimp_lookup_choice_done_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_LOOKUP_CHOICE_DONE, \
				 (im_id), (ic_id))

#define iiimp_lookup_choice_done_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_LOOKUP_CHOICE_DONE_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_lookup_choice_process_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	type,
    IIIMP_card16	value);

#define iiimp_lookup_choice_process_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_LOOKUP_CHOICE_PROCESS_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_aux_simple_new(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card32	class_index,
    IIIMP_string *	input_method_name);

extern IIIMP_message *
iiimp_aux_value_new(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card32	class_index,
    IIIMP_string *	input_method_name,
    IIIMP_card32_list *	integer_value,
    IIIMP_string *	string_value);


#define iiimp_aux_start_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_START, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_start_reply_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_START_REPLY, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_draw_new(data_s, im_id, ic_id, class_index, input_method_name, int_val, str_val)	\
		iiimp_aux_value_new((data_s), IM_AUX_DRAW, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name), \
				     (int_val), (str_val))

#define iiimp_aux_draw_reply_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_DRAW_REPLY, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_done_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_DONE, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_done_reply_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_DONE_REPLY, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_setvalues_new(data_s, im_id, ic_id, class_index, input_method_name, int_val, str_val)	\
		iiimp_aux_value_new((data_s), IM_AUX_SETVALUES, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name), \
				     (int_val), (str_val))

#define iiimp_aux_setvalues_reply_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_SETVALUES_REPLY, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_getvalues_new(data_s, im_id, ic_id, class_index, input_method_name, int_val, str_val)	\
		iiimp_aux_value_new((data_s), IM_AUX_GETVALUES, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name), \
				     (int_val), (str_val))

#define iiimp_aux_getvalues_reply_new(data_s, im_id, ic_id, class_index, input_method_name, int_val, str_val)	\
		iiimp_aux_value_new((data_s), IM_AUX_GETVALUES_REPLY, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name), \
				     (int_val), (str_val))
extern IIIMP_status
iiimp_card16_list_create(
    IIIMP_data_s *		data_s,
    IIIMP_card16_list **	ptr_ret,
    int				count,
    const IIIMP_card16 *	ptr);

extern IIIMP_status
iiimp_card32_list_create(
    IIIMP_data_s *		data_s,
    IIIMP_card32_list **	ptr_ret,
    int				count,
    const IIIMP_card32 *	ptr);

extern IIIMP_status
iiimp_string_create(
    IIIMP_data_s *		data_s,
    IIIMP_string **		ptr_ret,
    size_t			len,
    const IIIMP_card16 *	ptr);

extern IIIMP_status
iiimp_feedback_attr_list_create(
    IIIMP_data_s *		data_s,
    IIIMP_feedback_attr_list **	ptr_ret,
    int				count,
    const IIIMP_feedback_attr *	ptr);

extern IIIMP_status
iiimp_char_with_feedback_create(
    IIIMP_data_s *		data_s,
    IIIMP_char_with_feedback **	ptr_ret,
    IIIMP_card16		code,
    IIIMP_feedback_attr_list *	feedback_attr);

extern IIIMP_status
iiimp_operation_create(
    IIIMP_data_s *	data_s,
    IIIMP_operation **	ptr_ret,
    IIIMP_string *	id,
    size_t		value_nbyte,
    uchar_t *		value);

extern IIIMP_status
iiimp_annotation_value_text_create(
    IIIMP_data_s *		data_s,
    IIIMP_annotation_value **	ptr_ret,
    IIIMP_int32			start_index,
    IIIMP_int32			end_index,
    IIIMP_text *		value);

extern IIIMP_status
iiimp_annotation_value_string_create(
    IIIMP_data_s *		data_s,
    IIIMP_annotation_value **	ptr_ret,
    IIIMP_int32			start_index,
    IIIMP_int32			end_index,
    IIIMP_string *		value);

extern IIIMP_status
iiimp_annotation_create(
    IIIMP_data_s *		data_s,
    IIIMP_annotation **		ptr_ret,
    IIIMP_card32		id,
    IIIMP_annotation_value *	value);

extern IIIMP_status
iiimp_text_create(
    IIIMP_data_s *		data_s,
    IIIMP_text **		ptr_ret,
    IIIMP_char_with_feedback *	cwf,
    IIIMP_annotation *		anno);

extern IIIMP_status
iiimp_client_descriptor_create(
    IIIMP_data_s *		data_s,
    IIIMP_client_descriptor **	ptr_ret,
    IIIMP_string *		type,
    IIIMP_string *		os_name,
    IIIMP_string *		arch,
    IIIMP_string *		version,
    IIIMP_string *		X_display_name,
    IIIMP_string *		X_server_vendor);

extern IIIMP_status
iiimp_object_descriptor_create(
    IIIMP_data_s *		data_s,
    IIIMP_object_descriptor **	ptr_ret,
    IIIMP_card16		category,
    IIIMP_card32		object_size,
    IIIMP_card16		id_pre,
    IIIMP_card16		id_dyn,
    IIIMP_string *		rdun,
    IIIMP_string *		hrn,
    IIIMP_string *		signature,
    IIIMP_string *		user);

extern IIIMP_status
iiimp_ccdef_create(
    IIIMP_data_s *	data_s,
    IIIMP_ccdef **	ptr_ret,
    IIIMP_string *	contents);

extern IIIMP_status
iiimp_language_create(
    IIIMP_data_s *	data_s,
    IIIMP_language **	ptr_ret,
    IIIMP_string *	hrn,
    IIIMP_string *	id);

extern IIIMP_status
iiimp_jarfile_object_create(
    IIIMP_data_s *		data_s,
    IIIMP_jarfile_object **	ptr_ret,
    IIIMP_string *		class_names,
    size_t			value_nbyte,
    uchar_t *			value);

extern IIIMP_status
iiimp_inputmethod_descriptor_create(
    IIIMP_data_s *			data_s,
    IIIMP_inputmethod_descriptor **	ptr_ret,
    IIIMP_card16			id,
    IIIMP_string *			idname,
    IIIMP_string *			hrn,
    IIIMP_language *			language,
    IIIMP_string *			rdun);

extern IIIMP_status
iiimp_inputmethod_descriptor2_create(
    IIIMP_data_s *			data_s,
    IIIMP_inputmethod_descriptor **	ptr_ret,
    IIIMP_card16			id,
    IIIMP_string *			idname,
    IIIMP_string *			hrn,
    IIIMP_language *			language,
    IIIMP_string *			rdun,
    IIIMP_imeinfo *			imeinfo);

extern IIIMP_status
iiimp_binaryfile_object_create(
    IIIMP_data_s *		data_s,
    IIIMP_binaryfile_object **	ptr_ret,
    IIIMP_string *		object);

extern IIIMP_status
iiimp_imattribute_inputmethod_descriptor_create(
    IIIMP_data_s *			data_s,
    IIIMP_imattribute **		ptr_ret,
    IIIMP_card16			id,
    IIIMP_card16			id_dyn,
    IIIMP_inputmethod_descriptor *	value);

extern IIIMP_status
iiimp_imattribute_object_descriptor_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_object_descriptor *	value);

extern IIIMP_status
iiimp_imattribute_client_descriptor_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_client_descriptor *	value);

extern IIIMP_status
iiimp_imattribute_ccdef_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_ccdef *		value);

extern IIIMP_status
iiimp_imattribute_jar_gui_object_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_jarfile_object *	value);

extern IIIMP_status
iiimp_imattribute_jar_light_weight_engine_object_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_jarfile_object *	value);

extern IIIMP_status
iiimp_imattribute_binary_gui_object_create(
    IIIMP_data_s *			data_s,
    IIIMP_imattribute **		ptr_ret,
    IIIMP_card16			id,
    IIIMP_card16			id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_status
iiimp_imattribute_binary_light_weight_engine_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_status
iiimp_imattribute_script_gui_object_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_status
iiimp_imattribute_script_light_weight_engine_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_status
iiimp_icattribute_input_language_create(
    IIIMP_data_s *		data_s,
    IIIMP_icattribute **	ptr_ret,
    IIIMP_string *		value);

extern IIIMP_status
iiimp_icattribute_character_subsets_create(
    IIIMP_data_s *		data_s,
    IIIMP_icattribute **	ptr_ret,
    IIIMP_card32_list *		value);

extern IIIMP_status
iiimp_icattribute_input_method_name_create(
    IIIMP_data_s *		data_s,
    IIIMP_icattribute **	ptr_ret,
    IIIMP_string *		value);

extern IIIMP_status
iiimp_icattribute_input_method_create(
    IIIMP_data_s *		data_s,
    IIIMP_icattribute **	ptr_ret,
    IIIMP_card16		value);

extern IIIMP_status
iiimp_keyevent_list_create(
    IIIMP_data_s *		data_s,
    IIIMP_keyevent_list **	ptr_ret,
    int				count,
    IIIMP_keyevent *		k);

extern IIIMP_status
iiimp_contents_string_create(
    IIIMP_data_s *	data_s,
    IIIMP_contents **	ptr_ret,
    IIIMP_string *	value);

extern IIIMP_status
iiimp_contents_text_create(
    IIIMP_data_s *	data_s,
    IIIMP_contents **	ptr_ret,
    IIIMP_text *	value);

extern IIIMP_status
iiimp_contents_keyevent_list_create(
    IIIMP_data_s *		data_s,
    IIIMP_contents **		ptr_ret,
    IIIMP_keyevent_list *	value);

void	iiimp_message_delete(IIIMP_data_s * data_s, IIIMP_message * m);


/* prototype of composite data free function */

void	iiimp_card16_list_delete(IIIMP_data_s * data_s, IIIMP_card16_list * data);
void	iiimp_card32_list_delete(IIIMP_data_s * data_s, IIIMP_card32_list * data);
void	iiimp_string_delete(IIIMP_data_s * data_s, IIIMP_string * str);
void	iiimp_string_list_delete(IIIMP_data_s * data_s, IIIMP_string * str);
#if defined(USE_OBSOLETE_NS_CODE)
void	iiimp_utf8string_delete(IIIMP_data_s * data_s, IIIMP_utf8string * str);
void	iiimp_utf8string_list_delete(IIIMP_data_s * data_s, IIIMP_utf8string * str);
#endif /* USE_OBSOLETE_NS_CODE */
void	iiimp_feedback_attr_list_delete(IIIMP_data_s * data_s, IIIMP_feedback_attr_list * data);
void	iiimp_char_with_feedback_delete(IIIMP_data_s * data_s, IIIMP_char_with_feedback * cwf);
void	iiimp_char_with_feedback_list_delete(IIIMP_data_s * data_s, IIIMP_char_with_feedback * cwf);
void	iiimp_operation_delete(IIIMP_data_s * data_s, IIIMP_operation * op);
void	iiimp_operation_list_delete(IIIMP_data_s * data_s, IIIMP_operation * op);
void	iiimp_annotation_text_delete(IIIMP_data_s * data_s, IIIMP_annotation_value * anno_v);
void	iiimp_annotation_string_delete(IIIMP_data_s * data_s, IIIMP_annotation_value * anno_v);
void	iiimp_annotation_delete(IIIMP_data_s * data_s, IIIMP_annotation * anno);
void	iiimp_text_delete(IIIMP_data_s * data_s, IIIMP_text * text);
void	iiimp_text_list_delete(IIIMP_data_s * data_s, IIIMP_text * text);
void	iiimp_client_descriptor_delete(IIIMP_data_s * data_s, IIIMP_client_descriptor * cd);
void	iiimp_object_descriptor_delete(IIIMP_data_s * data_s, IIIMP_object_descriptor * od);
void	iiimp_object_descriptor_list_delete(IIIMP_data_s * data_s, IIIMP_object_descriptor * od);
void	iiimp_ccdef_delete(IIIMP_data_s * data_s, IIIMP_ccdef * ccdef);
void	iiimp_language_delete(IIIMP_data_s * data_s, IIIMP_language * language);
void	iiimp_language_list_delete(IIIMP_data_s * data_s, IIIMP_language * language);
void    iiimp_imeinfo_delete(IIIMP_data_s * data_s, IIIMP_imeinfo * imeinfo);
void    iiimp_imeinfo_list_delete(IIIMP_data_s * data_s, IIIMP_imeinfo * imeinfo);
void	iiimp_jarfile_object_delete(IIIMP_data_s * data_s, IIIMP_jarfile_object * jarfile);
void	iiimp_inputmethod_descriptor_delete(IIIMP_data_s * data_s, IIIMP_inputmethod_descriptor * im_desc);
void	iiimp_inputmethod_descriptor_list_delete(IIIMP_data_s * data_s, IIIMP_inputmethod_descriptor * im_desc);
void	iiimp_binaryfile_object_delete(IIIMP_data_s * data_s, IIIMP_binaryfile_object * bin_obj);
void	iiimp_imattribute_delete(IIIMP_data_s * data_s, IIIMP_imattribute * imattr);
void	iiimp_imattribute_list_delete(IIIMP_data_s * data_s, IIIMP_imattribute * imattr);
void	iiimp_icattribute_delete(IIIMP_data_s * data_s, IIIMP_icattribute * icattr);
void	iiimp_icattribute_list_delete(IIIMP_data_s * data_s, IIIMP_icattribute * icattr);
void	iiimp_keyevent_list_delete(IIIMP_data_s * data_s, IIIMP_keyevent_list * kel);
void	iiimp_contents_delete(IIIMP_data_s * data_s, IIIMP_contents * ptr);
void	iiimp_file_operation_request_delete(IIIMP_data_s * data_s, IIIMP_file_operation_request * data);
void	iiimp_file_operation_result_delete(IIIMP_data_s * data_s, IIIMP_file_operation_result * data);

#if defined(USE_OBSOLETE_NS_CODE)
/* obsolete prototypes -- start */
void	iiimp_open_delete(IIIMP_data_s * data_s, IIIMP_open *ptr);
void	iiimp_open_reply_delete(IIIMP_data_s * data_s, IIIMP_open_reply *ptr);
void	iiimp_close_delete(IIIMP_data_s * data_s, IIIMP_close *ptr);
void	iiimp_close_reply_delete(IIIMP_data_s * data_s, IIIMP_close_reply *ptr);
void	iiimp_read_delete(IIIMP_data_s * data_s, IIIMP_read *ptr);
void	iiimp_read_reply_delete(IIIMP_data_s * data_s, IIIMP_read_reply *ptr);
void	iiimp_write_delete(IIIMP_data_s * data_s, IIIMP_write *ptr);
void	iiimp_write_reply_delete(IIIMP_data_s * data_s, IIIMP_write_reply *ptr);
void	iiimp_opendir_delete(IIIMP_data_s * data_s, IIIMP_opendir *ptr);
void	iiimp_opendir_reply_delete(IIIMP_data_s * data_s, IIIMP_opendir_reply *ptr);
void	iiimp_closedir_delete(IIIMP_data_s * data_s, IIIMP_closedir *ptr);
void	iiimp_closedir_reply_delete(IIIMP_data_s * data_s, IIIMP_closedir_reply *ptr);
void	iiimp_seek_delete(IIIMP_data_s * data_s, IIIMP_seek *ptr);
void	iiimp_seek_reply_delete(IIIMP_data_s * data_s, IIIMP_seek_reply *ptr);
void	iiimp_mkdir_delete(IIIMP_data_s * data_s, IIIMP_mkdir *ptr);
void	iiimp_mkdir_reply_delete(IIIMP_data_s * data_s, IIIMP_mkdir_reply *ptr);
void	iiimp_rmdir_delete(IIIMP_data_s * data_s, IIIMP_rmdir *ptr);
void	iiimp_rmdir_reply_delete(IIIMP_data_s * data_s, IIIMP_rmdir_reply *ptr);
void	iiimp_symlink_delete(IIIMP_data_s * data_s, IIIMP_symlink *ptr);
void	iiimp_symlink_reply_delete(IIIMP_data_s * data_s, IIIMP_symlink_reply *ptr);
void	iiimp_stat_delete(IIIMP_data_s * data_s, IIIMP_stat *ptr);
void	iiimp_stat_reply_delete(IIIMP_data_s * data_s, IIIMP_stat_reply *ptr);
void	iiimp_lstat_delete(IIIMP_data_s * data_s, IIIMP_lstat *ptr);
void	iiimp_lstat_reply_delete(IIIMP_data_s * data_s, IIIMP_lstat_reply *ptr);
void	iiimp_fstat_delete(IIIMP_data_s * data_s, IIIMP_fstat *ptr);
void	iiimp_fstat_reply_delete(IIIMP_data_s * data_s, IIIMP_fstat_reply *ptr);
void	iiimp_creat_delete(IIIMP_data_s * data_s, IIIMP_creat *ptr);
void	iiimp_creat_reply_delete(IIIMP_data_s * data_s, IIIMP_creat_reply *ptr);
void	iiimp_lseek_delete(IIIMP_data_s * data_s, IIIMP_lseek *ptr);
void	iiimp_lseek_reply_delete(IIIMP_data_s * data_s, IIIMP_lseek_reply *ptr);
void	iiimp_unlink_delete(IIIMP_data_s * data_s, IIIMP_unlink *ptr);
void	iiimp_unlink_reply_delete(IIIMP_data_s * data_s, IIIMP_unlink_reply *ptr);
void	iiimp_rename_delete(IIIMP_data_s * data_s, IIIMP_rename *ptr);
void	iiimp_rename_reply_delete(IIIMP_data_s * data_s, IIIMP_rename_reply *ptr);
void	iiimp_fcntl_delete(IIIMP_data_s * data_s, IIIMP_fcntl *ptr);
void	iiimp_fcntl_reply_delete(IIIMP_data_s * data_s, IIIMP_fcntl_reply *ptr);
void	iiimp_truncate_delete(IIIMP_data_s * data_s, IIIMP_truncate *ptr);
void	iiimp_truncate_reply_delete(IIIMP_data_s * data_s, IIIMP_truncate_reply *ptr);
void	iiimp_ftruncate_delete(IIIMP_data_s * data_s, IIIMP_ftruncate *ptr);
void	iiimp_ftruncate_reply_delete(IIIMP_data_s * data_s, IIIMP_ftruncate_reply *ptr);
/* obsolete prototypes -- end */
#endif /* USE_OBSOLETE_NS_CODE */


/* IIIMP feedback attribute */

#define IIIMP_FEEDBACK_0_ID			(0)

#define IIIMP_FEEDBACK_0_NORMAL_VIDEO		(0)
#define IIIMP_FEEDBACK_0_REVERSE_VIDEO		(1)
#define IIIMP_FEEDBACK_0_UNDERLINE		(2)
#define IIIMP_FEEDBACK_0_HIGHLIGHT		(4)
#define IIIMP_FEEDBACK_0_PRIMARY		(8)
#define IIIMP_FEEDBACK_0_SECONDARY		(16)
#define IIIMP_FEEDBACK_0_TERTIARY		(32)


/* IIIMP annotation */

#define IIIMP_ANNOTATION_TEXT_INPUT_BEFORE_CONVERSION	(01)
#define IIIMP_ANNOTATION_READING_OF_THE_TEXT		(02)
#define IIIMP_ANNOTATION_TYPE_OF_SPEECH			(03)
#define IIIMP_ANNOTATION_TYPE_OF_CLAUSE			(04)


/* IIIMP contents */

#define IIIMP_CONTENTS_STRING	(0)
#define IIIMP_CONTENTS_TEXT	(1)
#define IIIMP_CONTENTS_KEYEVENT	(2)

/* IIIMP ic attribute */

#define IIIMP_ICATTRIBUTE_NONE			(0x00)
#define IIIMP_ICATTRIBUTE_INPUT_LANGUAGE	(0x01)
#define IIIMP_ICATTRIBUTE_CHARACTER_SUBSETS	(0x02)
#define IIIMP_ICATTRIBUTE_INPUT_METHOD_NAME	(0x03)
#define IIIMP_ICATTRIBUTE_INPUT_METHOD		(0x04)


/* IIIMP im attribute */

#define IIIMP_IMATTRIBUTE_NONE					(0x0000)
#define IIIMP_IMATTRIBUTE_INPUT_METHOD_LIST			(0x1001)
#define IIIMP_IMATTRIBUTE_OBJECT_DESCRIPTOR_LIST		(0x1010)
#define IIIMP_IMATTRIBUTE_CLIENT_DESCRIPTOR			(0x1011)
#define IIIMP_IMATTRIBUTE_CHARACTER_CONVERSION_DEFINITION_RULE	(0x1030)
#define IIIMP_IMATTRIBUTE_JAR_GUI_OBJECT			(0x1031)
#define IIIMP_IMATTRIBUTE_JAR_LIGHT_WEIGHT_ENGINE_OBJECT	(0x1032)
#define IIIMP_IMATTRIBUTE_BINARY_GUI_OBJECT			(0x1033)
#define IIIMP_IMATTRIBUTE_BINARY_LIGHT_WEIGHT_ENGINE_OBJECT	(0x1034)
#define IIIMP_IMATTRIBUTE_SCRIPT_GUI_OBJECT			(0x1035)
#define IIIMP_IMATTRIBUTE_SCRIPT_LIGHT_WEIGHT_ENGINE_OBJECT	(0x1036)
#define IIIMP_IMATTRIBUTE_CLIENT_GROUP				(0x1050)
#define IIIMP_IMATTRIBUTE_CAPABILITY				(0x1051)


/* IIIMP capability */

#define IIIMP_CAPABILITY_NONE					(0)
#define IIIMP_CAPABILITY_ERROR					(1)
#define IIIMP_CAPABILITY_FILE_OPERATION				(2)
#define IIIMP_CAPABILITY_KEY_RELEASE				(3)


/* IIIMP IM_LOOKUP_CHOICE_START */

/* lookup choice master */
#define IM_LOOKUP_CHOICE_START_UNKNOWN_IS_MASTER	(0)
#define IM_LOOKUP_CHOICE_START_SERVER_IS_MASTER		(1)
#define IM_LOOKUP_CHOICE_START_CLIENT_IS_MASTER		(2)

/* lookup choice drawing direction */
#define IM_LOOKUP_CHOICE_START_DRAWING_UP_HORIZONTALLY	(0)
#define IM_LOOKUP_CHOICE_START_DRAWING_UP_VERTICALLY	(1)

/* lookup choice lavel owner */
#define IM_LOOKUP_CHOICE_START_SERVER_OWNS_LABEL	(0)
#define IM_LOOKUP_CHOICE_START_CLIENT_OWNS_LABEL	(1)


/* IIIMP IM_LOOKUP_CHOICE_PROCESS */

#define IM_LOOKUP_CHOICE_PROCESS_INDEX	(0)
#define IM_LOOKUP_CHOICE_PROCESS_PAGE	(1)

#define IM_LOOKUP_CHOICE_PROCESS_PAGE_NEXT_PAGE		(1)
#define IM_LOOKUP_CHOICE_PROCESS_PAGE_PREV_PAGE		(2)
#define IM_LOOKUP_CHOICE_PROCESS_PAGE_FIRST_PAGE	(3)
#define IM_LOOKUP_CHOICE_PROCESS_PAGE_LAST_PAGE		(4)


/* IIIMP file operation */

#define IIIMP_FILE_OPERATION_DATA_FCNTL_FILE_STATUS_FLAGS	(1)
#define IIIMP_FILE_OPERATION_DATA_FCNTL_FILE_DESCRIPTOR_FLAGS	(2)
#define IIIMP_FILE_OPERATION_DATA_FCNTL_FLOCK			(3)


/* IIIMP IM_CONNECT */

#define IM_CONNECT_BIG_ENDIAN		(0x42)
#define IM_CONNECT_LITTLE_ENDIAN	(0x6c)


/* error status */

#define IIIMP_DATA_NO_ERROR	(0)
#define IIIMP_DATA_MALLOC_ERROR	(1)
#define IIIMP_DATA_INVALID	(2)


/* definition for debug */

#define	IIIMP_PRINT_NONE	(0x00000000)
#define	IIIMP_PRINT_QUERY	(0xffffffff)
#define	IIIMP_PRINT_JARFILE	(0x00000003)


/* obslete definitions -- start */
/* IIIMP file operation types */

#define IIIMP_FILE_OPERATION_TYPE_OPEN			(0)
#define IIIMP_FILE_OPERATION_TYPE_OPEN_REPLY		(1)
#define IIIMP_FILE_OPERATION_TYPE_READ			(2)
#define IIIMP_FILE_OPERATION_TYPE_READ_REPLY		(3)
#define IIIMP_FILE_OPERATION_TYPE_WRITE		(4)
#define IIIMP_FILE_OPERATION_TYPE_WRITE_REPLY		(5)
#define IIIMP_FILE_OPERATION_TYPE_CLOSE		(6)
#define IIIMP_FILE_OPERATION_TYPE_CLOSE_REPLY		(7)
#define IIIMP_FILE_OPERATION_TYPE_MKDIR		(8)
#define IIIMP_FILE_OPERATION_TYPE_MKDIR_REPLY		(9)
#define IIIMP_FILE_OPERATION_TYPE_RMDIR		(10)
#define IIIMP_FILE_OPERATION_TYPE_RMDIR_REPLY		(11)
#define IIIMP_FILE_OPERATION_TYPE_SYMLINK		(12)
#define IIIMP_FILE_OPERATION_TYPE_SYMLINK_REPLY	(13)
#define IIIMP_FILE_OPERATION_TYPE_STAT			(14)
#define IIIMP_FILE_OPERATION_TYPE_STAT_REPLY		(15)
#define IIIMP_FILE_OPERATION_TYPE_LSTAT		(16)
#define IIIMP_FILE_OPERATION_TYPE_LSTAT_REPLY		(17)
#define IIIMP_FILE_OPERATION_TYPE_FSTAT		(18)
#define IIIMP_FILE_OPERATION_TYPE_FSTAT_REPLY		(19)
#define IIIMP_FILE_OPERATION_TYPE_LSEEK		(20)
#define IIIMP_FILE_OPERATION_TYPE_LSEEK_REPLY		(21)
#define IIIMP_FILE_OPERATION_TYPE_UNLINK		(22)
#define IIIMP_FILE_OPERATION_TYPE_UNLINK_REPLY		(23)
#define IIIMP_FILE_OPERATION_TYPE_RENAME		(24)
#define IIIMP_FILE_OPERATION_TYPE_RENAME_REPLY		(25)
#define IIIMP_FILE_OPERATION_TYPE_FCNTL		(26)
#define IIIMP_FILE_OPERATION_TYPE_FCNTL_REPLY		(27)
#define IIIMP_FILE_OPERATION_TYPE_TRUNCATE		(28)
#define IIIMP_FILE_OPERATION_TYPE_TRUNCATE_REPLY	(29)
#define IIIMP_FILE_OPERATION_TYPE_FTRUNCATE		(30)
#define IIIMP_FILE_OPERATION_TYPE_FTRUNCATE_REPLY	(31)
#define IIIMP_FILE_OPERATION_TYPE_OPENDIR		(32)
#define IIIMP_FILE_OPERATION_TYPE_OPENDIR_REPLY	(33)
#define IIIMP_FILE_OPERATION_TYPE_CLOSEDIR		(34)
#define IIIMP_FILE_OPERATION_TYPE_CLOSEDIR_REPLY	(35)
#define IIIMP_FILE_OPERATION_TYPE_CREAT		(36)
#define IIIMP_FILE_OPERATION_TYPE_CREAT_REPLY		(37)
#define IIIMP_FILE_OPERATION_TYPE_SEEK			(38)
#define IIIMP_FILE_OPERATION_TYPE_SEEK_REPLY		(39)
/* obslete definitions -- end */

#ifdef	__cplusplus
}
#endif

#endif /* !IIIMP_DATA_H */


/* Local Variables: */
/* c-file-style: "iiim-project" */
/* End: */
