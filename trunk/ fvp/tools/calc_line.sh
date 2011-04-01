#!/bin/bash

echo "calc the lines of all *.cpp files"
find . -name "*.cpp" |xargs cat|wc -l
echo "calc the lines of all *.c files"
find . -name "*.c" |xargs cat|wc -l
echo "calc the lines of all *.h files"
find . -name "*.h" | xargs cat|wc -l
