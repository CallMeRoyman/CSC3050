#!/bin/bash

# DIR="."

# if [ -d "$DIR" ]
# then
#     rm "$DIR"/*.bin
# fi

FILES="./*.bin"
for file in $FILES
do
    if [ -f "$file" ]
    then
        rm "$file"
    fi
done

FILES="./correct_*"
for file in $FILES
do
    if [ -f "$file" ]
    then
        rm "$file"
    fi
done

FILES="./memory_*"
for file in $FILES
do
    if [ -f "$file" ]
    then
        rm "$file"
    fi
done

FILES="./register_*"
for file in $FILES
do
    if [ -f "$file" ]
    then
        rm "$file"
    fi
done

FILES="./*.out"
for file in $FILES
do
    if [ -f "$file" ]
    then
        rm "$file"
    fi
done

DIR="./build"
if [ -d "$DIR" ]
then
    rm -r build
fi

FILE="/tmp/file.txt"
if [ -f "$FILE" ]
then
    rm "$FILE"
fi