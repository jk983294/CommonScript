#!/usr/bin/perl
use strict;
use warnings;

sub clean_up_by_extension {
    my ($extension) = @_;
    my @list = <*.$extension>;
    if ( scalar @list > 0 ) {
        my @files = `ls *.$extension`;

        foreach my $file (@files) {
            chomp $file;
            my ($file_no_extension) = ( $file =~ /(.*).$extension/ );

            if ( -e "$file_no_extension.o" ) {
                `rm -f $file_no_extension.o`;
            }

            if ( -e $file_no_extension ) {
                `rm -f $file_no_extension`;
            }
        }
    }
}

clean_up_by_extension('c');
clean_up_by_extension('cpp');

if ( -e "a.out" ) {
    `rm -f a.out`;
}

`rm -f *.so`;
`rm -f *.o`;
`rm -f *.i`;
`rm -f *.s`;
