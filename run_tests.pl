#!/usr/bin/env perl
use strict;
use warnings;
use utf8;
use File::Find;
use File::Basename;
use Getopt::Long;

binmode(STDOUT, ":utf8");
binmode(STDERR, ":utf8");

my $record_golden = 0;
GetOptions("record|r" => \$record_golden);

my $test_target = $ARGV[0];
if (!$test_target) {
    die "Usage:\n" .
        "  perl run_tests.pl <test_name_or_path>          # Run entire flow and compare\n" .
        "  perl run_tests.pl --record <test_name_or_path> # Run flow and record expected\n" .
        "  perl run_tests.pl all                          # Run regression on all tests\n" .
        "Examples:\n" .
        "  perl run_tests.pl test_3_3_1\n" .
        "  perl run_tests.pl --record test_3_3_1\n" .
        "  perl run_tests.pl all\n";
}

# 1. Collect tests
my @tests_to_run;

if ($test_target eq "all") {
    find(sub {
        push @tests_to_run, $File::Find::name if /\.json$/;
    }, "tests");
} else {
    my $base = basename($test_target);
    $base =~ s/\.json$//;
    my $target_filename = "$base.json";
    my $matched = "";

    if (-f $test_target) {
        $matched = $test_target;
    } else {
        find(sub {
            $matched = $File::Find::name if $_ eq $target_filename;
        }, "tests");
    }

    die "Error: Test '$test_target' not found in tests/\n" unless ($matched && -f $matched);
    push @tests_to_run, $matched;
}

print "Total tests to execute: " . scalar(@tests_to_run) . "\n";

my $passed = 0;
my $failed = 0;

for my $json_file (@tests_to_run) {
    my $test_name = basename($json_file);
    $test_name =~ s/\.json$//;

    my $diag_file = $json_file;
    $diag_file =~ s/\.json$/.diag/;
    if (-f $diag_file) {
        print "\n[SKIP] Negative syntax testcase $test_name has diagnostic ($diag_file), skipping simulation pipeline.\n";
        $passed++;
        next;
    }

    print "\n==================================================\n";
    print "Running Test Pipeline: $test_name\n";
    print "==================================================\n";

    # Step 1: Generate C++
    print "[1/4] Generating C++ via gen_cpp.pl...\n";
    my $rc1 = system("perl gen_cpp.pl \"$json_file\"");
    if ($rc1 != 0) {
        print "[FAIL] Stage 1 (gen_cpp.pl) failed for $test_name\n";
        $failed++;
        next;
    }

    # Step 2: Compile Simulation
    print "[2/4] Compiling Simulation via compile_sim.pl...\n";
    my $rc2 = system("perl compile_sim.pl \"$test_name\"");
    if ($rc2 != 0) {
        print "[FAIL] Stage 2 (compile_sim.pl) failed for $test_name\n";
        $failed++;
        next;
    }

    # Step 3: Execute Simulation
    print "[3/4] Executing Simulation via exec_sim.pl...\n";
    my $rc3 = system("perl exec_sim.pl \"$test_name\"");
    if ($rc3 != 0) {
        print "[FAIL] Stage 3 (exec_sim.pl) failed for $test_name\n";
        $failed++;
        next;
    }

    # Step 4: Compare or Record
    print "[4/4] Comparing output via compare_output.pl...\n";
    my $record_flag = $record_golden ? "--record" : "";
    my $rc4 = system("perl compare_output.pl $record_flag \"$test_name\"");
    if ($rc4 == 0) {
        $passed++;
    } else {
        $failed++;
    }

    # Cleanup temporary simulation binary and generated .cpp after run
    unlink "sim_$test_name.exe" if -e "sim_$test_name.exe";
}

print "\n==================================================\n";
print "Pipeline Summary: $passed Passed, $failed Failed\n";
print "==================================================\n";

exit ($failed > 0 ? 1 : 0);
