#!/bin/bash

./build/simulator Example_test_cases/lw_sw/lw_sw.asm Example_test_cases/lw_sw/lw_sw.txt 0 Example_test_cases/lw_sw/lw_sw_checkpts.txt Example_test_cases/lw_sw/lw_sw.in lw_sw.out

a=4
cmp register_$a.bin Example_test_cases/lw_sw/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/lw_sw/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/lw_sw/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/lw_sw/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


a=5
cmp register_$a.bin Example_test_cases/lw_sw/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/lw_sw/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/lw_sw/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/lw_sw/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


cmp lw_sw.out Example_test_cases/lw_sw/lw_sw_correct.out
if [ $? -eq 1 ]
then
    echo "Oooops! lw_sw failed"
else
    echo "Output of lw_sw is correct!"
fi