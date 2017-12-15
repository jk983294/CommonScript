#!/usr/bin/perl

#####################################################################################################
#
#  read messages from given process which data format is Midas　Header following Midas format
#
#  USAGE
#       md_client.pl <host>:<port>
#
#  OUTPUT
#    Output is to stdout, and consists of the time_t time the message was received
#
#####################################################################################################

use strict;
use Socket;
use Getopt::Long;
use Getopt::Std;
use Time::HiRes qw( gettimeofday );

package main;

my $separator = ';';
my ( $recv_msg, $bytes, $recv_block );
my ( $msg_length, $sec, $usec, $flag, $group, $seq );
my ( $host, $port, $iaddr, $paddr, $proto );

$| = 1;    ##autoflush stdout

my ($mtime);
my @timenow = ();

sub usage {
    if (@_) {
        print STDERR "\n", @_, "\n";
    }

    print STDERR "\n";
    print STDERR "Usage: md_client.pl <host>:<port>\n";
    exit 1;
}


###########################################################################
#
#  Main - process command line options and start up connection
#
###########################################################################
if ( @ARGV >= 1 ) { ( $host, $port ) = split( ':', $ARGV[0] ); }

if ( $host == '0' || $host == '' ) { $host = 'localhost'; }

usage "Host not specified - use <host>:<port>" unless $host;
usage "Port not specified: use <host>:<port>"  unless $port;

#
# Make the connection and enter the message loop
#
tcp_connection();


sub tcp_connection {
    ( $iaddr = inet_aton($host) ) or die "Bad hostname: $host\n";
    $paddr = sockaddr_in( $port, $iaddr );
    $proto = getprotobyname('tcp');

    socket( SOCK, PF_INET, SOCK_STREAM, $proto ) or die "socket: $!\n";

    while ( !connect( SOCK, $paddr ) ) {
        warn "Retrying connection in 1 second\n";
        sleep 1;
    }

    # turn buffered IO OFF for SOCKET
    my $old_h;
    $old_h = select(DEV);
    select(SOCKET);
    $| = 1;
    select($old_h);

    tcp_loop();

    close(SOCK) or die "close: $!\n";
}


#
#  tcp_loop - read and process tcp updates
#

sub tcp_loop {

READLOOP:
    while (1) {

        #----------------------------------------------------------------------------------
        #
        # data format
        #
        # Each message will have a leading 16 byte header
        # - 0 - 1    msg length (total exclude length field)
        # - 2 - 5    time second
        # - 6 - 9    time usecond
        # - 10       255
        # - 11       group
        # - 12 - 15  msg sequence number
        #----------------------------------------------------------------------------------

        $bytes = read SOCK, $recv_msg, 16;
        ( $msg_length, $sec, $usec, $flag, $group, $seq ) = unpack "nNNCCN", $recv_msg;
        $msg_length = $msg_length - 14;

        if ( $msg_length <= 0 ) {
            next READLOOP;
        }

        if ( $flag != 0xFF ) {
            print "header format wrong.\n";
            next READLOOP;
        }
        $bytes = read SOCK, $recv_block, $msg_length;

        @timenow = gettimeofday();

        foreach $recv_msg ( split( $separator, $recv_block ) ) {
            $mtime = sprintf( "%d.%06.6d", $timenow[0], $timenow[1] );
            print "TIME $mtime ,$recv_msg;\n";
        }
    }    # end while(1)
}    # end sub tcp_loop
