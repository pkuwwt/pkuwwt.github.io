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

置换格式时设置图像分辨率，并指定(偏好)输出图像大小。输出为jpg时此法不适用。
{% highlight bash %}
convert -density 800x800 -resize 250x250 input.pdf out.png
{% highlight %}

