#!/bin.sh -e

Sep="\n=================================\n"

printf "\nTable of words and descriptions with hash-search\n"

clang-3.5 -o hashtab 005.c
./hashtab -u the <input.txt >output.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput:\n\n"

cat output.txt
