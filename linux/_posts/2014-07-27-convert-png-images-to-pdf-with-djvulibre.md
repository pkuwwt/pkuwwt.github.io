---
layout: blog
comments: true
title: 用djvulibre将png图片转化为pdf
---

假设有1.png,...,25.png这些按顺序编号的图片文件，下面是转换过程

{% highlight bash %}
for x in {1..25}.png; do convert $x $x.jpg; c44 -dpi 300 $x.jpg; done
djvm -c ../result.djvu {1..25}.png.jpg.djvu
ddjvu -format=pdf ../result.djvu ../result.pdf
{% endhighlight %}

其中`convert`工具来自于ImageMagick。
