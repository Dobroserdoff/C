#!/bin.sh -e

Sep="\n=================================\n"

printf "\nList of all words and numbers of lines where it appears\n"

clang-3.5 -o format 002.c
./format -o <input.txt >outputo.txt
./format -h <input.txt >outputx.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOctal output:\n\n"

cat outputo.txt

printf "$sep\nHexadecimal output:\n\n"

cat outputx.txt
