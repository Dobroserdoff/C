#!/bin.sh -e

Sep="\n=================================\n"

printf "\nFiles comparison\n"

clang-3.5 -o compare 006.c
./compare original.txt same.txt different.txt >output.txt

printf "$sep\nOriginal file:\n\n"

cat original.txt

printf "$sep\nThe first file to compare:\n\n"

cat same.txt

printf "$sep\nThe second file to compare:\\n\n"

cat different.txt

printf "$sep\nOutput:\n\n"

cat output.txt
