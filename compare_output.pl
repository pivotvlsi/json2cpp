#!/usr/bin/env perl
use strict;
use warnings;
use utf8;
use File::Find;
use File::Copy;
use File::Basename;
use Getopt::Long;

binmode(STDOUT, ":utf8");
binmode(STDERR, ":utf8");

my $record_golden = 0;
GetOptions("record|r" => \$record_golden);

my $test_target = $ARGV[0];
if (!$test_target) {
    die "Usage:\n" .
        "  perl compare_output.pl <test_name>          # Compare actual vs expected output\n" .
        "  perl compare_output.pl --record <test_name> # Record actual as expected\n";
}

my $base_name = basename($test_target);
$base_name =~ s/\.(out|actual|expected|cpp|json)$//;
$base_name =~ s/\.actual$//;

# Locate test directory
my $matched_path = "";
find(sub {
    if ($_ eq "$base_name.json") {
        $matched_path = $File::Find::name;
    }
}, "tests");

my $test_dir = $matched_path ? dirname($matched_path) : "tests";
my $actual_out   = "$test_dir/$base_name.actual.out";
my $expected_out = "$test_dir/$base_name.expected.v.out";

if (! -e $actual_out) {
    die "Error: Actual output file '$actual_out' not found! Run 'perl exec_sim.pl $base_name' first.\n";
}

# 1. Record mode
if ($record_golden) {
    copy($actual_out, $expected_out) or die "Failed to record expected file: $!";
    print "[RECORDED] Saved expected output:\n  $expected_out\n";
    exit(0);
}

# 2. Check if expected file exists
if (! -e $expected_out) {
    print "[WARN] Expected file '$expected_out' does not exist.\n";
    print "Run with '--record' to establish this output as expected:\n";
    print "  perl compare_output.pl --record $base_name\n";
    exit(1);
}

# 3. Pure-Perl line-by-line comparison
sub read_lines {
    my ($file) = @_;
    open my $fh, '<', $file or die "Cannot read $file: $!";
    my @lines = <$fh>;
    close $fh;
    s/\r?\n$// for @lines;
    return @lines;
}

my @exp = read_lines($expected_out);
my @act = read_lines($actual_out);

my $diff = 0;
my $max = scalar(@exp) > scalar(@act) ? scalar(@exp) : scalar(@act);

for (my $i = 0; $i < $max; $i++) {
    my $e = defined $exp[$i] ? $exp[$i] : "<EOF>";
    my $a = defined $act[$i] ? $act[$i] : "<EOF>";
    if ($e ne $a) {
        if (!$diff) {
            print "\n=== [FAIL] Output mismatch for $base_name! ===\n";
            $diff = 1;
        }
        my $num = $i + 1;
        print "Line $num:\n";
        print "  Expected: $e\n";
        print "  Actual:   $a\n";
    }
}

if (!$diff) {
    print "\n=== [PASS] Output matches expected result for $base_name! ===\n";
    exit(0);
} else {
    exit(1);
}
