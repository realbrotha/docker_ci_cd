# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/usr/lib/kdb/MacroLib.perlmod 1.3 
#  
# Licensed Materials - Property of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 1999,2001 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
################################################################


			package MacroLib;


################################################################

use init;		### import is required 

$main::{allcpu} = $main::MacroLib::{allcpu};
$main::{allthread} = $main::MacroLib::{allthread};
$main::{allpageins} = $main::MacroLib::{allpageins};
$main::{allstorage} = $main::MacroLib::{allstorage};
$main::{alllocks} = $main::MacroLib::{alllocks};
$main::{usemaster} = $main::MacroLib::{usemaster};


############
#
# usemaster
#
############

sub usemaster {
	package Master;
	require "/usr/lib/kdb/masterscript.pm" or die "couldn't open masterscript.pm: $!";
	master(@_);
}





############
#
# allcpu
#
############

### Displays the MST and the pending mpc services for each CPU.


sub allcpu {

	print $Dump->stat;
	$ErrFound = undef;

	my $cpus = $Kernel->cpu_table;
	return unless ( defined $cpus );

	return unless ( defined $cpus->count );

	for ($index = 0; $index < $cpus->{count}; $index += 1) {

		$ErrFound = undef;
		print "\n***  CPU : $index  ***\n";
		
		my $cpu = $cpus->element($index);
		next unless ( defined $cpu );

		$cpu->rawinfo =~ /(mpc_pend\W+\w+)\W/;
		next if ( defined $ErrFound );

		print "\n$1\n";
		next unless ( defined $cpu->mst_table );

		print $cpu->mst_table->rawinfo;
         
	}
}




##############
#
# allthread
#
##############

### Displays the runnable threads , the thread table and the detailed
### report and stack of each thread which STATE is RUN or SLEEP.


sub allthread {

	$ErrFound = undef;

	my $threads = $Kernel->thread_table;
	return unless ( defined $threads );

	print "RUNNABLE THREADS :\n";
	print "****************\n";

	print $threads->running, "\n";

	print "ALL THREADS\n";
	print "***********\n";

	print $threads->rawinfo, "\n";
	return if ( defined $ErrFound );

	print "Detailed listing\n";
	print "****************\n";

	return unless ( defined $threads->count );

	for ($index = 0; $index < $threads->{count}; $index += 1) {

		$ErrFound = undef;

		my $thstate = $threads->tabfield2val($index, 'STATE');

		if ( $thstate eq 'RUN' or $thstate eq 'SLEEP' ) {

			my $thread = $threads->element($index);
			next unless ( defined $thread );
			
			print $thread->rawinfo,"\n";
			next if ( defined $ErrFound );

			my $stk = $thread->stack;
			next unless ( defined $stk );

			next unless ( defined $stk->depth );

			for ($index1 = 0; $index1 < $stk->{depth}; $index1 += 1)
			{
				print	$stk->address($index1),"\t",
					$stk->routine($index1), "\t",
					$stk->offset($index1),"\n";
			}
		}
	}	
}




##############
#
# allpageins
#
##############

### Displays the table of threads waiting for PageIn.


sub allpageins {

	$ErrFound = undef;

	my $threads = $Kernel->thread_table;
	return unless ( defined $threads );
	
	print "THREADS WAITING FOR PAGING\n";
	print "**************************\n";

	print $threads->pageins, "\n";

}




##############
#
# allstorage
#
##############

### Displays the VMM SCB Index ,  Segment ID , number of pgsp blocks and
### pages in real memory  for each segment in use.


sub allstorage {

	$ErrFound = undef;

	my $threads = $Kernel->thread_table;
	return unless ( defined $threads );

	### To sort the Segment Registers

	my @segtable = undef;
	my $tabindex = 0;

	my $indexed = sub {
		my $i;
		my $segt = shift;

		for ( $i=0; $i<$#segtable+1; $i++ ) {

			return 1 if ( $segt eq $segtable[$i] );
			next;
		}

		return 0;

	};	### DO NOT ERASE the ;


	return unless ( defined $threads->count );

	for ( $index = 0; $index < $threads->{count}; $index += 1 ) {

		my $thstate = $threads->tabfield2val($index, 'STATE');
		next unless ( $thstate eq 'RUN' or $thstate eq 'SLEEP' );

		### Threads which STATE is RUN or SLEEP

		my $thread = $threads->element($index);
		next unless ( defined $thread );
			
		my $adspace = $thread->cur_space;
		next unless ( defined $adspace );

		$adspace->rawinfo;
		next if ( defined $ErrFound );


		for ($ind = 0; $ind <= 15; $ind += 1) {

			next unless ( $adspace->seginuse($ind) );

			### Each Segment Register in use

			$segtable[$tabindex++] = $adspace->segreg($ind) unless ( &$indexed( $adspace->segreg($ind) ));

		}

	}

 
	for ( $ind=0; $ind<$tabindex; $ind+=1 ) {

		my $segt = Segment->new( $segtable[$ind] );
		next unless ( defined $segt );

		$segt->rawinfo =~ /^(VMM SCB Addr.+)/m;
		next if ( defined $ErrFound );

		print $1, "\n";

		$segt->{rawinfo} =~ /^number of pgsp blocks\W+\w+\W+(\w+)/m;
		print "number of pgsp blocks : $1\n";

		$segt->{rawinfo} =~ /^pages in real memory\W+\w+\W+(\w+)/m;
		print "pages in real memory : $1\n";
		
	}		
		
}



##############
#
# alllocks
#
##############

### Displays the detailed report and stack of the threads which hold a lock 
### other threads are awaiting.


sub alllocks {

	$ErrFound = undef;

	my $threads = $Kernel->thread_table;
	return unless ( defined $threads );

	### To sort the list of locks that threads are awaiting

	my @lcktable = undef;
	my $tabindex = 0;


	my $indexed = sub {
		my $i;
		my $lck = shift;

		for ( $i = 0; $i < $#lcktable+1; $i++ ) {

			return 1 if ( $lck eq $lcktable[$i] );
			next;
		}

		return 0;

	};	### DO NOT ERASE the ;

	return unless ( defined $threads->count );

	for ( $index = 0; $index < $threads->{count}; $index += 1 ) {

		my $thstate = $threads->tabfield2val($index, 'STATE');
		next unless ( $thstate eq 'RUN' or $thstate eq 'SLEEP' );

		### Threads which STATE is RUN or SLEEP

		my $thread = $threads->element($index);
		next unless ( defined $thread );

		$thread->rawinfo =~ /wchan1\W+(\w+)\W+/;
		next if ( defined $ErrFound );

		my $wchan1 = $1;
		next unless ( $1 =~ /[^0]+/ );

		### the thread is waiting for a lock

		$lcktable[$tabindex++] = $wchan1 unless &$indexed($wchan1);
	}


	### Locks that threads are awaiting

	for ( $ind = 0; $ind < $tabindex; $ind += 1 ) {

		my $hold = $Memory->xbyte_view( $lcktable[$ind], 4 );
		next if ( defined $ErrFound );

		$hold =~ /:\W+\w+\W+(\w+)/m;

#		$Memory->xbyte_view( $lcktable[$ind], 4 ) =~ /:\W+\w+\W+(\w+)/m;

		my $tid = $1;	

                for ( $i = 0; $i < $#tidtable + 1; $i++ ) {

                        last if ( $1 eq $tidtable[$i] );
                        next;
                }

		### This thread has not been listed yet

		if ( $i == $#tidtable + 1 ) {

			$tidtable[$i] = $1;
			my $thread = Thread->new;
			next unless ( defined $thread );

			$thread->{_rawcmd} = [ ['senddata','ttid','signature'],['readdata'] ];		
			$thread->{signature} = $1;

			print $thread->rawinfo;		
			next if ( defined $ErrFound );

			my $stk = $thread->stack;
			next unless ( defined $stk );

			print $stk->rawinfo;

		}
	}

}



##############
#
# unimport
#
##############

### Unload the functions of this library.


sub unimport {

	for $key (keys %main::MacroLib::) { 
		delete $main::MacroLib::{$key};
	}

	for $key (keys %main::) { 
		if ( $key =~ /MacroLib/ ) {
			delete $main::{$key};
		}
	}

	for $key (keys %INC) { 
		if ( $key =~ /MacroLib/ ) {
			delete $INC{$key};
		}
	}

	for $key (keys %main::) {
		if ( $main::{$key} =~ /MacroLib/ ) {
			delete $main::{$key};
		}
	}
}

1;

