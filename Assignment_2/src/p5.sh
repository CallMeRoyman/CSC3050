#!/bin/bash

./build/simulator Example_test_cases/memcpy-hello-world/memcpy-hello-world.asm Example_test_cases/memcpy-hello-world/memcpy-hello-world.txt 0 Example_test_cases/memcpy-hello-world/memcpy-hello-world_checkpts.txt Example_test_cases/memcpy-hello-world/memcpy-hello-world.in memcpy-hello-world.out
a=12
cmp register_$a.bin Example_test_cases/memcpy-hello-world/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/memcpy-hello-world/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/memcpy-hello-world/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/memcpy-hello-world/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


a=13
cmp register_$a.bin Example_test_cases/memcpy-hello-world/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/memcpy-hello-world/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/memcpy-hello-world/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/memcpy-hello-world/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


a=21
cmp register_$a.bin Example_test_cases/memcpy-hello-world/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/memcpy-hello-world/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/memcpy-hello-world/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/memcpy-hello-world/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


a=55
cmp register_$a.bin Example_test_cases/memcpy-hello-world/correct_dump/register_$a.bin
if [ $? -eq 1 ]
then
    hexdump register_$a.bin > register_$a.txt
    hexdump Example_test_cases/memcpy-hello-world/correct_dump/register_$a.bin > correct_register_$a.txt
fi
cmp memory_$a.bin Example_test_cases/memcpy-hello-world/correct_dump/memory_$a.bin
if [ $? -eq 1 ]
then
    hexdump memory_$a.bin > memory_$a.txt
    hexdump Example_test_cases/memcpy-hello-world/correct_dump/memory_$a.bin > correct_memory_$a.txt
fi


cmp memcpy-hello-world.out Example_test_cases/memcpy-hello-world/memcpy-hello-world_correct.out
if [ $? -eq 1 ]
then
    echo "Oooops! memcpy-hello-world failed"
else
    echo "Output of memcpy-hello-world is correct!"
fi