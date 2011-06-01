#!/bin/bash
declare -A data
if [[ !(-r $1 && -r $2)  ]]; then 
	echo "Files are not readable" ;
	exit
fi

while read item size; do
	 if [ "$item" != "" ]; then
		if [ "$size" != "" ]; then
			md5="$item:$size"
		else
			data["$item"]="$md5"
		fi;
	fi;
done <"./$1"
while read hash size item; do
	md5="$item:$size"
	if [[ $md5 != "${data[$item]}" ]]; then
		echo "File $item has changed from ${data[$item]} to $md5."
	fi;
done <"./$2"
