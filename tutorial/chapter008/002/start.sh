#!/bin.sh -e

sep="\n=================================\n"

printf "\nBuffered input and output using system calls\n"

clang-3.5 -o buffer 002.c
./buffer input1.txt r output.txt w
./buffer input2.txt r output.txt a

printf "$sep\nThe First Input:\n\n"

cat input1.txt

printf "$sep\nThe Second Input:\n\n"

cat input2.txt

printf "$sep\nOutput:\n\n"

cat output.txt
