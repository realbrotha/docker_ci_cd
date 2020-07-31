/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * Privilege constant definitions.  Privileges and privilege sets
 * are only known by name and should be mapped at runtime.
 *
 * THIS FILE WAS GENERATED; DO NOT EDIT
 */



#ifndef _SYS_PRIV_NAMES_H
#define	_SYS_PRIV_NAMES_H

#pragma ident	"@(#)priv_defs	1.12	06/06/09 SMI"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __PRIV_CONST_IMPL
/*
 * Privilege names
 */
/*
 * Allows a process to request critical events without limitation.
 * Allows a process to request reliable delivery of all events on
 * any event queue.
 */
#define	PRIV_CONTRACT_EVENT	((const char *)"contract_event")

/*
 * Allows a process to observe contract events generated by
 * contracts created and owned by users other than the process's
 * effective user ID.
 * Allows a process to open contract event endpoints belonging to
 * contracts created and owned by users other than the process's
 * effective user ID.
 */
#define	PRIV_CONTRACT_OBSERVER	((const char *)"contract_observer")

/*
 * Allow a process to access per-CPU hardware performance counters.
 */
#define	PRIV_CPC_CPU		((const char *)"cpc_cpu")

/*
 * Allows DTrace kernel-level tracing.
 */
#define	PRIV_DTRACE_KERNEL	((const char *)"dtrace_kernel")

/*
 * Allows DTrace process-level tracing.
 * Allows process-level tracing probes to be placed and enabled in
 * processes to which the user has permissions.
 */
#define	PRIV_DTRACE_PROC	((const char *)"dtrace_proc")

/*
 * Allows DTrace user-level tracing.
 * Allows use of the syscall and profile DTrace providers to
 * examine processes to which the user has permissions.
 */
#define	PRIV_DTRACE_USER	((const char *)"dtrace_user")

/*
 * Allows a process to change a file's owner user ID.
 * Allows a process to change a file's group ID to one other than
 * the process' effective group ID or one of the process'
 * supplemental group IDs.
 */
#define	PRIV_FILE_CHOWN		((const char *)"file_chown")

/*
 * Allows a process to give away its files; a process with this
 * privilege will run as if {_POSIX_CHOWN_RESTRICTED} is not
 * in effect.
 */
#define	PRIV_FILE_CHOWN_SELF	((const char *)"file_chown_self")

/*
 * Allows a process to execute an executable file whose permission
 * bits or ACL do not allow the process execute permission.
 */
#define	PRIV_FILE_DAC_EXECUTE	((const char *)"file_dac_execute")

/*
 * Allows a process to read a file or directory whose permission
 * bits or ACL do not allow the process read permission.
 */
#define	PRIV_FILE_DAC_READ	((const char *)"file_dac_read")

/*
 * Allows a process to search a directory whose permission bits or
 * ACL do not allow the process search permission.
 */
#define	PRIV_FILE_DAC_SEARCH	((const char *)"file_dac_search")

/*
 * Allows a process to write a file or directory whose permission
 * bits or ACL do not allow the process write permission.
 * In order to write files owned by uid 0 in the absence of an
 * effective uid of 0 ALL privileges are required.
 */
#define	PRIV_FILE_DAC_WRITE	((const char *)"file_dac_write")

/*
 * Allows a process to set the sensitivity label of a file or
 * directory to a sensitivity label that does not dominate the
 * existing sensitivity label.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_FILE_DOWNGRADE_SL	((const char *)"file_downgrade_sl")

/*
 * Allows a process to create hardlinks to files owned by a uid
 * different from the process' effective uid.
 */
#define	PRIV_FILE_LINK_ANY	((const char *)"file_link_any")

/*
 * Allows a process which is not the owner of a file or directory
 * to perform the following operations that are normally permitted
 * only for the file owner: modify that file's access and
 * modification times; remove or rename a file or directory whose
 * parent directory has the ``save text image after execution''
 * (sticky) bit set; mount a ``namefs'' upon a file; modify
 * permission bits or ACL except for the set-uid and set-gid
 * bits.
 */
#define	PRIV_FILE_OWNER		((const char *)"file_owner")

/*
 * Allows a process to change the ownership of a file or write to
 * a file without the set-user-ID and set-group-ID bits being
 * cleared.
 * Allows a process to set the set-group-ID bit on a file or
 * directory whose group is not the process' effective group or
 * one of the process' supplemental groups.
 * Allows a process to set the set-user-ID bit on a file with
 * different ownership in the presence of PRIV_FILE_OWNER.
 * Additional restrictions apply when creating or modifying a
 * set-uid 0 file.
 */
#define	PRIV_FILE_SETID		((const char *)"file_setid")

/*
 * Allows a process to set the sensitivity label of a file or
 * directory to a sensitivity label that dominates the existing
 * sensitivity label.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_FILE_UPGRADE_SL	((const char *)"file_upgrade_sl")

/*
 * Allows a process to make privileged ioctls to graphics devices.
 * Typically only xserver process needs to have this privilege.
 * A process with this privilege is also allowed to perform
 * privileged graphics device mappings.
 */
#define	PRIV_GRAPHICS_ACCESS	((const char *)"graphics_access")

/*
 * Allows a process to perform privileged mappings through a
 * graphics device.
 */
#define	PRIV_GRAPHICS_MAP	((const char *)"graphics_map")

/*
 * Allows a process to read a System V IPC
 * Message Queue, Semaphore Set, or Shared Memory Segment whose
 * permission bits do not allow the process read permission.
 * Allows a process to read remote shared memory whose
 * permission bits do not allow the process read permission.
 */
#define	PRIV_IPC_DAC_READ	((const char *)"ipc_dac_read")

/*
 * Allows a process to write a System V IPC
 * Message Queue, Semaphore Set, or Shared Memory Segment whose
 * permission bits do not allow the process write permission.
 * Allows a process to read remote shared memory whose
 * permission bits do not allow the process write permission.
 * Additional restrictions apply if the owner of the object has uid 0
 * and the effective uid of the current process is not 0.
 */
#define	PRIV_IPC_DAC_WRITE	((const char *)"ipc_dac_write")

/*
 * Allows a process which is not the owner of a System
 * V IPC Message Queue, Semaphore Set, or Shared Memory Segment to
 * remove, change ownership of, or change permission bits of the
 * Message Queue, Semaphore Set, or Shared Memory Segment.
 * Additional restrictions apply if the owner of the object has uid 0
 * and the effective uid of the current process is not 0.
 */
#define	PRIV_IPC_OWNER		((const char *)"ipc_owner")

/*
 * Allow a process to bind to a port that is configured as a
 * multi-level port(MLP) for the process's zone. This privilege
 * applies to both shared address and zone-specific address MLPs.
 * See tnzonecfg(4) from the Trusted Extensions manual pages for
 * information on configuring MLP ports.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_NET_BINDMLP	((const char *)"net_bindmlp")

/*
 * Allows a process to send and receive ICMP packets.
 */
#define	PRIV_NET_ICMPACCESS	((const char *)"net_icmpaccess")

/*
 * Allows a process to set NET_MAC_AWARE process flag by using
 * setpflags(2). This privilege also allows a process to set
 * SO_MAC_EXEMPT socket option by using setsockopt(3SOCKET).
 * The NET_MAC_AWARE process flag and the SO_MAC_EXEMPT socket
 * option both allow a local process to communicate with an
 * unlabeled peer if the local process' label dominates the
 * peer's default label, or if the local process runs in the
 * global zone.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_NET_MAC_AWARE	((const char *)"net_mac_aware")

/*
 * Allows a process to bind to a privileged port
 * number. The privilege port numbers are 1-1023 (the traditional
 * UNIX privileged ports) as well as those ports marked as
 * "udp/tcp_extra_priv_ports" with the exception of the ports
 * reserved for use by NFS.
 */
#define	PRIV_NET_PRIVADDR	((const char *)"net_privaddr")

/*
 * Allows a process to have direct access to the network layer.
 */
#define	PRIV_NET_RAWACCESS	((const char *)"net_rawaccess")

/*
 * Allows a process to generate audit records.
 * Allows a process to get its own audit pre-selection information.
 */
#define	PRIV_PROC_AUDIT		((const char *)"proc_audit")

/*
 * Allows a process to change its root directory.
 */
#define	PRIV_PROC_CHROOT	((const char *)"proc_chroot")

/*
 * Allows a process to use high resolution timers.
 */
#define	PRIV_PROC_CLOCK_HIGHRES	((const char *)"proc_clock_highres")

/*
 * Allows a process to call execve().
 */
#define	PRIV_PROC_EXEC		((const char *)"proc_exec")

/*
 * Allows a process to call fork1()/forkall()/vfork()
 */
#define	PRIV_PROC_FORK		((const char *)"proc_fork")

/*
 * Allows a process to examine the status of processes other
 * than those it can send signals to.  Processes which cannot
 * be examined cannot be seen in /proc and appear not to exist.
 */
#define	PRIV_PROC_INFO		((const char *)"proc_info")

/*
 * Allows a process to lock pages in physical memory.
 */
#define	PRIV_PROC_LOCK_MEMORY	((const char *)"proc_lock_memory")

/*
 * Allows a process to send signals to other processes, inspect
 * and modify process state to other processes regardless of
 * ownership.  When modifying another process, additional
 * restrictions apply:  the effective privilege set of the
 * attaching process must be a superset of the target process'
 * effective, permitted and inheritable sets; the limit set must
 * be a superset of the target's limit set; if the target process
 * has any uid set to 0 all privilege must be asserted unless the
 * effective uid is 0.
 * Allows a process to bind arbitrary processes to CPUs.
 */
#define	PRIV_PROC_OWNER		((const char *)"proc_owner")

/*
 * Allows a process to elevate its priority above its current level.
 * Allows a process to change its scheduling class to any scheduling class,
 * including the RT class.
 */
#define	PRIV_PROC_PRIOCNTL	((const char *)"proc_priocntl")

/*
 * Allows a process to send signals or trace processes outside its
 * session.
 */
#define	PRIV_PROC_SESSION	((const char *)"proc_session")

/*
 * Allows a process to set its uids at will.
 * Assuming uid 0 requires all privileges to be asserted.
 */
#define	PRIV_PROC_SETID		((const char *)"proc_setid")

/*
 * Allows a process to assign a new task ID to the calling process.
 */
#define	PRIV_PROC_TASKID	((const char *)"proc_taskid")

/*
 * Allows a process to trace or send signals to processes in
 * other zones.
 */
#define	PRIV_PROC_ZONE		((const char *)"proc_zone")

/*
 * Allows a process to enable and disable and manage accounting through
 * acct(2), getacct(2), putacct(2) and wracct(2).
 */
#define	PRIV_SYS_ACCT		((const char *)"sys_acct")

/*
 * Allows a process to perform system administration tasks such
 * as setting node and domain name and specifying nscd and coreadm
 * settings.
 */
#define	PRIV_SYS_ADMIN		((const char *)"sys_admin")

/*
 * Allows a process to start the (kernel) audit daemon.
 * Allows a process to view and set audit state (audit user ID,
 * audit terminal ID, audit sessions ID, audit pre-selection mask).
 * Allows a process to turn off and on auditing.
 * Allows a process to configure the audit parameters (cache and
 * queue sizes, event to class mappings, policy options).
 */
#define	PRIV_SYS_AUDIT		((const char *)"sys_audit")

/*
 * Allows a process to perform various system configuration tasks.
 * Allows a process to add and remove swap devices; when adding a swap
 * device, a process must also have sufficient privileges to read from
 * and write to the swap device.
 */
#define	PRIV_SYS_CONFIG		((const char *)"sys_config")

/*
 * Allows a process to successfully call a kernel module that
 * calls the kernel drv_priv(9F) function to check for allowed
 * access.
 * Allows a process to open the real console device directly.
 * Allows a process to open devices that have been exclusively opened.
 */
#define	PRIV_SYS_DEVICES	((const char *)"sys_devices")

/*
 * Allows a process to increase the size of a System V IPC Message
 * Queue buffer.
 */
#define	PRIV_SYS_IPC_CONFIG	((const char *)"sys_ipc_config")

/*
 * Allows a process to unlink and link directories.
 */
#define	PRIV_SYS_LINKDIR	((const char *)"sys_linkdir")

/*
 * Allows filesystem specific administrative procedures, such as
 * filesystem configuration ioctls, quota calls and creation/deletion
 * of snapshots.
 * Allows a process to mount and unmount filesystems which would
 * otherwise be restricted (i.e., most filesystems except
 * namefs).
 * A process performing a mount operation needs to have
 * appropriate access to the device being mounted (read-write for
 * "rw" mounts, read for "ro" mounts).
 * A process performing any of the aforementioned
 * filesystem operations needs to have read/write/owner
 * access to the mount point.
 * Only regular files and directories can serve as mount points
 * for processes which do not have all zone privileges asserted.
 * Unless a process has all zone privileges, the mount(2)
 * system call will force the "nosuid" and "restrict" options, the
 * latter only for autofs mountpoints.
 * Regardless of privileges, a process running in a non-global zone may
 * only control mounts performed from within said zone.
 * Outside the global zone, the "nodevices" option is always forced.
 */
#define	PRIV_SYS_MOUNT		((const char *)"sys_mount")

/*
 * Allows a process to configure a system's network interfaces and routes.
 * Allows a process to configure network parameters using ndd.
 * Allows a process access to otherwise restricted information using ndd.
 * Allows a process to push the rpcmod STREAMs module.
 * Allows a process to pop anchored STREAMs modules.
 * Allows a process to INSERT/REMOVE STREAMs modules on locations other
 * than the top of the module stack.
 * Allows a process to configure IPsec.
 */
#define	PRIV_SYS_NET_CONFIG	((const char *)"sys_net_config")

/*
 * Allows a process to perform Sun private NFS specific system calls.
 * Allows a process to bind to ports reserved by NFS: ports 2049 (nfs)
 * and port 4045 (lockd).
 */
#define	PRIV_SYS_NFS		((const char *)"sys_nfs")

/*
 * Allows a process to create and delete processor sets, assign
 * CPUs to processor sets and override the PSET_NOESCAPE property.
 * Allows a process to change the operational status of CPUs in
 * the system using p_online(2).
 * Allows a process to configure resource pools and to bind
 * processes to pools
 */
#define	PRIV_SYS_RES_CONFIG	((const char *)"sys_res_config")

/*
 * Allows a process to modify the resource limits specified
 * by setrlimit(2) and setrctl(2) without restriction.
 * Allows a process to exceed the per-user maximum number of
 * processes.
 * Allows a process to extend or create files on a filesystem that
 * has less than minfree space in reserve.
 */
#define	PRIV_SYS_RESOURCE	((const char *)"sys_resource")

/*
 * Allows a process to successfully call a third party loadable module
 * that calls the kernel suser() function to check for allowed access.
 * This privilege exists only for third party loadable module
 * compatibility and is not used by Solaris proper.
 */
#define	PRIV_SYS_SUSER_COMPAT	((const char *)"sys_suser_compat")

/*
 * Allows a process to manipulate system time using any of the
 * appropriate system calls: stime, adjtime, ntp_adjtime and
 * the IA specific RTC calls.
 */
#define	PRIV_SYS_TIME		((const char *)"sys_time")

/*
 * Allows a process to translate labels that are not dominated
 * by the process' sensitivity label to and from an external
 * string form.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_SYS_TRANS_LABEL	((const char *)"sys_trans_label")

/*
 * Allows a process to override colormap restrictions.
 * Allows a process to install or remove colormaps.
 * Allows a process to retrieve colormap cell entries allocated
 * by other processes.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_COLORMAP	((const char *)"win_colormap")

/*
 * Allows a process to configure or destroy resources that are
 * permanently retained by the X server.
 * Allows a process to use SetScreenSaver to set the screen
 * saver timeout value.
 * Allows a process to use ChangeHosts to modify the display
 * access control list.
 * Allows a process to use GrabServer.
 * Allows a process to use the SetCloseDownMode request which
 * may retain window, pixmap, colormap, property, cursor, font,
 * or graphic context resources.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_CONFIG		((const char *)"win_config")

/*
 * Allows a process to read from a window resource that it does
 * not own (has a different user ID).
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_DAC_READ	((const char *)"win_dac_read")

/*
 * Allows a process to write to or create a window resource that
 * it does not own (has a different user ID). A newly created
 * window property is created with the window's user ID.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_DAC_WRITE	((const char *)"win_dac_write")

/*
 * Allows a process to perform operations on window input devices.
 * Allows a process to get and set keyboard and pointer controls.
 * Allows a process to modify pointer button and key mappings.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_DEVICES	((const char *)"win_devices")

/*
 * Allows a process to use the direct graphics access (DGA) X protocol
 * extensions. Direct process access to the frame buffer is still
 * required. Thus the process must have MAC and DAC privileges that
 * allow access to the frame buffer, or the frame buffer must be
 * allocated to the process.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_DGA		((const char *)"win_dga")

/*
 * Allows a process to set the sensitivity label of a window resource
 * to a sensitivity label that does not dominate the existing
 * sensitivity label.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_DOWNGRADE_SL	((const char *)"win_downgrade_sl")

/*
 * Allows a process to set a font path.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_FONTPATH	((const char *)"win_fontpath")

/*
 * Allows a process to read from a window resource whose sensitivity
 * label is not equal to the process sensitivity label.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_MAC_READ	((const char *)"win_mac_read")

/*
 * Allows a process to create a window resource whose sensitivity
 * label is not equal to the process sensitivity label.
 * A newly created window property is created with the window's
 * sensitivity label.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_MAC_WRITE	((const char *)"win_mac_write")

/*
 * Allows a process to request inter-window data moves without the
 * intervention of the selection confirmer.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_SELECTION	((const char *)"win_selection")

/*
 * Allows a process to set the sensitivity label of a window
 * resource to a sensitivity label that dominates the existing
 * sensitivity label.
 * This privilege is interpreted only if the system is configured
 * with Trusted Extensions.
 */
#define	PRIV_WIN_UPGRADE_SL	((const char *)"win_upgrade_sl")


/*
 * Privilege set names
 */
/*
 * Set of privileges currently in effect.
 */
#define	PRIV_EFFECTIVE		((const char *)"Effective")

/*
 * Set of privileges that comes into effect on exec.
 */
#define	PRIV_INHERITABLE	((const char *)"Inheritable")

/*
 * Set of privileges that can be put into the effective set without
 * restriction.
 */
#define	PRIV_PERMITTED		((const char *)"Permitted")

/*
 * Set of privileges that determines the absolute upper bound of
 * privileges this process and its off-spring can obtain.
 */
#define	PRIV_LIMIT		((const char *)"Limit")


#endif /* __PRIV_CONST_IMPL */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_PRIV_NAMES_H */