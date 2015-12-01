#!/bin/sh -e

delim="\n========================================\n"

printf "Compiling:\n\n"

cc -o calc calc.c
./calc <input.txt >output.txt

printf "$delim\nInput was:\n\n"

cat input.txt

printf "$delim\nOutput was:\n\n"

cat output.txt
