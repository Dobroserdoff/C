#!/bin.sh -e

Sep="\n=================================\n"

printf "\nTable of words and descriptions of real code with hash-search\n"

gcc -o scanner 004.c
./scanner <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
