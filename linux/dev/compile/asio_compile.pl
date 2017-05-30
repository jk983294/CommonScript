#!/usr/bin/perl
use strict;
use warnings;

my @files = `ls *.cpp`;

foreach my $file (@files) {
    chomp $file;
    my ($file_no_extension) = ( $file =~ /(.*).cpp/ );

    my $mtime1 = ( stat($file) )[8];
    my $mtime2 = ( stat($file_no_extension) )[8];

    if ( !-e $file_no_extension or ( $mtime1 > $mtime2 ) ) {
        print "compiling $file\n";
        `g++ -c -std=c++11 -Wall -g $file`;
        `g++ $file_no_extension.o -o $file_no_extension -pthread -lboost_system`;
        `rm -f $file_no_extension.o`;

        # backup options: -lboost_thread
    }
}
