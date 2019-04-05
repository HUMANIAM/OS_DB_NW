#!/bin/sh

# looping in shell programming ex1
for i in 1 2
do 
echo "I am ", $i
done


# listing files in the current dir
for file in files_are *
do
echo $file
done
