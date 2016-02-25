#!/bin.sh -e

sep="\n=================================\n"

printf "\nC declaration into a word description and back converter\n"

clang-3.5 -o converter 018.c
./converter <input1.txt >output1.txt
./converter -u <input2.txt >output2.txt

printf "$sep\nDeclaration into a word description input:\n\n"

cat input1.txt

printf "$sep\nShorthand conversion input:\n\n"

cat input2.txt

printf "$sep\nOutput:\n\n"

cat output1.txt
printf "\n"
cat output2.txt
