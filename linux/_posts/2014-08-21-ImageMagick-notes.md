---
layout: blog
comments: true
title: ImageMagick使用笔记
---


将png图片变透明(即将白色部分全变成透明的)
{% highlight bash %}
convert orgin.png -transparent white trans.png
{% endhighlight %}

替换图像中的颜色，比如将所有的黑色换成黄色
{% highlight bash %}
convert input.png -fill yellow -opaque black output.png
{% endhighlight %}

置换格式时设置图像分辨率
{% highlight bash %}
convert -density 500x500 input.pdf out.png
{% highlight %}
