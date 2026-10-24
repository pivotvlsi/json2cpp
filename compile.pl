#!/usr/bin/env perl
use strict;
use warnings;
use utf8;
use File::Find;
use File::Copy;
use File::Path qw(make_path remove_tree);
use File::Basename;

# Set binmode for proper UTF-8 console output
binmode(STDOUT, ":utf8");
binmode(STDERR, ":utf8");
#Compile DPI functions
print "Building libdpi...\n";
system("g++ -shared -O2 -I. dpi/dpi.cpp -o libdpi.dll -Wl,--out-implib,libdpi.a");

# 1. Compile json2map static library if libjson2map.a doesn't exist
if (! -e "json2map_cpp/libjson2map.a") {
    print "Building libjson2map.a...\n";
    system("g++ -std=c++17 -I./json2map_cpp -c json2map_cpp/json2map.cpp -o json2map_cpp/json2map.o");
    system("g++ -std=c++17 -I./json2map_cpp -c json2map_cpp/convert2code.cpp -o json2map_cpp/convert2code.o");
    system("ar rcs json2map_cpp/libjson2map.a json2map_cpp/json2map.o json2map_cpp/convert2code.o");
}

# 2. Compile json2verif.exe
print "Building json2verif.exe...\n";
my $cmd = "g++ -std=c++17 -I./json2cpp_cpp -I./json2map_cpp " .
    "json2verif_cpp/json2verif.cpp " .
    "json2cpp_cpp/convertjson2cpp.cpp " .
    "json2cpp_cpp/top_module_krama.cpp " .
    "json2cpp_cpp/update_initial_begin_block.cpp " .
    "json2cpp_cpp/update_always_begin_block.cpp " .
    "json2cpp_cpp/update_initial_if_block.cpp " .
    "json2cpp_cpp/update_initial_elseif_block.cpp " .
    "json2cpp_cpp/update_initial_elseonly_block.cpp " .
    "json2cpp_cpp/check_expr.cpp " .
    "json2cpp_cpp/check_expr_initial_block.cpp " .
    "json2cpp_cpp/check_expr_always_block.cpp " .
    "json2cpp_cpp/gen_statements.cpp " .
    "-L./json2map_cpp -ljson2map " .
    "-o json2verif.exe";

my $status = system($cmd);
if ($status != 0) {
    die "Compilation failed with exit code: $status\n";
} else {
    print "Compilation successful -> json2verif.exe\n";
}


print "Building gen_main.exe...\n";
my $status_main = system("g++ -std=c++17 json2cpp_cpp/gen_main.cpp -o gen_main.exe");
if ($status_main != 0) {
    die "Failed to compile gen_main.exe\n";
}
print "Compilation successful -> gen_main.exe\n";
