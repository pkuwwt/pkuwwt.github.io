---
title: Linux下将多个图像转换为pdf
layout: blog
comments: true
---

基本上有两种方案，一种是用convert，一种是用gs
{% highlight bash %}
convert *.jpg output.pdf
gs -sDEVICE=pdfwrite -o $out /usr/share/ghostscript/*/lib/viewjpeg.ps -c "(1.jpg) viewJPEG showpage (2.jpg) viewJPEG showpage"
{% endhighlight %}

但是convert有时候得到的pdf居然打不开，因此，只能使用gs了。下面是写的一个脚本。首先用ImageMagick的convert工具转换成jpeg，因为gs不能处理所有类型的图片。然后，用gs命令生成pdf。
{% highlight bash %}
#!/bin/bash
## 
## USAGE: 
##    ./images2pdf.sh a.jpg b.jpg output.pdf
##    ./images2pdf.sh a.jpg b.jpg 
##

if (( $# < 1 ));then
	echo "USAGE: $0 a.jpg [b.jpg ...] [output.pdf]"
	exit
fi

if ! `which gs >/dev/null`;then
	echo "No ghostscript installed"
	exit 
fi
if ! `which convert >/dev/null`;then
	echo "No ImageMagick installed"
	exit 
fi

command=""
while (( $# > 1 ));do
	tmp=__tmp-$1.jpg
	convert $1 $tmp
	command="${command} ($tmp) viewJPEG showpage "
	shift
done
out=$1
if [[ "-${out##*.}" != "-pdf" ]];then
	tmp=__tmp-$1.jpg
	convert $1 $tmp
	command="${command} ($tmp) viewJPEG showpage "
	out=output.pdf
fi

gs -sDEVICE=pdfwrite -o $out /usr/share/ghostscript/*/lib/viewjpeg.ps -c "$command"

rm __tmp-*.jpg
{% endhighlight %}

