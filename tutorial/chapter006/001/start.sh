#!/bin.sh -e

sep="\n=================================\n"

printf "\nKeyword counter\n"

clang-3.5 -o counter 001.c
./counter <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
