#!/usr/bin/perl

use strict;
use warnings;
use File::Basename;
use Getopt::Std;
use FileHandle;
use Sys::Hostname;
use Term::ANSIColor;
use Term::ReadLine;
use Text::ParseWords;

package main;

# example: ./pstart.pl -f filename

#-----------------------------------------
# Global Variables
#-----------------------------------------
my ( $processOpt, $nameOpt, $expandedCmdLine );

my $filename;
my $output = "";

my $currentHost;

my $adminScriptFile = "admin";
my $adminScriptPath = "/home/kun/bin/admin";

#-----------------------------------------
# Functions
#-----------------------------------------
sub trim {
    my @result = ();
    foreach my $inStr (@_) {
        $inStr =~ s/^\s+//;
        $inStr =~ s/\s+$//;
        push( @result, $inStr );
    }
    return (@result);
}

sub parse_environment_entry {
    return quotewords( "," => 1, $_[0] );
}

#-----------------------------------------
sub LogToFile {
    my ($str) = @_;
    my $t = localtime( time() );
    print LOG_FILE "$t: $str\n";
}

sub splitRDLine {
    my ( $line_data, $line_out_hashref, $log_file ) = @_;
    my %keywords = (
        "feed", 1, "process", 1, "mode", 0, "instance", 0, "data", 0, "enabled", 1, "start_name", 2, "executable", 2,
        "cmd_line", 0, "env_file", 0, "environment", 0, "input_feed_upstream", 0
    );
    my @line = split( /~/, $line_data );
    my ( $name, $host, $value, $enabled );
    my $input_feeds = {};
    my $file_hash   = {};

    ($host) = trim( $line[0] );
    $line_out_hashref->{"host"} = $host;
    my $firstItem = 1;
    foreach my $nv_pair (@line) {
        if ($firstItem) {
            $firstItem = 0;
            next;
        }
        ( $name, $value ) = trim( split( /=/, $nv_pair ) );
        if ( $name =~ /file_/ ) {
            $file_hash->{"$name"} = $value;
        } elsif ( $name =~ /input_feed/ ) {
            $input_feeds->{"$name"} = $value;
        } else {
            $line_out_hashref->{"$name"} = $value;
        }
    }

    if ( keys(%$input_feeds) != 0 ) {
        $line_out_hashref->{"input_feed"} = $input_feeds;
    }
    if ( keys(%$file_hash) != 0 ) {
        $line_out_hashref->{"file_hash"} = $file_hash;
    }
    return ($line_out_hashref);
}

#-----------------------------------------
sub DoStartProcessing {
    my ($input) = @_;

    my $line_hashref = {};

    $line_hashref = splitRDLine( $input, $line_hashref, *LOG_FILE );
    my $host       = $line_hashref->{"host"};
    my $feed       = $line_hashref->{"feed"};
    my $region     = $line_hashref->{"region"};
    my $process    = $line_hashref->{"process"};
    my $data       = $line_hashref->{"data"};
    my $enabled    = $line_hashref->{"enabled"};
    my $start_name = $line_hashref->{"start_name"};
    my $executable = $line_hashref->{"executable"};
    my $cmd_line   = $line_hashref->{"cmd_line"};

    return if ( ( $host ne "localhost" ) && ( $host ne $currentHost ) );

    if ( $enabled ne "t" )   { return; }
    if ( $feed eq "" )       { return; }
    if ( $process eq "" )    { return; }
    if ( $enabled eq "" )    { return; }
    if ( $start_name eq "" ) { return; }
    if ( $executable eq "" ) { return; }
    if ( $data eq "" )       { LogToFile("WARNING: `data' is blank in entry: $input\n"); }
    if ( $cmd_line eq "" )   { LogToFile("WARNING: `cmd_line' is blank in entry: $input\n"); }

    return if ( $nameOpt    && ( $nameOpt ne $start_name ) );
    return if ( $processOpt && ( $processOpt ne $process ) );

    LogToFile("About to start $start_name based on: \n$input\n");
    StartProcess($line_hashref);
    return;
}

#-----------------------------------------
sub StartProcess {
    my ($line_hashref) = @_;

    my ( $start_name, $executable, $cmd_line, $process );
    $start_name = $line_hashref->{"start_name"};
    $executable = $line_hashref->{"executable"};
    $cmd_line   = $line_hashref->{"cmd_line"};
    $process    = $line_hashref->{"process"};

    # check if executable exists.
    if ( !( -e "$executable" ) ) {
        LogToFile("ERROR: $executable does not exist.");
    } else {
        LogToFile("NOTICE: $executable exists.");
    }

    # if ctl file is in cmd_line, check for existence of ctl file
    my @line = trim( split( ' ', $cmd_line ) );
    my $i    = @line;
    my $j    = 0;
    while ( $j < $i ) {
        if ( $line[$j] eq "-c" ) {
            $j++;
            if ( $j < $i ) {
                my $ctl = $line[$j];
                if ( !( -e $ctl ) ) {
                    LogToFile("ERROR: cannot find ctl file: $ctl");
                } else {
                    LogToFile("NOTICE: ctl file found: $ctl");
                }
            } else {
                LogToFile("WARNING: -c option found on command line without a ctl file.");
            }
        }
        $j++;
    }

    CreateLinksAndDirectories( $start_name, $executable );
    BuildEnvironment($line_hashref);
    ExecuteEmitCommand( $start_name, $expandedCmdLine );
}

#-----------------------------------------
sub CreateLinksAndDirectories {
    my ( $start_name, $executable ) = @_;
    my $basePath = "/var/tmp";

    # only create the directories and directory links once
    if ( !( -e "$basePath/bin" ) ) {
        LogToFile("Creating dir $basePath/bin");
        if ( !mkdir("$basePath/bin") ) {
            LogToFile("ERROR: mkdir $basePath/bin failed: $!");
            exit(1);
        }
        chmod( 0777, "$basePath/bin" );
    }
    if ( !( -e "$basePath/etc" ) ) {
        LogToFile("Creating dir $basePath/etc");
        if ( !mkdir("$basePath/etc") ) {
            LogToFile("ERROR: mkdir $basePath/etc failed: $!");
            exit(1);
        }
        chmod( 0777, "$basePath/etc" );
    }
    if ( !( -e "$basePath/etc/emit" ) ) {
        LogToFile("Creating dir $basePath/etc/emit");
        if ( !mkdir("$basePath/etc/emit") ) {
            LogToFile("ERROR: mkdir $basePath/etc/emit failed: $!");
            exit(1);
        }
        chmod( 0777, "$basePath/etc/emit" );
    }

    # delete and create symbolic link for actual executable in /var/tmp/bin.
    LogToFile("Creating symlink for actual executable: $basePath/bin/$start_name, Actual process: $executable");
    if ( -l "$basePath/bin/$start_name" ) {
        if ( !unlink("$basePath/bin/$start_name") ) {
            LogToFile("ERROR: unlink $basePath/bin/$start_name failed: $!");
        }
    }
    if ( !symlink( "$executable", "$basePath/bin/$start_name" ) ) {
        LogToFile("ERROR: symlink $basePath/bin/$start_name failed: $!");
        exit(1);
    }
}

#-----------------------------------------
sub BuildEnvironment {
    my ($line_hashref) = @_;

    my $host               = $line_hashref->{"host"};
    my $region             = $line_hashref->{"region"};
    my $process            = $line_hashref->{"process"};
    my $data               = $line_hashref->{"data"};
    my $start_name         = $line_hashref->{"start_name"};
    my $env_file           = $line_hashref->{"env_file"};
    my $environment        = $line_hashref->{"environment"};
    my $input_feed_hashref = $line_hashref->{"input_feed"};
    my $file_hashref       = $line_hashref->{"file_hash"};
    $expandedCmdLine = $line_hashref->{"cmd_line"};

    my @datatypes = trim( split( ",", $data ) );
    my @env_vars = trim( parse_environment_entry($environment) );

    my $ref_datatypes = \@datatypes;
    my $ref_env_vars  = \@env_vars;

    my $basePath = "/var/tmp";

    # create emit file in /var/tmp/etc/emit
    LogToFile("Creating $basePath/etc/emit/$start_name");
    my $results = `rm -f $basePath/etc/emit/$start_name 2>&1`;
    LogToFile("$results");
    if ( !open( OUT_ENV_FILE, ">$basePath/etc/emit/$start_name" ) ) {
        LogToFile("ERROR: open/create $basePath/etc/emit/$start_name failed: $!");
        exit(1);
    }

    # add rd env variables to the emit file
    LogToFile("###### Start of common env from resource discovery ######");
    print OUT_ENV_FILE "###### Start of common env from resource discovery ######\n";

    # We will only execute this header part if the file does not exist yet.
    # (This is because BuildEnvironment gets invoked per every process.)
    # However, we need the $basePath and other variables to correctly build the envvars.
    if ($host) {
        if ( !-e "$basePath/bin/run_$host" ) {
            if ( !open( EXECUTE_SCRIPT, ">>$basePath/bin/run_$host" ) ) {
                LogToFile("ERROR: open/create $basePath/bin/run_$host failed: $!");
            } else {
                chmod( 0777, "$basePath/bin/run_$host" );

                print EXECUTE_SCRIPT "#!/bin/bash\n";
                print EXECUTE_SCRIPT "RD_FEED=$line_hashref->{feed}\n";

                close EXECUTE_SCRIPT;
            }
        }
    }

    print OUT_ENV_FILE "export RD_HOST=\"$host\"\n";
    LogToFile("export RD_HOST=\"$host\"");

    # build the env variables for all of the RD entries except those that need to be parsed further
    foreach my $rd_key ( keys %$line_hashref ) {
        next if ( $rd_key eq "host" );
        next if ( $rd_key eq "input_feed" );
        next if ( $rd_key eq "data" );
        next if ( $rd_key eq "environment" );
        next if ( $rd_key eq "file_hash" );
        next if ( $rd_key eq "cmd_line" );
        my $rd_value = $line_hashref->{$rd_key};
        $rd_value = "" if ( !$rd_value );

        my $oname = "RD_";
        $oname .= uc($rd_key);
        print OUT_ENV_FILE "export $oname=\"$rd_value\"\n";
        LogToFile("export $oname=\"$rd_value\"");
    }

    # file_dir is assigned a default if not present
    if ( !( exists( $line_hashref->{"file_dir"} ) ) ) {
        print OUT_ENV_FILE "export RD_FILE_DIR=\"/var/tmp/rd/\"\n";
        LogToFile("export RD_FILE_DIR = \"/var/tmp/rd/\"");
    }

    # build all of the datatype env variables (datatype:port)
    foreach my $item (@$ref_datatypes) {
        my ( $type, $port ) = trim( split( ":", $item ) );
        $type =~ tr/[a-z]/[A-Z]/;
        LogToFile("export RD_$type=\"$port\"");
        print OUT_ENV_FILE "export RD_$type=\"$port\"\n";
        if ( $type eq "ADMIN" ) {
            print OUT_ENV_FILE "export ADMIN=\"$adminScriptPath $host:$port\"\n";
            LogToFile("export ADMIN=\"$adminScriptPath $host:$port\"");
        }
        if ( $expandedCmdLine =~ /\$RD_$type/ ) {    # replace any variables in cmd line with actual ports
            $expandedCmdLine =~ s/\$RD_$type/$port/g;
        }
    }

    print OUT_ENV_FILE "export RD_CMD_LINE=\"$expandedCmdLine\"\n";
    LogToFile("export RD_CMD_LINE=\"$expandedCmdLine\"");

    # build all of the file name env variables
    if ($file_hashref) {
        foreach my $name ( keys %$file_hashref ) {
            my $value = $file_hashref->{$name};
            my $oname = uc($name);
            print OUT_ENV_FILE "export RD_$oname=\"$value\"\n";
            LogToFile("export RD_$oname=\"$value\"");
        }
    }

    LogToFile("###### End of common env from resource discovery ######");
    print OUT_ENV_FILE "###### End of common env from resource discovery ######\n";

    LogToFile("###### Start of Base env variables for emit ######");
    print OUT_ENV_FILE "export MAXPROCESS=1\n";
    LogToFile("export MAXPROCESS=1");
    print OUT_ENV_FILE "export MAXSPAWN=99\n";
    LogToFile("export MAXSPAWN=99");

    LogToFile("###### End of Base env variables for emit ######");

    # if additional environment variables were specified, add them to the emit file
    if (@$ref_env_vars) {
        LogToFile("###### Start of env listed in start file ######");
        print OUT_ENV_FILE "###### Start of env listed in start file ######\n";
        foreach my $var (@$ref_env_vars) {

            my ( $name, $value ) = trim( split( ":", $var, 2 ) );
            LogToFile("export $name=$value");
            print OUT_ENV_FILE "export $name=$value\n";
        }
        LogToFile("###### End of env listed in start file ######");
        print OUT_ENV_FILE "###### End of env listed in start file ######\n";
    }

    # There can be multiple env files specified
    if ($env_file) {
        my @env_files = trim( split( ",", $env_file ) );
        foreach my $e_file (@env_files) {

            # copy it to emit file
            if ( -e "$e_file" ) {
                LogToFile("###### Start of env copied from file $e_file ######");
                print OUT_ENV_FILE "###### Start of env copied from file $e_file ######\n";
                if ( open( IN_ENV_FILE, "$e_file" ) ) {
                    while (<IN_ENV_FILE>) {
                        chomp;
                        print OUT_ENV_FILE "$_\n";
                        LogToFile("$_");
                    }
                    close(IN_ENV_FILE);
                    LogToFile("###### End of env copied from file $e_file ######");
                    print OUT_ENV_FILE "###### End of env copied from file $e_file ######\n";
                } else {
                    LogToFile("ERROR: open of $e_file failed: $!");
                    print OUT_ENV_FILE "###### Nothing copied from file $e_file ######\n";
                }
            } else {
                print OUT_ENV_FILE "###### Nothing copied from file $e_file ######\n";
                LogToFile("NOTE: env variables were not copied from [$e_file]");
            }
        }
    }

    close(OUT_ENV_FILE);
}

#-----------------------------------------
sub ExecuteEmitCommand {
    my ( $start_name, $cmd_line ) = @_;
    my @ARGS;

    my $EMIT = "/home/kun/github/CommonScript/linux/bin/emit.sh";
    LogToFile("EMIT = $EMIT");

    my $basePath = "/var/tmp";

    push( @ARGS, $EMIT );
    push( @ARGS, "$basePath/bin/$start_name" );
    push( @ARGS, $cmd_line );
    push( @ARGS, "&" );

    my $command = join( ' ', @ARGS );

    LogToFile("Executing: $command\n\n");
    my $results    = `$command`;
    my $exitStatus = 0;
    if ( $? != 0 ) { $exitStatus = "ERROR [$?]"; }
    LogToFile("\nResult: exit code: $exitStatus, $results");
}

sub cleanRDLine {
    my ($line) = @_;
    $_ = $line;
    $_ =~ s/\s+$//;    # remove trailing spaces
    my $last_char = substr( $_, -1 );
    if ( $last_char eq "\\" ) {
        chop;          # get rid of \
        $_ =~ s/\s+$//;
        return ( 1, $_ );
    } else {
        return ( 0, $_ );
    }
}

#-----------------------------------------
# Main
#-----------------------------------------

$| = 1;

if ( !getopts('f:') ) {
    print "getopt error\n";
    exit(1);
}

my $rdFile = basename($::opt_f);

my ( $sec, $min, $hour, $mday, $mon, $year ) = (localtime)[0, 1, 2, 3, 4, 5];
$year += 1900;
$mon  += 1;
my $today = sprintf( "%d%02d%02d.%02d%02d%02d", $year, $mon, $mday, $hour, $min, $sec );
my $logFileName;

if ( !( -e "/var/tmp/pstart" ) ) {
    LogToFile("Creating dir /var/tmp/pstart");
    if ( !mkdir("/var/tmp/pstart") ) {
        LogToFile("ERROR: mkdir /var/tmp/pstart failed: $!");
        exit(1);
    }
    chmod( 0777, "/var/tmp/pstart" );
}
$logFileName = "/var/tmp/pstart/pstart.$rdFile";

if ( !open( LOG_FILE, ">$logFileName.$today" ) ) {
    print "ERROR: cannot open log file /var/tmp/pstart/pstart.$today\n";
}

LogToFile("Admin Script = $adminScriptPath");

# optional arguments
if ($::opt_p) { $processOpt = $::opt_p; }
if ($::opt_n) { $nameOpt    = $::opt_n; }

$currentHost = hostname();
chomp($currentHost);

LogToFile("Using files: $::opt_f\n");

my $line_data = "";
my $last_char;
my $line_num = 0;
my $cont;

my $file = $::opt_f;
LogToFile("Processing file: $file");

# read each entry in the file
open( RDFILE, "< $file" )
    or print "Could not open $file for reading $filename\n"
    and LogToFile("Could not open $file for reading $filename\n")
    and next;

while (<RDFILE>) {
    chomp;
    $line_num++;
    next if /^#/;    # ignore comments
    if (/^\s*$/) {   # ignore blank lines

        # if $line_data contains anything then we assume that the entry is complete and should be processed
        # this happens when someone accidentally leaves a \ at the end of the last line of an entry
        if ($line_data) {
            LogToFile(
                "WARNING: Line $line_num, Previous line contains invalid continuation character '\\'. Assuming end of entry. \n"
            );
        }
        next if ( !$line_data );
    }

    ( $cont, $_ ) = cleanRDLine($_);
    $line_data .= $_;
    next if ( $cont == 1 );

    LogToFile("DoStartProcessing $line_data\n");
    DoStartProcessing($line_data);
    $line_data = "";
}
close(RDFILE);
$line_num = 0;

close(LOG_FILE);
exit(0);
