# README
[![Build Status](https://travis-ci.org/FilippoRanza/bfi.svg?branch=master)](https://travis-ci.org/FilippoRanza/bfi)
## What is bfi? ##
bfi is a **Brainfuck** interpreter.
bfi can execute programs from file,command line 
or its interactive shell.

This interpreter checks **Brainfuck** and make
some simple _optimizations_ 

## Installation: ##
cmake CMakeList.txt && make && make install

After a successful installation you should run 
**[sudo] mandb**, to update manpages databse.

### Ubuntu ###
Install, using apt(or equivalent), _libreadline6_ and _libreadline6-dev_

### Arch ###
Search on the **AUR**

ATTENTION:
bfi needs GNU Readline library
ensure you have readline run-time and
developer version installed to compile
and run bfi.

## Usage: ##
bfi _[option...]_ _[-e code | file ]_ _[argument..]_
for a complete guide read manual at
man bfi

## Tests ##
This program uses a custom test method:

test directory contains server subdirectories, each implements a specific test,
all those tests are run, and is every test success then the test is considered completed successfully.

Each test checks a bfi's feature: submits some code in way accepted by bfi, then the output in compared 
with expected  output, the test success if those outputs are equal, fails otherwise.
 
 