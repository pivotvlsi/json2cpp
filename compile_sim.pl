#!/usr/bin/env perl
use strict;
use warnings;
use utf8;
use File::Basename;

binmode(STDOUT, ":utf8");
binmode(STDERR, ":utf8");

my $test_target = $ARGV[0];
if (!$test_target) {
    die "Usage: perl compile_sim.pl <test_name>\n" .
        "Example: perl compile_sim.pl test_3_3_1\n";
}

my $base_name = basename($test_target);
$base_name =~ s/\.(cpp|json)$//;

my $cpp_file = "$base_name.cpp";
if (! -e $cpp_file) {
    die "Error: C++ file '$cpp_file' not found! Run 'perl gen_cpp.pl $base_name' first.\n";
}

# 1. Create runner harness to instantiate the module
my $runner_cpp = "sim_runner_$base_name.cpp";
open my $rfh, '>', $runner_cpp or die "Cannot create $runner_cpp: $!";
print $rfh qq{
#include "$cpp_file"

int main() {
    $base_name dut;
    return 0;
}
};
close $rfh;

# 2. Compile simulation executable
my $sim_exe = "sim_$base_name.exe";
print "Compiling simulation binary: $sim_exe...\n";
my $cmd = "g++ -std=c++17 -I. -I./primitive_cpp $runner_cpp primitive_cpp/definitions.cpp -o $sim_exe";
my $rc = system($cmd);

# Clean up harness file
unlink $runner_cpp;

if ($rc != 0) {
    die "Error: Compilation of $sim_exe failed with code $rc\n";
}

print "Success: Created $sim_exe\n";
exit(0);
