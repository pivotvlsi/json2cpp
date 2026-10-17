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

# 3. Copy test JSON to sam_ folder safely using Python for Windows UTF-8 path handling
system(qq{python -c "import os, shutil; d='sam_आन्तरिककुञ्जीमूल्यरूपम्'; os.makedirs(d, exist_ok=True); [os.remove(os.path.join(d, x)) for x in os.listdir(d)]; shutil.copy(r'$matched_path', d)"});

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
