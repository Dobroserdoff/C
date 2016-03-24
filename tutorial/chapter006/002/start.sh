#!/bin.sh -e

sep="\n=================================\n"

printf "\nWord counter by the first N-characters\n"

clang-3.5 -o counter 002.c
./counter -4 <input.txt >output1.txt
./counter -4 -d <input.txt >output2.txt
./counter -4 -r <input.txt >output3.txt

printf "$sep\nInput:\n\n"

cat input.txt

printf "$sep\nOutput for alphabetical order:\n\n"

cat output1.txt

printf "$sep\nOutput for direct numeric order:\n\n"

cat output2.txt

printf "$sep\nOutput for reverse numeric order:\n\n"

cat output3.txt

