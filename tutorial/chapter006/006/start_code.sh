#!/bin.sh -e

Sep="\n=================================\n"

printf "\nTable of words and descriptions of real code with hash-search\n"

clang-3.5 -o hashtab_code 006.c
./hashtab_code <input_code.c >output_code.c

printf "$sep\nInput:\n\n"

cat input_code.c

printf "$sep\nOutput:\n\n"

cat output_code.c
