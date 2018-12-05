#!/bin/bash

gcc tempread.c -o tempread
init_output=$(./tempread)
echo $init_output

while true;
do
    output=$(./tempread)
    diff=$(($output - $init_output))
    diff=$(($diff / 1000))
    if [ $diff -ge 1 ] && [ $diff -lt 2 ]; then
        gpio mode 0 output
        gpio write 0 1
    
    elif [ $diff -ge 2 ] && [ $diff -lt 3 ]; then
        gpio mode 0 output
        gpio mode 1 output 
        gpio write 0 1
        gpio write 1 1
    elif [ $diff -ge 3 ]; then
        gpio mode 0 output
        gpio mode 1 output
        gpio mode 2 output 
        gpio write 0 1
        gpio write 1 1
        gpio write 2 1
    fi
done

