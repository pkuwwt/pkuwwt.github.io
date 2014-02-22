---
layout: blog
comments: true
title: 一个用于寻找文件，并便于打开文件的脚本
---

在Linux命令行下，通常需要根据文件名去找一个文件，然后再将文件名拷出来，小心加上引号(文件名中可能包含空格)，然后，再在行首加上打开命令。这个过程甚是麻烦。

当然，你可以使用管道。但是如果有多个文件，而你只想打开其中一个呢?

下面是我的[脚本](../img/find_file.sh)，相当于是`find`的增强，在交互上应该让人舒服不少。

[脚本](../img/find_file.sh)中，使用了`-type f`和`-iname`选项，即只寻找规则文件，并不考虑大小写。另外，擅自在模式前后加上了通配符`*`，`find`总是强迫用户写出完整的模式，有时候有点多余。

{% highlight bash linenos %}
#!/bin/bash

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
{% endhighlight %}

同样，这里有几个需要备忘的bash脚本技巧:

  - 当比较数字之前，需要检测此数字是否是空字符串，否则会是错误的表达式
  - 比较字符串时，需要在前面或后面加上其它符号，同样是为了防止空字符串导致错误表达式
  - 获取文件的第2行，暂时使用`head -2 | tail -1`，不知还有没有更方便方法
  - 获取文件后缀: `${param##*.}`
  - 将字符串大写变小写: `${param,,*}`

