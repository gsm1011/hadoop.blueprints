#!/bin/bash 

# Bash function to split into lines of text into individual words
while read line; do 
  for word in $line; do
    word=`echo $word | tr ‘[A-Z]’ ‘[a-a]’`
    word=`echo $word | tr -d ‘[:punct:]’`
    echo $word 
  done
done
