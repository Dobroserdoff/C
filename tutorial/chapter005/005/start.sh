#!/bin/sh -e

sep="\n=================================\n"

printf "\nString stack operator:\n"

gcc -o stroper main.c getop.c functions.c
./stroper <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
