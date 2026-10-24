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

# 1. Generate main.cpp simulation harness via gen_main.exe
if (! -e "gen_main.exe") {
    system("g++ -std=c++17 json2cpp_cpp/gen_main.cpp -o gen_main.exe");
}
my $rc_main = system("gen_main.exe");
if ($rc_main != 0 || ! -e "main.cpp") {
    die "Error: gen_main.exe failed to generate main.cpp\n";
}

# 2. Compile simulation executable
my $sim_exe = "sim_$base_name.exe";
my $cmd = "g++ -std=c++17 -I. -I./primitive_cpp main.cpp primitive_cpp/definitions.cpp primitive_cpp/initial_begin_check_basic_equality.cpp -L. -ldpi -o $sim_exe";
my $rc = system($cmd);

# Clean up generated main.cpp
unlink "main.cpp" if -e "main.cpp";

if ($rc != 0) {
    die "Error: Compilation of $sim_exe failed with code $rc\n";
}

print "Success: Created $sim_exe\n";
exit(0);
