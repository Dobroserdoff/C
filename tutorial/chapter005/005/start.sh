#!/bin/sh -e

sep="\n=================================\n"

printf "\nText processor:\n"

gcc -o stroper str.h main.c getop.c functions.c stack.c
./stroper <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
