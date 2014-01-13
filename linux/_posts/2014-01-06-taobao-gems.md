---
layout: blog
title: 使用淘宝提供的Ruby源
---

国外的Ruby源经常受到干扰，速度慢，所幸，国内有[淘宝](http://ruby.taobao.org/)做了镜像，每5分钟更新一次。

替换源的方法在[镜像主页](http://ruby.taobao.org/)上已经有了，这里只是备份一下。

{% highlight bash %}
gem sources --remove https://rubygems.org/
gem sources -a http://ruby.taobao.org/
gem sources -l
{% endhighlight %}

