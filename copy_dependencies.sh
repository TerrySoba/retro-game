#!/bin/bash

# check if enough parameters have ben given
if [ $# -ne 3 ]
then
	echo "Usage: $0 <shared object> <output directory> <source dir>"
	exit 1
fi

inputfile=$1
outputdir=$2
sourcedir=$3

#check if inputfile exists
if [ ! -f "$inputfile" ]; then
	echo "File \"$inputfile\" not found."
	exit 1
fi

#check if outputdir exists
if [ ! -d "$outputdir" ]; then
	echo "Directory \"$outputdir\" not found."
	exit 1
fi

#check if sourcedir exists
if [ ! -d "$sourcedir" ]; then
	echo "Directory \"$sourcedir\" not found."
	exit 1
fi


depfiles=$(ldd "$inputfile" | grep "$sourcedir" | awk '{print $3}')

for file in $depfiles
do
	echo "Copying file \"$file\" to \"$outputdir/$(basename $file)\"" 
	cp "$file" "$outputdir"
done
