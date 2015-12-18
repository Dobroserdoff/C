#!/bin/sh -e

sep="\n=================================\n"

printf "\nString concatenation:\n"

gcc -o strconcat 003.c
./strconcat <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
