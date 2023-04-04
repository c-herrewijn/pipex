#!/bin/bash

echo "start tests..."
cd /Users/cherrewi/Documents/repositories/pipex/
echo -e "aa line 1\nbb line2\ncc line3" > infile

# ---------------------
# correct
echo "---------------------"
echo "test 1"
rm -rf outfile
./pipex infile cat "wc -l" outfile
echo $?
cat outfile

echo "original"
rm -rf outfile
< infile cat | wc -l > outfile
echo $?
cat outfile

# ---------------------
# wrong function name 2nd function
echo "---------------------"
echo "test 2"
rm -rf outfile
./pipex infile cat "wcX -l" outfile
echo $?
cat outfile

echo "original"
rm -rf outfile
< infile cat | wcX -l > outfile
echo $?
cat outfile


# ---------------------
# wrong argvars 2nd function
echo "---------------------"
echo "test 3"
rm -rf outfile
./pipex infile cat "wc -Q" outfile
echo $?
cat outfile

echo "original"
rm -rf outfile
< infile cat | wc -Q > outfile
echo $?
cat outfile

# ---------------------
# infile no privileges
echo "---------------------"
chmod 000 infile
echo "test 4"
rm -rf outfile
./pipex infile cat "wc -l" outfile
echo $?
cat outfile

echo "original"
rm -rf outfile
< infile cat | wc -l > outfile
echo $?
cat outfile
chmod 644 infile

# ---------------------
# unset Path
echo "---------------------"
echo "test 5"
temp_path=$PATH
rm -rf outfile
unset PATH
./pipex infile cat "wc -l" outfile
echo $?
PATH=$temp_path
cat outfile

echo "original"
rm -rf outfile
unset PATH
< infile cat | wc -l > outfile
echo $?
PATH=$temp_path
cat outfile

# ---------------------
# todo: commands in path without permission

# ---------------------
# todo: commands in local dir (with unset PATH) with permission

# ---------------------
# todo: commands in local dir (with unset PATH) without permission
