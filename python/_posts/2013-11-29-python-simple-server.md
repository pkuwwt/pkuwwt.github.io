---
vim: wrap expandtab ft=markdown
layout: blog
comments: true
title: 最简单的python服务器
---

## 只需要一条命令

{% highlight python %}
$ python -m SimpleHTTPServer 4444
{% endhighlight %}

这里的4444是你选定的端口，默认是8000。SimpleHTTPServer是python的一个包。

## 如果想在python脚本里执行呢?

{% highlight python %}
import SimpleHTTPServer
SimpleHTTPServer.test()
{% endhighlight %}


