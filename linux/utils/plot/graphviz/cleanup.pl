#!/usr/bin/perl
use strict;
use warnings;

my @files = `ls *.gv`;

foreach my $file (@files) {
    chomp $file;
    my ($file_no_extension) = ( $file =~ /(.*).gv/ );

    if ( -e "$file_no_extension.svg" ) {
        `rm -f $file_no_extension.svg`;
    }
}
