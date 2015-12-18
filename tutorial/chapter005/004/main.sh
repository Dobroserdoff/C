#!/bin.sh -e

sep="\n=================================\n"

printf "\nString ending comparison:\n"

gcc -o strtail 004.c
./strtail <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
