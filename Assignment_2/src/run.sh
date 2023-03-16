#!/bin/bash

cmake -B build
cmake --build build

for i in {1..5}
do
    ./p$i.sh
done