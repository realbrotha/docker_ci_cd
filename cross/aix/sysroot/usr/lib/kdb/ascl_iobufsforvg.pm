# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/ascl_iobufsforvg.perlmod 1.1 
#  
# Licensed Materials - Property of IBM 
#  
# Restricted Materials of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 2001 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
sub iobufsforvg {
	my $dsdptr = $_[0];
	my $command = "volgrp $dsdptr";
	eval{ $Dbg->sendcmd($command) };
	my $rawvolgrp = eval{ $Dbg->readcmd() };
	my $oldstar = $*;
	$*=1;
	my @workq = split("\n",$rawvolgrp);
	my $bufcount = 0;
	my @bufline;
	foreach (@workq) {
		#  The only lines that start with a hex digit are the work queue address lines
		if (/^[0-9,A-F]\w+\s+(\w+)/) {
			$bufline[$bufcount] = $1;
			$bufcount++;
		}
	}
	foreach my $buf (@bufline) {
		$command = "buf $buf";
		eval{ $Dbg->sendcmd($command) };
		my $rawbuf = eval{ $Dbg->readcmd() };
		( $rawbuf =~ /av_forw\s+(\w+)/ ) && (my $pbuf = $1);
		$command = "dw $pbuf 8";
		eval{ $Dbg->sendcmd($command) };
		my $rawdev = eval{ $Dbg->readcmd() };
		my @devlines = split("\n",$rawdev);
		my @fields = split(" ",$devlines[2]);
		($fields[4] =~ /^(....)(....)/) && (my $diskmajor = $1) && (my $diskminor = $2);
		infoprint(1, "Buf: 0x$buf  Pbuf: 0x$pbuf  Disk Major/Minor: ", hex($diskmajor), " ,", hex($diskminor), "\n");

	}
	$*=$oldstar;
}
1;
