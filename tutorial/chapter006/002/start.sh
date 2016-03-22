#!/bin.sh -e

sep="\n=================================\n"

printf "\nWord counter by the first N-characters\n"

clang-3.5 -o counter 002.c
./counter -4 <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
