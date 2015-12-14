#!/bin/sh -e

sep="\n=================================\n"

printf "\nChar to double:\n"

gcc -o getdouble 002.c
./getdouble <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
