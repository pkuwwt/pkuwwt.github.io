---
layout: blog
comments: true
title: bit操作
---

用`unsigned char`或`unsigned int`作为bool数组是常用的编程手法。对于第$n$位上的bit位，有如下几种操作。

### 设置bit为1 ###
{% highlight cpp %}
    number |= 1<<n;
{% endhighlight %}

### 清除bit为0 ###

{% highlight cpp %}
    number &= ~(1<<n);
{% endhighlight %}

### 切换bit ###

{% highlight cpp %}
    number ^= 1<<n;
{% endhighlight %}

### bit位取值 ###

{% highlight cpp %}
    bit = number & (1<<n);
{% endhighlight %}
  

参考: [How do you set, clear and toggle a single bit in C/C++?](http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c)
