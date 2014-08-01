---
layout: blog
comments: true
title: wxMaxima连不上maxima
---

本来用得好好的，wxMaxima突然有一天连不上maxima了，提示`not connected to maxima`。google了一下，好像确保`/etc/hosts`中有下面两行这就行了。

{% highlight bash %}
127.0.0.1 localhost
127.0.0.1 localhost.localdomain localhost
{% endhighlight %}

