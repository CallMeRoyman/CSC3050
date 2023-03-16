#!/bin/bash

./build/simulator Example_test_cases/many/many.asm Example_test_cases/many/many.txt test Example_test_cases/many/many_checkpts.txt Example_test_cases/many/many.in many.out

a=0
cmp register_$a.bin Example_test_cases/many/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/many/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/many/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/many/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


a=23
cmp register_$a.bin Example_test_cases/many/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/many/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/many/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/many/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


a=97
cmp register_$a.bin Example_test_cases/many/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/many/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/many/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/many/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


cmp many.out Example_test_cases/many/many_correct.out
if [ $? -eq 1 ]
then
    echo "Oooops! many failed"
else
    echo "Output of many is correct!"
fi