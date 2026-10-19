#!/usr/bin/env perl
use strict;
use warnings;
use utf8;
use File::Find;
use File::Copy;
use File::Basename;

binmode(STDOUT, ":utf8");
binmode(STDERR, ":utf8");

my $test_target = $ARGV[0];
if (!$test_target) {
    die "Usage: perl gen_cpp.pl <test_name_or_path>\n" .
        "Example: perl gen_cpp.pl test_3_3_1\n";
}

# 1. Ensure json2verif.exe exists
if (! -e "json2verif.exe") {
    print "json2verif.exe not found. Running compile.pl...\n";
    my $rc = system("perl compile.pl");
    die "Error: Failed to build json2verif.exe\n" if $rc != 0;
}

# 2. Find target test JSON
my $base_name = $test_target;
$base_name =~ s/\.json$//;
my $target_filename = basename("$base_name.json");
my $matched_path = "";

if (-f $test_target) {
    $matched_path = $test_target;
} else {
    find(sub {
        if ($_ eq $target_filename) {
            $matched_path = $File::Find::name;
        }
    }, "tests");
}

die "Error: Test '$test_target' not found in tests/\n" unless ($matched_path && -f $matched_path);

my $actual_test_base = basename($matched_path);
$actual_test_base =~ s/\.json$//;

print "Translating AST JSON -> C++ for: $actual_test_base\n";

# 3. Copy test JSON to sam_ folder safely using Python with Unicode codepoints for Windows
my $safe_path = $matched_path;
$safe_path =~ s{\\}{/}g;
system(qq{python -c "import os, shutil, sys; d=''.join(chr(c) for c in [115,97,109,95,2310,2344,2381,2340,2352,2367,2325,2325,2369,2334,2381,2332,2368,2350,2370,2354,2381,2351,2352,2370,2346,2350,2381]); os.makedirs(d, exist_ok=True); [os.remove(os.path.join(d, x)) for x in os.listdir(d)]; shutil.copy(sys.argv[1], d)" "$safe_path"});

# 4. Run json2verif.exe
my $rc = system("json2verif.exe");
if ($rc != 0) {
    die "Error: json2verif.exe translation failed with code $rc\n";
}

my $generated_cpp = "$actual_test_base.cpp";
if (! -e $generated_cpp) {
    die "Error: $generated_cpp was not created by json2verif.exe!\n";
}

print "Success: Created $generated_cpp\n";
exit(0);
