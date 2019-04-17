#!/bin/sh

INPUT_STRING=hello
while [ "$INPUT_STRING" != "bye" ]
do
  echo "Please type something in (bye to quit)"
  read INPUT_STRING
  echo "You typed: $INPUT_STRING"
done

# read the content of this file
while read f
do 
	case $f in
		Ar) echo "Arabic" ;;
		Eng) echo "English" ;;
		*) echo "I don't know this language : $f";;
	esac
		
done < while.sh
