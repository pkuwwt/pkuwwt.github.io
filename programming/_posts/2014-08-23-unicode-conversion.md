---
layout: blog
comments: true
tags: programming Unicode
title: 中文转码工具
---

## native2ascii
native2ascii是Java自带的一个工具，可以在中文和Unicode码的ASCII表示之间进行相互置换，对于文本编码时的编程很重要。

Uniocde转中文字符
{% highlight bash %}
echo "\u6e38\u620f\u73a9\u5bb6" >origin.txt
native2ascii -reverse -encoding GB2312 origin.txt cn.txt
{% endhighlight %}
上述命令将`origin.txt`中的Unicode记号转为中文文本文件`cn.txt`，其编码是`GB23112`，当然选择其它文本编码也是可以的，比如`UTF8`。

中文字符转Unicode字符
{% highlight bash %}
native2ascii -encoding Uniocde cn.txt unicode.txt
{% endhighlight %}

你很有可能发现，上述过程中，`origin.txt`和`unicode.txt`的内容是不一样的。这是因为我们人为指定了编码。如果都不要`-encoding`属性，则`native2ascii`与`native2ascii -reverse`是完全互逆的。


## 网址中的中文解码
假设网址为`http://index.baidu.com/Industry/?word=%CD%F2%BF%C6`。这里面的`%CD%F2%BF%C6`是GBK编码。因此，解码很简单

{% highlight bash %}
echo -e `echo %CD%F2%BF%C6 | sed 's,%,\\\\x,g'` | iconv -f gbk -
{% endhighlight %}
结果是
{% highlight bash %}
万科
{% endhighlight %}

