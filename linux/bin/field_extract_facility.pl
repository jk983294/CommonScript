#!/usr/bin/perl
#
# read the in stream for extracting specific fields
#
use strict;
use Env;
$| = 1;    # no buffer, output directly

my $PREV_LINE;

sub print_help {
    my $script_name = `basename $0`;
    chomp($script_name);
    print "Extract data fields from rtmd utility, input is STDIN\n";
    print "  $script_name <field>[,<field>] [|1|2|3] \n";
    print "    field  field interested (or '\*' for wildcard)\n";
    print "    Option blank->UNIX time\n";
    print "           1->Localtime \n";
    print "           2->no time \n";
    print "           3->UNIX time without symbol (for time comparison)\n";
    exit;
}

if ( $ARGV[0] eq "" ) {
    $ARGV[0] = '*';
}

# list of symbol should be shown in sequence, some default fields are included
my @pre_field_list = qw(e id );
my %pre_field_map;
$pre_field_map{"id"} = 1;
$pre_field_map{"e"}  = 1;
if ( $ARGV[1] eq "" ) {
    $ARGV[1] = "1";
}

# get the field list and remove the deplication
my @field_list = ( sort( split ",", $ARGV[0] ) );
my @new_field_list;
foreach my $field (@field_list) {
    my $flag = 0;

    # remove duplication
    foreach my $lookup (@pre_field_list) {
        if ( $lookup eq $field ) { $flag = 1; }
    }

    # remove duplication
    foreach my $lookup2 (@new_field_list) {
        if ( $lookup2 eq $field ) { $flag = 1; }
    }

    if ( !$flag ) { @new_field_list = ( @new_field_list, $field ); }
}
@field_list = @new_field_list;

my $showtime = $ARGV[1];

# message loop
my %field_pair;
while (<STDIN>) {
    my $output = "";
    my $input  = $_;

    my @fv_pairs = split " ,", $input;
    undef %field_pair;

    # push the list into the hash array
    my $output = "";
    foreach my $i ( 0 .. $#fv_pairs ) {
        my $fPair = $fv_pairs[$i];
        $fPair =~ s/ /./g;    # convert all space to dot
        $fPair =~ s/\./ /;    # make first dot back to space to resolve value contains space issue
        my ( $field, $value ) = split " ", $fPair;    # get key value pair

        $field_pair{$field} = $value;
    }

    # convert the time stamp from UNIX time (nanosecond) into localtime
    my $time;
    if ( defined( $field_pair{"rcvt"} ) ) { $time = $field_pair{"rcvt"}; }

    if ( $showtime eq "1" ) {
        if ($time) {
            my ( $y, $m, $d, $ss, $mm, $hh ) = ( localtime( $time / 1000000000 ) )[5, 4, 3, 0, 1, 2];
            $y += 1900;
            $m += 1;
            $time = sprintf "%02d/%02d/%02d-%02d:%02d:%02d", $y, $m, $d, $hh, $mm, $ss;
        }
    } elsif ( $showtime eq "2" ) {
        $time = "";
    }

    # generate the header (include predefined fields)
    my $header_output = "";
    foreach my $field (@pre_field_list) {
        if ( $field_pair{$field} ) {
            $header_output = sprintf( "%s%s %s ,", $header_output, $field, $field_pair{$field} );
        }
    }

    # generate other fields
    $output = "";

    # if wildcard is specified
    if ( $field_list[0] eq "*" ) {
        foreach my $field ( sort keys %field_pair ) {
            if ( $field ne ";" and ( !exists $pre_field_map{$field} ) ) {
                if ( $field_pair{$field} eq "" ) {
                    $output = sprintf( "%s%s ,", $output, $field );
                } else {
                    $output = sprintf( "%s%s %s ,", $output, $field, $field_pair{$field} );
                }
            }
        }
    } else {
        foreach my $field (@field_list) {
            if ( exists( $field_pair{$field} ) and ( !exists $pre_field_map{$field} ) ) {
                if ( $field_pair{$field} eq "" ) {
                    $output = sprintf( "%s%s ,", $output, $field );
                } else {
                    $output = sprintf( "%s%s %s ,", $output, $field, $field_pair{$field} );
                }
            }
        }
    }

    # generate the time stamp
    if ( $output ne "" ) {
        $output = $time . " ," . $header_output . $output . ";";

        if ( $ARGV[1] eq "3" ) { $output = "TIME " . $output; }

        print "$output \n";
    }
}
