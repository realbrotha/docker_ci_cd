# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos53H src/bos/usr/lib/security/CC_EVALify.sh 1.14 
#  
# Licensed Materials - Property of IBM 
#  
# Restricted Materials of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 2002,2005 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
#
# NAME: CC_EVALify.sh
#
# DESCRIPTION:
#       Perform the steps needed to modify a base-installed system
#       to conform to the Target of Evaluation for the Common
#       Criteria evaluation.
#
# Finish Common Criteria technology configuration:
#
#    1). Add patch directory processing
#    2). Remove /dev/echo from /etc/pse.conf
#    3). Instantiate streams devices
#    4). Set permissions on BSD-style ptys to 000
#    5). Remove non-CC entries from inetd.conf
#    6). Update CC status in sysck.cfg
#    7). Change device permissions
#    8). Remove suid/sgid permission bits from non-trusted commands.
#    9). Register symlinks in sysck.cfg
#   10). Register devices in sysck.cfg
#   11). Change default minlen to 8
#   12). Remove httpdlite from inittab
#   13). Configure doc_search for browser use
#   14). Remove TCB bit from volatile data files
#   15). NFS port (2049) is a privileged port
#   16). Change websm to 9090 in /etc/security/priv
#   17). Add the default dacinet ACL
#   18). Make sure that the loopback interface is up
#   19). Create synonyms for /dev/console.
#   20). Enforce default X server connection permissions
#   21). Change /var/docsearch so that all files are world-readable
#   22). Add ODM stanzas to set the console permissions
#   23). Allow only root to access removable media
#   24). Disable sendmail
#   25). Disable IMNsearch
#   26). Disable tunrestore
#   27). Remove perfvmmstat and ipcs_perf
#

umask 077
unset PATH
export PATH=/usr/bin:/etc:/usr/sbin:/sbin:/usr/ucb

typeset TMP=/tmp/${0##*/}.$$
mkdir $TMP || {
	print -u2 "${0##*/}: could not create temporary directory"
	exit 1
}
function cleanup_exit {
	[[ -s $TMP/stderr || -s $TMP/stdout ]] || rm -rf $TMP
	return 0
}
trap 'cleanup_exit ; exit 0' EXIT QUIT TERM HUP INT
echo "Finishing CAPP/EAL4+ Technology configuration..."
echo

exec 3>&1
exec 1>&-
exec 2>&-

typeset -i i=0;
typeset file mode fileset srv found=0
typeset oLANG ipldev pty cdrom patch

set -A CC_CHG \
 "/usr/sbin/krshd"      "bos.net.tcp.client"  "C2_exclude" \
 "/usr/sbin/krlogind"   "bos.net.tcp.client"  "C2_exclude" \
 "/sbin/comp.kext"      "bos.rte.jfscomp"     "C2_exclude" \
 "/sbin/comp.uext"      "bos.rte.jfscomp"     "C2_exclude" \
 "/usr/sbin/portmir"    "bos.sysmgt.serv_aid" "C2_exclude" \
 "/usr/lpp/internet/server_root/cgi-bin/dpid2" "internet_server.base.httpd" "C2_exclude" \
 "/usr/sbin/auditconv"  "bos.rte.security"    "C2_exclude" \
 "/usr/bin/nslookup"    "bos.net.tcp.client"  "C2_exclude" \
 "/usr/sbin/mkpasswd"   "bos.rte.security"    "C2_exclude" \
 "/usr/lib/lpd/rembak"  "bos.rte.printers"    ""

set -A CC_INETD_SERVICE \
	"ftp"        \
	"telnet"     \
	"login"      \
	"shell"      \
	"exec"

set -A CHG_DEV \
   "/dev/xti"                           "0700" \
   "/dev/xti/tcp"                       "0600" \
   "/dev/xti/udp"                       "0600" \
   "/dev/xti/unixst"                    "0600" \
   "/dev/xti/unixdg"                    "0600" \
   "/dev/clone"                         "0600" \
   "/dev/echo"                          "0000" \
   "/dev/slog"                          "0600" \
   "/dev/spx"                           "0600" \
   "/dev/sad"                           "0600" 
   
set -A CHG_SGID \
   "/usr/bin/chfn"                      "0500" \
   "/usr/bin/chgrpmem"                  "0555" \
   "/usr/bin/lssrc"						"0555" \
   "/usr/bin/ps"						"0555" \
   "/usr/bin/smitacl"					"0555" \
   "/usr/bin/splp"						"0555" \
   "/usr/bin/timex"						"0555" \
   "/usr/bin/uptime"					"0555" \
   "/usr/bin/w"							"0555" \
   "/usr/bin/w64"						"0555" \
   "/usr/lib/lpd/pio/etc/piomkapqd"		"0555" \
   "/usr/lib/lpd/piobe"					"0555" \
   "/usr/sbin/killall"					"0555" \
   "/usr/sbin/lsgroup"					"0555"

set -A TRUSTED_PROGS \
   "/usr/bin/at"\
   "/usr/sbin/audit"\
   "/usr/sbin/auditbin"\
   "/usr/sbin/auditcat"\
   "/usr/sbin/auditmerge"\
   "/usr/sbin/auditpr"\
   "/usr/sbin/auditselect"\
   "/usr/sbin/auditstream"\
   "/usr/bin/batch"\
   "/usr/bin/chsh"\
   "/usr/sbin/chtcb"\
   "/usr/sbin/cron"\
   "/usr/bin/crontab"\
   "/usr/sbin/diag"\
   "/usr/sbin/ftpd"\
   "/usr/bin/ipcs"\
   "/usr/bin/ipcs64"\
   "/usr/bin/logout"\
   "/usr/bin/passwd"\
   "/usr/sbin/ping"\
   "/usr/sbin/rexecd"\
   "/usr/sbin/rlogind"\
   "/usr/sbin/rpc.mountd"\
   "/usr/sbin/rshd"\
   "/usr/bin/setsenv"\
   "/usr/bin/su"\
   "/usr/sbin/telnetd"\
   "/usr/sbin/tsm"\
   "/usr/lpp/X11/bin/xlock"\
   "/usr/bin/telnet"\
   "/usr/bin/tn"

set -A FIX_SYMLINKS \
	"/usr/bin/imnss"    "/usr/IMNSearch/bin/imnss"

function getlinks {
	typeset links l dev inode d0
	typeset file=${1?}
	typeset oLANG=$LANG; LANG=C

	ls -li $file 2>/dev/null | read inode d0
	df $file 2>/dev/null | awk '{x=$NF}END{print x}' |read dev d0
	[[ -z $inode || -z $dev ]] && return 1
	find $dev -xdev -inum $inode | fgrep -v $file | while read l ; do
		if [[ -z $links ]] 
		then
			links="$l"
		else
			links="$links,$l"
		fi
	done
	print $links
	LANG=$oLANG
}

function chgmode {
        typeset file=${1?}
        typeset owner=${2?}
        typeset group=${3?}
        typeset mode=${4?}

        chown $owner.$group $file
        chmod $mode $file
        tcbck -a $file mode=$mode owner=$owner group=$group type
        tcbck -y $file
}

function addlinks {
	typeset dev=${1?}
	typeset i found=0

	for i in $dev $(getlinks $dev | sed 's/,/ /') ; do
		fgrep -q $i: /etc/security/sysck.cfg && {
			found=1
			break;
		}
	done
	[[ $found -eq 1 ]] && {
		dev=$i
		tcbck -a $dev links=$(getlinks $dev)
		tcbck -y $dev
	}
	print $dev
}

#
# 1). Search patches directory for late additions
#
echo "1). Search patches directory" 1>&3

mount | awk '$1 == "/dev/cd0" {print $2}' | read cdrom
[[ ! -z $cdrom ]] && [[ -d $cdrom/patches ]] && {
	find $cdrom/patches -type f | while read patch; do
		cp -p $patch ${patch##$cdrom/patches}
	done
}

#
# 2). Remove /dev/echo from /etc/pse.conf
#
echo "2). Remove /dev/echo from /etc/pse.conf" 1>&3

ex - /etc/pse.conf <<EOF
g,/dev/echo,s,^\([^#]\),#\1,
w
q
EOF

#
# 3). Instantiate streams devices so that their permissions
#	can be modified.
#
echo "3). Instantiate streams devices" 1>&3

strload -f /etc/pse.conf

#
# 4). Set permissions on BSD-style ptys to 000
#
echo "4). Set permissions on BSD-style ptys to 000" 1>&3

for pty in /dev/ptyp* /dev/ttyp* ; do
	chgmode $pty root system 000
done

#
# 5). Remove non-CC entries from inetd.conf
#
echo "5). Remove non-CC technology entries from inetd.conf" 1>&3

#   create backup / keep top-of-file comments

[[ ! -f /etc/inetd.conf.non-CC ]] &&
	cp -p /etc/inetd.conf /etc/inetd.conf.non-CC
ex - /etc/inetd.conf <<-EOF
	1,/^[^#][^#]/-1 ya c
	%d
	0pu c
	x
EOF

#   add CC services to end of inetd.conf

i=0
while [[ $i -lt ${#CC_INETD_SERVICE[*]} ]] ; do
	srv=${CC_INETD_SERVICE[$i]}    ; i=$i+1
	sed -e "/^[# 	]*$srv[ 	]*/!d" /etc/inetd.conf.non-CC >> /etc/inetd.conf
done

#
# 6). Update CC status in sysck.cfg
#
echo "6). Update CC technology status in sysck.cfg" 1>&3

i=0;
while [[ $i -lt ${#CC_CHG[*]} ]] ; do
	file=${CC_CHG[$i]}     ; i=$i+1
	fileset=${CC_CHG[$i]}  ; i=$i+1
	exclude=${CC_CHG[$i]}  ; i=$i+1

	tcbck -a $file mode class=apply,inventory,$fileset${exclude:+,$exclude}
	tcbck -y $file
done

#
# 7). Change permissions on devices to be accessible by root only
#
echo "7). Change permissions on devices to be accessible by root only" 1>&3

#Restrict access to some /dev objects
i=0;
while [[ $i -lt ${#CHG_DEV[*]} ]] ; do
	file=${CHG_DEV[$i]}     ; i=$i+1
	mode=${CHG_DEV[$i]}     ; i=$i+1

	chgmode $file root system $mode
done

#
# 8). Remove suid/sgid permission bits from commands that are non-trusted.
#
echo "8). Remove suid/sgid permission bits from commands that are non-trusted." 1>&3

#Remove suid bit if file is owned by root and executable by an entity that is not in an admin group.
#Trusted programs are to be exempt from this modification.
for FILE in `find /  ! \( -type d -a -name "proc" -a -prune \) -a \
			\( -type f -a \( -perm -4000 \) -a -user root  -a \
			\( -perm -0001 -o \( -perm -4010 -a  \
				! \( -group system -o -group sys -o -group adm -o\
					 -group uucp -o -group mail -o -group security -o\
					 -group cron -o -group printq -o -group audit -o\
					 -group shutdown \) \) \) \)`
do
	LINE=`echo ${TRUSTED_PROGS[*]} | grep "$FILE"`
	if [[ -z $LINE ]]; then 	#if not a trusted program
		#does an entry already exist in the TCB?
		egrep ^$FILE: /etc/security/sysck.cfg >/dev/null
		ret=$?
		#no entry, but could be a hard link to existing entry, check "links" attrs
		if [[ $ret != 0 ]]; then 
			egrep "$FILE,|$FILE\$" /etc/security/sysck.cfg | egrep links >/dev/null
			ret=$?	
			if [[ $ret != 0 ]]; then
				#not a link, need to chmod and add new stanza to TCB
				chg_flag=1
			else
				#is a link, skip this file
				chg_flag=0
			fi
		else
			#there is an entry, need to chmod and update the TCB
			chg_flag=1
		fi
		
		#if needed, chmod and update/add to the TCB
		if [[ $chg_flag -eq 1 ]]; then
			chmod "-s" $FILE

			ls_line=`ls -l $FILE`
			mode=`echo $ls_line | awk '{print $1}' | sed 's/^-//g'`
			owner=`echo $ls_line | awk '{print $3}'`
			group=`echo $ls_line | awk '{print $4}'`

			tcbck -a $FILE mode=$mode owner=$owner group=$group type
			tcbck -y $FILE
		fi
	fi
done

#Restrict access to some sgid objects
i=0;
while [[ $i -lt ${#CHG_SGID[*]} ]] ; do
	file=${CHG_SGID[$i]}     ; i=$i+1
	mode=${CHG_SGID[$i]}     ; i=$i+1

	chgmode $file root system $mode
done

#
# 9). Register missing symlinks in sysck.cfg
#
echo "9). Register missing symlinks in sysck.cfg" 1>&3

i=0;
while [[ $i -lt ${#FIX_SYMLINKS[*]} ]] ; do
	file=${FIX_SYMLINKS[$i]}     ; i=$i+1
	target=${FIX_SYMLINKS[$i]}   ; i=$i+1

	tcbck -a $file type=SYMLINK target=$target
	tcbck -y $file
done

#
# 10). Register any missing devices in sysck.cfg
#
echo "10). Register any missing devices in sysck.cfg" 1>&3

#
# 11). Change default minlen user attribute to 8
#
echo "11). Change default minlen user attribute to 8" 1>&3

chsec -f /etc/security/user -s default -a minlen=8

#
# 12). Remove httpd-lite from inittab
#
echo "12). Remove httpd-lite from inittab" 1>&3

lsitab httpdlite >/dev/null && rmitab httpdlite

#
# 13). Configure doc_search for browser use
#
echo "13). Configure doc_search for browser use" 1>&3

chwebconfig -C -o LOCAL -p80 -c/usr/lpp/internet/server_root/cgi-bin \
	-d/usr/lpp/internet/server_root/pub

# Add new executables created by chwebconfig into TCB 
for file in /usr/lpp/internet/server_root/cgi-bin/ds_* ; do
	chtcb on $file
	tcbck -a $file class="inventory,IMNSearch.rte.httpdlite" group=imnadm \
		owner=imnadm mode="TCB,SUID,SGID,755" type
done

#
# 14). Remove TCB bit from volatile data files
#
echo "14). Remove TCB bit from volatile data files" 1>&3

chtcb off /etc/qconfig
tcbck -a /etc/qconfig owner group mode type

#
# 15). Only root can bind() to the NFS port
#
echo "15). Restrict non-root access to NFS port" 1>&3

egrep -q '^2049[      ]' /etc/security/priv ||
	echo "2049" >> /etc/security/priv

#
# 16). Change websm port to 9090
#
echo "16). Change websm port to 9090" 1>&3

/usr/bin/ex - /etc/security/priv <<-EOF
	g/^[ 	]*websm.*\$/s//9090/
	w!
	q
EOF

#
# 17). Add the default dacinet ACL
#
echo "17). Add the default dacinet ACL" 1>&3

egrep -q '^0[ 	]' /etc/security/acl ||
	echo "0			::/0" >> /etc/security/acl

#
# 18). Make sure that the loopback interface is up
#
echo "18). Enable the loopback interface" 1>&3

chdev -l lo0 -a "state=up"

#
# 19). Create synonyms for /dev/console
#
echo "19). Create synonyms for /dev/console" 1>&3

chsec -f /etc/security/login.cfg -s /dev/console \
	 -a "synonym=/dev/lft0,/dev/mouse0,/dev/kbd0,/dev/rcm0"

#
# 20). Enforce default X server connection permissions
#
echo "20). Enforce default X server connection permissions" 1>&3

ed - /usr/lpp/X11/defaults/xserverrc << \EOF
g!\(/usr/lpp/X11/bin/X\)[ 	][ 	]*\($EXTENSIONS\)!s!!\1 -secIP -secSMT -secLocal 700 \2!
w
q
EOF

#
# 21). Change /var/docsearch so that all files are world-readable
#
echo "21). Change /var/docsearch so that all files are world-readable" 1>&3

find /var/docsearch -type f ! -perm -004 | xargs chmod o+r
find /var/docsearch -type d ! -perm -005 | xargs chmod o+rx

#
# 22). Add ODM stanzas to set the console permissions
#
echo "22). Add ODM stanzas to set the console permissions" 1>&3

cat >$TMP/console.odm <<EOF
PdAt:
	uniquetype = "/dev/mouse0"
	attribute = "protection"
	deflt = "600"
	values = ""
	width = ""
	type = "R"
	generic = "DU"
	rep = "s"
	nls_index = 0

PdAt:
	uniquetype = "/dev/kbd0"
	attribute = "protection"
	deflt = "600"
	values = ""
	width = ""
	type = "R"
	generic = "DU"
	rep = "s"
	nls_index = 0

PdAt:
	uniquetype = "/dev/rcm0"
	attribute = "protection"
	deflt = "600"
	values = ""
	width = ""
	type = "R"
	generic = "DU"
	rep = "s"
	nls_index = 0
EOF

odmadd $TMP/console.odm

#
# 23). Allow only root to access removable media
#
echo "23). Restrict non-root access to removable media" 1>&3

for dev in /dev/rmt* /dev/fd* /dev/rfd* ; do
	[[ ! -c $dev && ! -b $dev ]] && continue
	addlinks $dev | read dev
	chgmode $dev root system 600
done

for dev in /dev/cd* /dev/rcd* ; do
	[[ ! -c $dev && ! -b $dev ]] && continue
	addlinks $dev | read dev
	chgmode $dev root system 400
done

#
# 24). Disable sendmail
#
echo "24). Disable sendmail" 1>&3

if [[ -f /etc/rc.tcpip ]] then
	sed 's/^start[	 ]*\/usr\/lib\/sendmail/#start \/usr\/lib\/sendmail/' \
		/etc/rc.tcpip > /etc/rc.tcpip.$$
	cp /etc/rc.tcpip.$$ /etc/rc.tcpip
	rm /etc/rc.tcpip.$$
fi
stopsrc -s sendmail

#
# 25). Disable IMNsearch
#
echo "25). Disable IMNSearch" 1>&3

if lsitab itess
then
	rmitab itess
fi

#
# 26). Disable tunrestore
#
echo "26). Disable tunrestore" 1>&3

if lsitab tunables
then
	rmitab tunables
fi

#
# 27). Remove perfvmmstat
#
echo "27). Remove perfvmmstat and ipcs_perf" 1>&3

for FILE in /usr/lib/drivers/perfvmmstat.* ; do
	if [ -f ${FILE} ] ; then
		rm ${FILE}
		tcbck -d ${FILE}
		for DIR in /etc/objrepos /usr/lib/objrepos ; do
			ODMDIR=$DIR odmdelete -o inventory \
				-q "loc0 = '${FILE}'"
		done
	fi
done
chgmode /usr/bin/ipcs_perf root bin 000

# Finished
echo "Finished." 1>&3

exit 0

