# myfind
A mini implementation of find command that lists all files and directories

# Test
```
$ cd myfind/
$ make test
mkdir -p test
mkdir -p test/a
mkdir -p test/b
touch test/a/1
touch test/b/1
touch test/c
*********** STARTING TEST ***********
./myfind test
test
test/a
test/a/1
test/b
test/b/1
test/c
***********  ENDING TEST  ***********
*********** STARTING TEST ***********
./myfind test test test/c test/a/1
test
test/a
!!! ignoring test/a/1 !!!
test/b
test/b/1
!!! ignoring test/c !!!
***********  ENDING TEST  ***********
```
