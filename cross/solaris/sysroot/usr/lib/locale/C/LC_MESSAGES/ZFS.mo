   #   H  Ź  I×  ˙˙˙˙˙˙                     ˙˙˙˙˙˙   &            ;   .˙˙˙˙˙˙   N   ^         f   ˙˙˙      y   Č˙˙˙˙˙˙      Î            Ô˙˙˙˙˙˙   ´   ö   	      Ç  ˙˙˙˙˙˙   ß  Q   
      ň  Š˙˙˙˙˙˙    Ż          ľ˙˙˙     -  ×˙˙˙˙˙˙  @  ď        X  V˙˙˙˙˙˙  k  V        |  \˙˙˙˙˙˙    b        Ś  ˙˙˙˙˙˙  š  â        Ń  W˙˙˙     ä  6˙˙˙˙˙˙  ő  <        
  E˙˙˙˙˙˙    j        2  ˙˙˙˙˙˙  J  î         ]  [˙˙˙˙˙˙  n  a      !    j˙˙˙   "    ˙˙˙˙˙˙  Ť  Ż      5  Ă  ˙˙˙˙˙˙  Ö     $   &  ç  ˙˙˙˙˙˙  ü     %   )    Á˙˙˙˙˙˙  $  Ý   (   *  <  +˙˙˙   +  O  #K˙˙˙˙˙˙  `  #Q   '   0  u  #Z˙˙˙˙˙˙    #   -   /    #˙˙˙˙˙˙  ľ  $,   .   2  Č  )>˙˙˙˙˙˙  Ů  )D   1   3  î  )J˙˙˙   4    )o˙˙˙˙˙˙    )š   ,   >  .  *(˙˙˙˙˙˙  A  3m   6   8  R  3s˙˙˙˙˙˙  g  3|   7   ;  |  3Ą˙˙˙˙˙˙    3Á   :   <  §  4 ˙˙˙   =  ş  ;˙˙˙˙˙˙  Ë  ;   9   C  ŕ  ;˙˙˙˙˙˙  ő  ;Á   ?   A    <˙˙˙   B     <o˙˙˙˙˙˙  3  EÇ   @   E  D  EÍ˙˙˙˙˙˙  Y  EÖ   D   F  n  Eű˙˙˙   G    F˙˙˙˙˙˙    F`ZFS-8000-D3.type ZFS-8000-D3.severity ZFS-8000-D3.response ZFS-8000-D3.impact ZFS-8000-D3.description ZFS-8000-D3.action ZFS-8000-CS.type ZFS-8000-CS.severity ZFS-8000-CS.response ZFS-8000-CS.impact ZFS-8000-CS.description ZFS-8000-CS.action ZFS-8000-A5.type ZFS-8000-A5.severity ZFS-8000-A5.response ZFS-8000-A5.impact ZFS-8000-A5.description ZFS-8000-A5.action ZFS-8000-9P.type ZFS-8000-9P.severity ZFS-8000-9P.response ZFS-8000-9P.impact ZFS-8000-9P.description ZFS-8000-9P.action ZFS-8000-8A.type ZFS-8000-8A.severity ZFS-8000-8A.response ZFS-8000-8A.impact ZFS-8000-8A.description ZFS-8000-8A.action ZFS-8000-72.type ZFS-8000-72.severity ZFS-8000-72.response ZFS-8000-72.impact ZFS-8000-72.description ZFS-8000-72.action ZFS-8000-6X.type ZFS-8000-6X.severity ZFS-8000-6X.response ZFS-8000-6X.impact ZFS-8000-6X.description ZFS-8000-6X.action ZFS-8000-5E.type ZFS-8000-5E.severity ZFS-8000-5E.response ZFS-8000-5E.impact ZFS-8000-5E.description ZFS-8000-5E.action ZFS-8000-4J.type ZFS-8000-4J.severity ZFS-8000-4J.response ZFS-8000-4J.impact ZFS-8000-4J.description ZFS-8000-4J.action ZFS-8000-3C.type ZFS-8000-3C.severity ZFS-8000-3C.response ZFS-8000-3C.impact ZFS-8000-3C.description ZFS-8000-3C.action ZFS-8000-2Q.type ZFS-8000-2Q.severity ZFS-8000-2Q.response ZFS-8000-2Q.impact ZFS-8000-2Q.description ZFS-8000-2Q.action ZFS-8000-14.type ZFS-8000-14.severity ZFS-8000-14.response ZFS-8000-14.impact ZFS-8000-14.description ZFS-8000-14.action Fault Major No automated response will occur. Fault tolerance of the pool may be compromised. A ZFS device failed.  Refer to %s for more information. Run 'zpool status -x' and replace the bad device. Fault Major No automated response will occur. The pool data is unavailable A ZFS pool failed to open.  Refer to %s for more information. Run 'zpool status -x' and either attach the missing device or
	    restore from backup. Error Major No automated response will occur, The pool is unavailable The on-disk version is not compatible with the running
	    system.  Refer to %s for more information. 
If this error is seen during 'zpool import', see the section below.  Otherwise,
run 'zpool status -x' to determine which pool is faulted:


# zpool status -x
  pool: test
 state: FAULTED
status: The ZFS version for the pool is incompatible with the software running
        on this system.
action: Destroy and re-create the pool.
 scrub: none requested
config:

        NAME                  STATE     READ WRITE CKSUM
        test                  FAULTED      0     0     0  incompatible version
          mirror              ONLINE       0     0     0
            c0t0d0            ONLINE       0     0     0
            c0t0d1            ONLINE       0     0     0


The pool cannot be used on this system.  Either move the disks to the system
where they were originally created, or destroy the pool and re-create it from
backup.


If this error is seen during import, the pool cannot be imported on the current
system.  The disks must be attached to the system which originally created the
pool, and imported there.
	 Error Minor ZFS has attempted to repair the affected data. The system is unaffected.  The detected errors may
	    indicate future failure. A device has experienced uncorrectable errors in a
	    replicated configuration.  Refer to %s for more information. 
Run 'zpool status -x' to determine which pool has experienced errors:


# zpool status
  pool: test
 state: ONLINE
status: One or more devices has experienced an unrecoverable error.  An
        attempt was made to correct the error.  Applications are unaffected.
action: Determine if the device needs to be replaced, and clear the errors
        using 'zpool online' or replace the device with 'zpool replace'.
   see: http://www.sun.com/msg/ZFS-8000-9P
 scrub: none requested
config:

        NAME                  STATE     READ WRITE CKSUM
        test                  ONLINE       0     0     0
          mirror              ONLINE       0     0     0
            c0t0d0            ONLINE       0     0     2
            c0t0d1            ONLINE       0     0     0


Find the device with a non-zero error count for READ, WRITE, or CKSUM.  This
indicates that the device has experienced a read I/O error, write I/O error, or
checksum validation error.  Because the device is part of a mirror or RAID-Z
device, ZFS was able to recover from the error and subsequently repair the
damaged data.

These error counts may or may not indicate that the device needs replacement.
It depends on how the errors were caused, which the administrator needs to
determine.  For example, the following cases will all produce errors that do not
indicate potential device failure:


A network attached device lost connectivity but has now
recovered
A device suffered from a bit flip, and expected event over long
periods of time
An adminstrator accidentally wrote over a portion of the disk using
another program


In these cases, the presence of errors does not indicate that the device is
likely to fail in the future, and therefore does not need to be replaced.  If
this is the case, then the device errors should be cleared using 'zpool online':


# zpool online test c0t0d0


On the other hand, errors may very well indicate that the device has failed or
is about to fail.  If there are continual I/O errors to a device that is
otherwise attached and functioning on the system, it most likely needs to be
replaced.   The administrator should check the system log for any driver
messages that may indicate hardware failure.  If it is determined that the
device needs to be replaced, then the 'zpool replace' command should be used:


# zpool replace test c0t0d0 c0t0d2


This will attach the new device to the pool and begin resilvering data to it.
Once the resilvering process is complete, the old device will automatically be
removed from the pool, at which point it can safely be removed from the system.
If the device needs to be replaced in-place (because there are no available
spare devices), the original device can be removed and replaced with a new
device, at which point a different form of 'zpool replace' can be used:


# zpool replace test c0t0d0


This assumes that the original device at 'c0t0d0' has been replaced with a new
device under the same path, and will be replaced appropriately

You can monitor the progress of the resilvering operation by using the 'zpool
status -x' command:


# zpool status -x
  pool: test
 state: DEGRADED
status: One or more devices is currently being replaced.  The pool may not be
	providing the necessary level of replication.
action: Wait for the resilvering operation to complete
 scrub: resilver in progress, 0.14% done, 0h0m to go
config:

        NAME                  STATE     READ WRITE CKSUM
        test                  ONLINE       0     0     0
          mirror              ONLINE       0     0     0
            replacing         ONLINE       0     0     0
              c0t0d0          ONLINE       0     0     3
              c0t0d2          ONLINE       0     0     0  58.5K resilvered
            c0t0d1            ONLINE       0     0     0

	 Error Critical No automated response will be taken. The file or directory is unavailable. A file or directory could not be read due to corrupt data.  Refer to %s for more information. 
Run 'zpool status -x' to determine which pool is damaged:


# zpool status -x
  pool: test
 state: ONLINE
status: One or more devices has experienced an error and no valid replicas
        are available.  Some filesystem data is corrupt, and applications
        may have been affected.
action: Destroy the pool and restore from backup.
   see: http://www.sun.com/msg/ZFS-8000-8A
 scrub: none requested
config:

        NAME                  STATE     READ WRITE CKSUM
        test                  ONLINE       0     0     2
          c0t0d0              ONLINE       0     0     2
          c0t0d1              ONLINE       0     0     0


Unfrotunately, the data cannot be repaired, and the only choice to repair the
data is to restore the pool from backup.  Applications attempting to access the
corrupted data will get an error (EIO), and data may be permanently lost.
	 Error Critical No automated response will be taken. The pool is no longer available The metadata required to open the pool is corrupt.  Refer to %s for more information. 
If this error is encountered during 'zpool import', see the section below.
Otherwise, run 'zpool status -x' to determine which pool is faulted:


# zpool status -x
# zpool import
  pool: test
    id: 13783646421373024673
 state: FAULTED
status: The pool metadata is corrupted and cannot be opened.
action: Destroy the pool and restore from backup.
   see: http://www.sun.com/msg/ZFS-8000-72
config:

        test              FAULTED   corrupted data
          c0t0d0          ONLINE
	  c0t0d1	  ONLINE


Even though all the devices are available, the on-disk data has been corrupted
such that the pool cannot be opened.  All data within the pool is lost, and the
pool must be destroyed and restored from an appropriate backup source.


If this error is encountered during 'zpool import', the pool is unrecoverable
and cannot be imported.  The pool must be restored from an appropriate backup
source.
	 Error Critical No automated response will be taken. The pool cannot be imported One or more top level devices are missing.  Refer to %s for more information. 
Run 'zpool import' to list which pool cannot be imported:


# zpool import
  pool: test
    id: 13783646421373024673
 state: FAULTED
status: One or more devices are missing from the system.
action: The pool cannot be imported.  Attach the missing
	devices and try again.
   see: http://www.sun.com/msg/ZFS-8000-6X
config:

        test              FAULTED   missing device
          c0t0d0          ONLINE

        Additional devices are known to be part of this pool, though their
        exact configuration cannot be determined.


ZFS attempts to store enough configuration data on the devices such that the
configuration is recoverable from any subset of devices.  In some cases,
particularly when an entire toplevel virtual device is not attached to the
system, ZFS will be unable to determine the complete configuration.  It will
always detect that these devices are missing, even if it cannot identify all of
the devices.

The unknown missing devices must be attached to the system, at which point
'zpool import' can be used to import the pool.
	 Error Critical No automated response will be taken. The pool is no longer available A device could not be opened due to a missing or invalid
	    device label and no replicas are available.  Refer to %s for more information. 
If this error is encountered during 'zpool import', see the section below.
Otherwise, run 'zpool status -x' to determine which pool is faulted:


# zpool status -x
  pool: test
 state: FAULTED
status: One or more devices could not be used because the the label is missing 
        or invalid.  There are insufficient replicas for the pool to continue
        functioning.
action: Destroy and re-create the pool from a backup source.
   see: http://www.sun.com/msg/ZFS-8000-5E
 scrub: none requested
config:

        NAME                  STATE     READ WRITE CKSUM
        test                  FAULTED      0     0     0  insufficient replicas
          c0t0d0              FAULTED      0     0     0  corrupted data
          c0t0d1              ONLINE       0     0     0


The device listed as FAULTED with "corrupted data" cannot be opened due to a
corrupt label.  ZFS will be unable to use the pool, and all data within the pool
is irrevocably lost.  The pool must be destroyed and recreated from an
appropriate backup source.  Using replicated configurations will prevent this
from happening in the future.


If this error is enountered during 'zpool import', the action is the same.  The
pool cannot be imported - all data is lost and must be restored from an
appropriate backup source.
	 Error Major No automated response will be taken. The pool is no longer providing the configured level of
	    replication. A device could not be opened due to a missing or invalid
	    device label.  Refer to %s for more information. 
If this error is encountered while running 'zpool import', see the section
below.  Otherwise, run 'zpool status -x' to determine which pool has the
damaged device:


# zpool status -x
  pool: test
 state: DEGRADED
status: One or more devices could not be used because the label is missing or
        invalid.  Sufficient replicas exist for the pool to continue
        functioning in a degraded state.
action: Replace the device using 'zpool replace'.
   see: http://www.sun.com/msg/ZFS-8000-4J
 scrub: none requested
config:

        NAME                  STATE     READ WRITE CKSUM
        test                  DEGRADED     0     0     0
          mirror              DEGRADED     0     0     0
            c0t0d0            ONLINE       0     0     0
            c0t0d1            FAULTED      0     0     0  corrupted data


Determine which device is damaged by locating the FAULTED device showing
"corrupted data".  This indicates that the device label was corrupt.  Because
ZFS could not identify the device as the one expected, no automatic resilvering
will take place.

The device can be resilvered by issuing 'zpool replace':


# zpool replace test c0t0d1


This will replace the device in situ.  To replace the device with another,
different, device, run 'zpool replace' with an additional argument specifying
the new device:


# zpool replace test c0t0d1 c0t0d2


ZFS will being migrating data to the new device as soon as the replace is
issued.  Once the resilvering completes, the original device (if different from
the replacement) will be removed, and the pool will be restored to the ONLINE
state.


If this error is encountered while running 'zpool import', the pool can be still
be imported despite the failure:


# zpool import
  pool: test
    id: 5187963178597328409
 state: DEGRADED
status: One or more devices contains corrupted data.  The fault tolerance of
	the pool may be compromised if imported.
action: The pool can be imported using its name or numeric identifier.
   see: http://www.sun.com/msg/ZFS-8000-4J
config:

        test              DEGRADED
          mirror          DEGRADED
            /disk/a       ONLINE
            /disk/b       FAULTED   corrupted data


To import the pool, run 'zpool import':


# zpool import test


Once the pool has been imported, the damaged device can be replaced according to
the above procedure.
	 Error Critical No automated response will be taken. The pool is no longer available A device could not be opened and no replicas are available.  Refer to %s for more information. 
If this error was encountered while running 'zpool import', please see the
section below.  Otherwise, run 'zpool status -x' to determine which pool
has experienced a failure:


# zpool status -x
  pool: test
 state: FAULTED
status: One or more devices could not be opened.  There are insufficient
	replicas for the pool to continue functioning.
action: Attach the missing device and online it using 'zpool online'.
   see: http://www.sun.com/msg/ZFS-8000-3C
 scrub: none requested
config:

        NAME                  STATE     READ WRITE CKSUM
        test                  FAULTED      0     0     0  insufficient replicas
          c0t0d0              ONLINE       0     0     0
          c0t0d1              FAULTED      0     0     0  cannot open
#


Attach the device to the system and run 'zpool status' again.  The pool
should automatically detect the newly attached device and resume
functioning.  You may have to mount the filesystems in the pool explicitly
using 'zfs mount'.

If the device is no longer available and cannot be reattached to the system,
then the pool must be destroyed and re-created from a backup source.


If this error is encountered during a 'zpool import', it means that one of
the devices is not attached to the system:


# zpool import
  pool: test
    id: 10121266328238932306
 state: FAULTED
status: One or more devices are missing from the system.
action: The pool cannot be imported.  Attach the missing devices and
	try again.
   see: http://www.sun.com/msg/ZFS-8000-3C
config:

        test              FAULTED   insufficient replicas
          c0t0d0          ONLINE
          c0t0d1          FAULTED   cannot open


The pool cannot be imported until the missing device is attached to the
system.  If the device has been made available in an alternate location, you
can use the '-d' option to 'zpool import' to search for devices in a
different directory.
	 Error Major No automated response will be taken. The pool is no longer providing the configured level of
	    replication. A device in a replicated configuration could not be
	    opened.  Refer to %s for more information. 
If this error was encountered while running 'zpool import', please see the
section below.  Otherwise, run 'zpool status -x' to determine which pool has
experienced a failure:


# zpool status -x
  pool: test
 state: DEGRADED
status: One or more devices could not be opened.  Sufficient replicas exist for
        the pool to continue functioning in a degraded state.
action: Attach the missing device and online it using 'zpool online'.
   see: http://www.sun.com/msg/ZFS-8000-2Q
 scrub: none requested
config:

        NAME                  STATE     READ WRITE CKSUM
        test                  DEGRADED     0     0     0
          mirror              DEGRADED     0     0     0
            c0t0d0            ONLINE       0     0     0
            c0t0d1            FAULTED      0     0     0  cannot open
#


Determine which device failed to open by looking for a FAULTED device with
an additional "cannot open" message.  If this device has been inadvertently
removed from the system, attach the device and bring it online with 'zpool
online':


# zpool online test c0t0d1
Bringing device 'c0t0d1' online
#


If the device is no longer available, the device can be replaced using the
'zpool replace' command:


# zpool replace test c0t0d1 c0t0d2
#


Existing data will be resilvered to the new device.  Once the resilvering
completes, the device will be removed from the pool.


If this error is encountered during a 'zpool import', it means that one of
the devices is not attached to the system:


# zpool import
  pool: test
    id: 10121266328238932306
 state: DEGRADED
status: One or more devices are missing from the system.
action: The pool can be imported despite missing or damaged devices.  The
        fault tolerance of the pool may be compromised if imported.
   see: http://www.sun.com/msg/ZFS-8000-2Q
config:

        test              DEGRADED
          mirror          DEGRADED
            c0t0d0        ONLINE
            c0t0d1        FAULTED   cannot open


Unlike when the pool is active on the system, the device cannot be replaced
while the pool is exported.  If the device can be attached to the system,
attach the device and run 'zpool import' again.

Alternatively, the pool can be imported as-is, though it will be placed in
the DEGRADED state due to a missing device.  Once the pool has been
imported, the missing device can be replaced as described above.
	 Error Critical No automated response will be taken. ZFS filesystems are not available The ZFS cache file is corrupted  Refer to %s for more information. 
To determine which pools are availabe for import, run the 'zpool status'
command:


# zpool import
  pool: test
    id: 12743384782310107047
 state: ONLINE
action: The pool can be imported using its name or numeric identifier.
config:

        test              ONLINE
          c0t0d0          ONLINE
#


This will automatically scan /dev/dsk for any devices
part of a pool.  If you previously had storage pools with devices in a
different directory, us the '-d' option to 'zpool import' to scan alternate
locations.

Once you have determined which pools are available for import, you can
import the pool explicitly by specifying the name or numeric identifier:


# zpool import test
#


Alternately, you can import all available pools by specifying the '-a'
option.  Once a pool has been imported, the ZFS cache will be repaired so
that the pool will appear normally in the future.
	 