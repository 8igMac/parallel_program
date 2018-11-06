Parallel Programming Practice Code
===
> Written in c++

# Table of Content
1. [Pthread Programming](#pthread-programming)

# Pthread Programming
This is a program that simulates throwing darts on a suqare dartboard
randomly to estimate the value of **pi**, which is called Monte Carlo
 method. 

**The program takes two arguments, which the CPU cores and
the number of tosses.**

## How to run
1. compile
```
$ g++ pi.cpp -o thread -lpthread
```
2. execute
```
$ sh run.sh NUM_CORE NUM_TOSS
```

# OpenMP Programming
Parallelize a serial implementaion of the conjugate gradient 
method using OpenMP.

## How to run
1. build 
```
$ make DATASIZE=[LARGE|MEDIUMN|SMALL]
# (If not assign DATASIZE, default will be mediumn)
# Please do make clean if you want to change datasize.
```
2. run
```
$ ./bin/cg
```
3. clean 
```
$ make clean
```
