#!/usr/bin/perl
use strict;
use warnings;

my @files = `ls *.gv`;

foreach my $file (@files) {
    chomp $file;
    my ($file_svg) = ( $file =~ /(.*).gv/ );
    $file_svg = $file_svg . '.svg';

    my $mtime1 = ( stat($file) )[8];
    my $mtime2 = ( stat($file_svg) )[8];

    if ( !-e $file_svg or ( $mtime1 > $mtime2 ) ) {
        print "compiling $file to $file_svg\n";
        `dot -Tsvg $file -o $file_svg`;
    }
}
