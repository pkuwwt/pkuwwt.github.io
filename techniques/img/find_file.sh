#!/bin/bash
##
## A script to find file with similar syntax to `find`
## The user can choose a file in the resulting list
## and open it by pre-defined application
##
## By Wang Wentao
##    wwthunan@gmail.com
##    pkuwwt.github.com
##    2014-02-22
##

if (( $# < 2 )); then
	echo "USAGE: $0 path pattern [find-flags]"
	echo "Example: $0 . "'my*pattern -cmin 1'
	echo "       Press Ctrl-C to break"
	exit
fi

open_file(){
	_type=${@##*.}
	_type=${_type,,*}
	cmd=xdg-open
	if [[ $_type == "md" ]];then cmd=vim
	elif [[ $_type == "pdf" ]]; then cmd=evince
	elif [[ $_type == "jpg" ]]; then cmd=feh
	elif [[ $_type == "txt" ]]; then cmd=vim
	fi
	$cmd "$@"
}


TMP=/tmp/__tmp_`basename $0`.txt
path=$1
pattern=$2
shift 2

find $path  $@ -type f -iname "*$pattern*" >$TMP
NUM=`cat $TMP | wc -l`
cat -n $TMP
echo $pattern

if [[ "-$NUM" == "-" ]];then
	echo "Error"
	exit
fi
if (( $NUM == 0 )); then 
	echo "No file found"
	exit
fi

while true;do
	read -p "Select(1-$NUM): " ID

	if [[ "-$ID" == "-" ]];then
		continue
	fi
	if ! (( $ID >= 1 && $ID <= $NUM )); then
		echo "Wrong Index"
		continue
	fi

	FILE=`cat $TMP | head -$ID | tail -1`

	open_file "$FILE"
done

