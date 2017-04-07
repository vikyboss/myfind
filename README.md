# myfind
A mini implementation of find command that lists all files and directories.

# Test
```
$ cd myfind/
$ make test
cc -o myfind myfind.c -Wall -Werror
*********** STARTING TEST SETUP ***********
mkdir -p test
mkdir -p test/a
mkdir -p test/b
touch test/a/1
touch test/b/1
touch test/c
*********** ENDING TEST SETUP ***********

*********** STARTING TEST 1 ***********
./myfind test
test
test/a
test/a/1
test/b
test/b/1
test/c
***********  ENDING TEST 1  ***********

*********** STARTING TEST 2 ***********
./myfind test test test/c test/a/1
test
test/a
!!! ignoring test/a/1 !!!
test/b
test/b/1
!!! ignoring test/c !!!
***********  ENDING TEST  2 ***********
```
