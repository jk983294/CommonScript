#!/usr/bin/perl
use strict;
use warnings;

my @files = `ls *.cpp`;

foreach my $file (@files) {
    chomp $file;
    my ($file_no_extension) = ( $file =~ /(.*).cpp/ );

    if ( -e "$file_no_extension.o" ) {
        `rm -f $file_no_extension.o`;
    }

    if ( -e $file_no_extension ) {
        `rm -f $file_no_extension`;
    }
}

if ( -e "a.out" ) {
    `rm -f a.out`;
}
