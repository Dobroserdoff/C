#!/bin/sh -e

sep="\n=================================\n"

printf "\nChar to int:\n"

gcc -o getint 001.c
./getint <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
