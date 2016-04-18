#!/bin.sh -e

Sep="\n=================================\n"

printf "\nBuffered input and output using system calls\n"

clang-3.5 -o buffer 002.c
./buffer input.txt output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
