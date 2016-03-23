#!/bin.sh -e

Sep="\n=================================\n"

printf "\nList of all words and numbers of lines where it appears\n"

clang-3.5 -o list 003.c
./list <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
