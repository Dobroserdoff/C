#!/bin.sh -e

sep="\n=================================\n"

printf "\nConverter to all upper/lower characters\n"

clang-3.5 -o converter 001.c
clang-3.5 -o CONVERTER 001.c
./converter <input.txt >outputl.txt
./CONVERTER <input.txt >outputu.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nAll lower characters output:\n\n"

cat outputl.txt

printf "$sep\nAll upper characters output:\n\n"

cat outputu.txt

