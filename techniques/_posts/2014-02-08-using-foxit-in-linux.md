---
layout: blog
comments: true
tags: linux pdf foxit
title: 在Linux下使用wine+foxit
---

foxit是一个免费的pdf阅读/编辑软件，支持常用的标注功能，但只有一个阉割的Linux版。

然而借助于wine，我们也可以在Linux下使用Winodws版的foxit。

官方的foxit安装程序会生成一个路径和文件名有空格的版本，而且存储时会出现问题，不如使用[免安装版](http://portableapps.com/apps/office/foxit_reader_portable)。

下载`FoxitReaderPortable_6.1.2.paf.exe`之后，用wine运行，安装(解压)至`~/Programs/FoxitReaderPortable/`。

然后在编辑/usr/bin/foxit文件:

{% highlight bash %}
export WINEDEBUG=-all
wine ~/Programs/FoxitReaderPortable/FoxitReaderPortable.exe "`winepath -w "$@"`"
{% endhighlight %}

注意，上面命令中的两对引号，它们的作用是将Linux下的路径转换为Windows中的路径，并支持带空格的文件名。类似的，其它Windows程序的wine版本存在的带空格文件名不能打开的问题，也可以用这种方式解决。

现在，就可以用foxit命令来在命令行中打开pdf文件了。比如

{% highlight bash %}
foxit ./file\ with\ space1.pdf
foxit "./file with space2.pdf"
{% endhighlight %}

