#!/usr/bin/env bash

path=$1

# check if no arguments were provided
if [ "$path" == "" ]
then
	# if no arguments provided, then call find in current directory
	# find all files in the current directory
	# pipe into word count and count the number of lines that appear
	# store line count in num_regular
	num_regular=$(find . -type f | wc -l)

	# same process as line above, except now with finding number of directories instead of files
	num_dir=$(find . -type d | wc -l)
else
	# if argument was provided, cd into that directory
	cd "$path" || exit

	# same process as listed above
	num_regular=$(find . -type f | wc -l)
        num_dir=$(find . -type d | wc -l)
fi

# print number of directories and number of regular files
echo "There were" "$num_dir" "directories."
echo "There were" "$num_regular" "regular files."


