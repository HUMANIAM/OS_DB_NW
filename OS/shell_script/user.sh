#!/bin/sh

#interact with user
echo "What is your name?"
read UserName
echo "I will create file with name ${UserName}_file"
touch "${UserName}_file"

