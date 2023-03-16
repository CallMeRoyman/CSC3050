#!/bin/bash

./build/simulator Example_test_cases/a-plus-b/a-plus-b.asm Example_test_cases/a-plus-b/a-plus-b.txt 0 Example_test_cases/a-plus-b/a-plus-b_checkpts.txt Example_test_cases/a-plus-b/a-plus-b.in a-plus-b.out

a=0
cmp register_$a.bin Example_test_cases/a-plus-b/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/a-plus-b/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/a-plus-b/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/a-plus-b/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


cmp a-plus-b.out Example_test_cases/a-plus-b/a-plus-b_correct.out
if [ $? -eq 1 ]
then
    echo "Oooops! a-plus-b failed"
else
    echo "Output of a-plus-b is correct!"
fi
   