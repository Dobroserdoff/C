#!/bin/sh -e

sep="\n=================================\n"

printf "\nDate converter:\n"

gcc -o date 008.c
./date <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
