#!/bin/sh -e

sep="\n=================================\n"

printf "\nReverse strings:\n"

gcc -o reverse 013.c
./reverse <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
