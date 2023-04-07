#!/bin/bash

# bash (and maybe other shells) keep a hash of recently used commands to make finding them easier. 
# Sometimes you have to purge the cache (using hash -r) if you change your PATH or program locations'
# https://superuser.com/a/238992/1270480

echo "start tests..."
orig_path=$PATH
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
rm -rf outfile
unset PATH
./pipex infile cat "wc -l" outfile
/bin/echo $?
PATH=$orig_path
cat outfile

echo "original"
rm -rf outfile
unset PATH
< infile cat | wc -l > outfile
echo $?
export PATH=$orig_path
cat outfile

# ---------------------
# Testing manual commands in PATH
# ---------------------
cmd_dir="/Users/cherrewi/Documents/repositories/pipex/tests/test_cmds"
mkdir -p $cmd_dir
PATH+=":"$cmd_dir
rm -rf $cmd_dir/hello_world
echo -e '#!/bin/bash\necho "hello world!!"' > $cmd_dir/hello_world
chmod 755 $cmd_dir/hello_world
hash -r

# ---------------------
# manual command in path WITH permission
echo "---------------------"
echo "test 6"
rm -rf outfile
./pipex infile cat hello_world outfile
echo $?
cat outfile

echo "original"
rm -rf outfile
< infile cat | hello_world > outfile
echo $?
cat outfile


# ---------------------
# manual command in path WITHOUT permission
echo "---------------------"
echo "test 7"
rm -rf outfile
chmod 000 $cmd_dir/hello_world
hash -r
./pipex infile cat hello_world outfile
echo $?
cat outfile

echo "original"
rm -rf outfile
< infile cat | hello_world > outfile
echo $?
cat outfile
rm -rf $cmd_dir  # cleanup


# ---------------------
# Testing manual commands in local directory
# ---------------------
rm -rf hello_world
echo -e '#!/bin/bash\necho "hello world!!"' > hello_world
chmod 755 hello_world


# ---------------------
# commands in local dir (with unset PATH) with permission
echo "---------------------"
echo "test 8"
unset PATH
hash -r
/bin/rm -rf outfile
./pipex infile hello_world hello_world outfile
/bin/echo $?
/bin/cat outfile

echo "original"
/bin/rm -rf outfile
< infile hello_world | hello_world > outfile
/bin/echo $?
/bin/cat outfile

# ---------------------
# commands in local dir (with unset PATH) without permission
echo "---------------------"
echo "test 9"
/bin/chmod 000 hello_world
/bin/rm -rf outfile
/usr/bin/hash -r
./pipex infile hello_world hello_world outfile
/bin/echo $?
/bin/cat outfile

echo "original"
/bin/rm -rf outfile
< infile hello_world | hello_world > outfile
/bin/echo $?
/bin/cat outfile
export PATH=$orig_path

# ---------------------
# Double errors
# ---------------------
echo "---------------------"
echo "test 10"
rm -rf outfile
./pipex infile ls3 ls3 outfile  # also try 10x manual, the error messages might get scrambled
echo $?
cat outfile

echo "original"
rm -rf outfile
< infile ls3 | ls3 > outfile
echo $?
cat outfile

# ---------------------
# outfile no privileges
echo "---------------------"
echo "test 11"
rm -rf outfile
touch outfile
chmod 000 outfile
./pipex infile cat "wc -l" outfile
echo $?
chmod 644 outfile
cat outfile

echo "original"
rm -rf outfile
touch outfile
chmod 000 outfile
< infile cat | wc -l > outfile
echo $?
chmod 644 outfile
cat outfile
rm -rf outfile

# ---------------------
# commands with full path
echo "---------------------"
echo "test 12"
rm -rf outfile
./pipex infile "/bin/cat" "/usr/bin/wc -l" outfile
echo $?
cat outfile

echo "original"
rm -rf outfile
< infile /bin/cat | /usr/bin/wc -l > outfile
echo $?
cat outfile
rm -rf outfile


# ---------------------
# command twice in path without and with access rights
echo "---------------------"
echo "test 13"

cmd_dir="/Users/cherrewi/Documents/repositories/pipex/tests/test_cmds"
cmd_dir2="/Users/cherrewi/Documents/repositories/pipex/tests/test_cmds2"
mkdir -p $cmd_dir
mkdir -p $cmd_dir2
PATH+=":"$cmd_dir
PATH+=":"$cmd_dir2
rm -rf $cmd_dir/hello_world
rm -rf $cmd_dir2/hello_world
echo -e '#!/bin/bash\necho "hello world!!"' > $cmd_dir/hello_world
echo -e '#!/bin/bash\necho "hello world 2!!"' > $cmd_dir2/hello_world
chmod 000 $cmd_dir/hello_world
chmod 755 $cmd_dir2/hello_world
hash -r

rm -rf outfile
./pipex infile cat hello_world outfile
echo $?
cat outfile

echo "original"
rm -rf outfile
< infile cat | hello_world > outfile
echo $?
cat outfile

# ---------------------
# command in path without access rights, and local with access rights
echo "---------------------"
echo "test 13: TODO!!"


# ---------------------
# Cleanup
# ---------------------
rm -rf hello_world
