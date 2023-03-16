#!/bin/bash

./build/simulator Example_test_cases/fib/fib.asm Example_test_cases/fib/fib.txt 0 Example_test_cases/fib/fib_checkpts.txt Example_test_cases/fib/fib.in fib.out

a=0
cmp register_$a.bin Example_test_cases/fib/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/fib/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/fib/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/fib/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


a=3
cmp register_$a.bin Example_test_cases/fib/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/fib/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/fib/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/fib/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


a=7
cmp register_$a.bin Example_test_cases/fib/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/fib/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/fib/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/fib/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


cmp fib.out Example_test_cases/fib/fib_correct.out
if [ $? -eq 1 ]
then
    echo "Oooops! fib failed"
else
    echo "Output of fib is correct!"
fi