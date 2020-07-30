#!/bin/sh
#
# Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
#ident	"@(#)smf_include.sh	1.5	06/05/03 SMI"

smf_present () {
	[ -r /etc/svc/volatile/repository_door ] && \
	    [ ! -f /etc/svc/volatile/repository_door ]
}

smf_clear_env () {
	unset \
		SMF_FMRI \
		SMF_METHOD \
		SMF_RESTARTER
}

# smf_console
#
#   Use as "echo message 2>&1 | smf_console".  If SMF_MSGLOG_REDIRECT is
#   unset, message will be displayed to console.  SMF_MSGLOG_REDIRECT is
#   reserved for future use.
#
smf_console () {
	/usr/bin/tee ${SMF_MSGLOG_REDIRECT:-/dev/msglog}
}

# smf_is_system_labeled
#
#  Returns zero (success) if system is labeled (aka Trusted Extensions).
#  1 otherwise.
#
smf_is_system_labeled() {
	[ ! -x /bin/plabel ] && return 1
	/bin/plabel > /dev/null 2>&1
	return $?
}

# smf_netstrategy
#   -> (_INIT_NET_IF, _INIT_NET_STRATEGY)
#
#   Sets _INIT_NET_IF to the name for the network-booted
#   interface if we are booting from the network.  _INIT_NET_STRATEGY is
#   assigned the value of the current network configuration strategy.
#   Valid values for _INIT_NET_STRATEGY are "none", "dhcp", and "rarp".
#
#   The network boot strategy for a zone is always "none".
#
smf_netstrategy () {
	if [ "${_INIT_ZONENAME:=`/sbin/zonename`}" != "global" ]; then
		_INIT_NET_STRATEGY="none" export _INIT_NET_STRATEGY
		return 0
	fi

	set -- `/sbin/netstrategy`
	if [ $? -eq 0 ]; then
		[ "$1" = "nfs" -o "$1" = "cachefs" ] && \
			_INIT_NET_IF="$2" export _INIT_NET_IF
		_INIT_NET_STRATEGY="$3" export _INIT_NET_STRATEGY
	else
		return 1
	fi
}

#
# smf_kill_contract CONTRACT SIGNAL WAIT TIMEOUT
#
#   To be called from stop methods of non-transient services.
#   Sends SIGNAL to the service contract CONTRACT.  If the
#   WAIT argument is non-zero, smf_kill_contract will wait
#   until the contract is empty before returning, or until
#   TIMEOUT expires.
#
#   Example, send SIGTERM to contract 200:
#
#       smf_kill_contract 200 TERM 
#
#   Since killing a contract with pkill(1) is not atomic,
#   smf_kill_contract will continue to send SIGNAL to CONTRACT
#   every second until the contract is empty.  This will catch
#   races between fork(2) and pkill(1).
#
#   Returns 1 if the contract is invalid.
#   Returns 2 if WAIT is "1", TIMEOUT is > 0, and TIMEOUT expires.
#   Returns 0 on success.
#
smf_kill_contract() {

	time_waited=0
	time_to_wait=$4

	[ -z "$time_to_wait" ] && time_to_wait=0

	# Verify contract id is valid using pgrep
	/usr/bin/pgrep -c $1 > /dev/null 2>&1
	ret=$?
	if [ $ret -gt 1 ] ; then
		echo "Error, invalid contract \"$1\"" >&2
		return 1
	fi

	# Return if contract is already empty.
	[ $ret -eq 1 ] && return 0

	# Kill contract.
	/usr/bin/pkill -$2 -c $1
	if [ $? -gt 1 ] ; then
		echo "Error, could not kill contract \"$1\"" >&2
		return 1
	fi

	# Return if WAIT is not set or is "0"
	[ -z "$3" ] && return 0
	[ "$3" -eq 0 ] && return 0
 
	# If contract does not empty, keep killing the contract to catch
	# any child processes missed because they were forking
	/usr/bin/sleep 5
	/usr/bin/pgrep -c $1 > /dev/null 2>&1
	while [ $? -eq 0 ] ; do
		
		time_waited=`/usr/bin/expr $time_waited + 5`
		
		# Return  if TIMEOUT was passed, and it has expired
		[ "$time_to_wait" -gt 0 -a $time_waited -ge $time_to_wait ] && \
		    exit 2
		/usr/bin/pkill -$2 -c $1
		/usr/bin/sleep 5
		/usr/bin/pgrep -c $1 > /dev/null 2>&1
	done

	return 0
}

#
# smf(5) method and monitor exit status definitions
#   SMF_EXIT_ERR_OTHER, although not defined, encompasses all non-zero
#   exit status values.
#
SMF_EXIT_OK=0
SMF_EXIT_ERR_FATAL=95
SMF_EXIT_ERR_CONFIG=96
SMF_EXIT_MON_DEGRADE=97
SMF_EXIT_MON_OFFLINE=98
SMF_EXIT_ERR_NOSMF=99
SMF_EXIT_ERR_PERM=100
