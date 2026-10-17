#!/usr/bin/env perl
use strict;
use warnings;
use utf8;
use File::Find;
use File::Basename;

binmode(STDOUT, ":utf8");
binmode(STDERR, ":utf8");

my $test_target = $ARGV[0];
if (!$test_target) {
    die "Usage: perl exec_sim.pl <test_name>\n" .
        "Example: perl exec_sim.pl test_3_3_1\n";
}

my $base_name = basename($test_target);
$base_name =~ s/\.(exe|cpp|json)$//;

my $sim_exe = "sim_$base_name.exe";
if (! -e $sim_exe) {
    die "Error: Simulation binary '$sim_exe' not found! Run 'perl compile_sim.pl $base_name' first.\n";
}

# Find test directory to place actual output next to test
my $target_filename = "$base_name.json";
my $matched_path = "";
find(sub {
    if ($_ eq $target_filename) {
        $matched_path = $File::Find::name;
    }
}, "tests");

my $test_dir = $matched_path ? dirname($matched_path) : "tests";
my $actual_out = "$test_dir/$base_name.actual.out";

print "Executing simulation: $sim_exe -> $actual_out\n";
my $rc = system("$sim_exe > \"$actual_out\" 2>&1");

if ($rc != 0) {
    print "Warning: Simulation returned non-zero exit code $rc\n";
} else {
    print "Success: Simulation completed. Output saved to $actual_out\n";
}

exit(0);
