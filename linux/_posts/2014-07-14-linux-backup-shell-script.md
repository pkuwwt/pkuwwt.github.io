---
layout: blog
comments: true
title: 备份文件Shell脚本
---

{% highlight bash %}
#!/bin/bash
# compression_targz bzip2|xz|lzip|lzma|lzop|gzip output inputs... 
function compression_tar(){
	local METHOD=$1
	local OUT=$2
	shift
	shift
	local IN=$@
	local POSTFIX=""
	case $METHOD in
		bzip2 ) POSTFIX="tar.bz2";;
		xz ) POSTFIX="tar.xz";;
		lzip ) POSTFIX="tar.lz";;
		lzma ) POSTFIX="tar.lzma";;
		lzop ) POSTFIX="tar.lzo";;
		gzip ) POSTFIX="tar.gz";;
		* ) return;;
	esac
	POSTFIX="`date +%Y%m%d-%H%M%S`.$POSTFIX"
	tar -c --$METHOD -vf "$OUT-$POSTFIX" $IN
}
# compression_7z output inputs... 
function compression_7z(){
	local OUT=$1
	shift
	local IN=$@
	local POSTFIX="`date +%Y%m%d-%H%M%S`.7z"
	7z a $OUT-$POSTFIX $IN
}
# compression_zip output inputs...
function compression_zip(){
	local OUT=$1
	shift
	local IN=$@
	local POSTFIX="`date +%Y%m%d-%H%M%S`.zip"
	zip $OUT-$POSTFIX $IN
}
# common interface
# compression output inputs...
function compression(){
	local OUTPUT=$1
	shift
	compression_tar gzip $OUTPUT $@
}
############################################################
## not as a main program
if [[ $0 == "bash" ]];then
	return
fi
if (( $# == 0 )); then
	echo "USAGE: $0 [-o output] file1 file2 file3 ..."
	exit
fi
if [[ $1 == "-o" ]]; then
	if (( $# < 3 )); then
		echo "USAGE: $0 [-o output] file1 file2 file3 ..."
		exit
	fi
	shift
	OUTPUT=$1
	shift
else
	OUTPUT=`echo $1 | sed 's/\/$//g'`
fi
# trip tailing slash
OUTPUT=`echo $OUTPUT|sed 's/\/*$//g'`
compression $OUTPUT $*
{% endhighlight %}

