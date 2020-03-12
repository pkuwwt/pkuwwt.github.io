---
layout: blog
comments: true
title: 修复pdf没有嵌入字体的问题
---

一些非标准的pdf文件，特别是在windows下生成的一些pdf文件，往往没有嵌入全部的字体，导致这样的pdf文件在其它系统下不能正确渲染。使用`pdffonts`命令(来自于poppler-utils)，可以查看哪些字体没有嵌入进去。

解决办法是用gs修复一下。

{% highlight bash %}
#!/bin/bash
# repair font-not-embbed problem

if (( $# < 1 ));then
	echo "USAGE: $0 input.pdf [out.pdf]"
	exit
fi

INPUT=$1
OUTPUT=/tmp/repair-pdf.pdf

gs -o "$OUTPUT" -dPDFSETTINGS=/prepress -sDEVICE=pdfwrite "$INPUT"

if (( $# < 2 ));then
	mv "$OUTPUT" "$INPUT"
else
	mv "$OUTPUT" "$2"
fi
{% endhighlight %}

## 参考文献

  * [The pdf viewer evince on Linux can not display some math symbols correctly](http://stackoverflow.com/questions/10277418/the-pdf-viewer-evince-on-linux-can-not-display-some-math-symbols-correctly)

