---
layout: blog
comments: true
title: 在Linux下为笔记本添加两指左右滚动功能
---

默认下，synaptics触摸板是允许双指上下滚动的，但是左右不行。可以执行

{% highlight bash %}
synclient -l
{% endhighlight %}

查询目前的所有选项的参数。其中可以找到`HorizTwoFingerScroll`选项，默认是关闭的。可以手动打开

{% highlight bash %}
synclient HorizTwoFingerScroll=1
{% endhighlight %}

但是重启之后就会回到默认状态，怎么办呢？编写配置文件`/etc/X11/xorg.conf.d/50-synaptics.conf`。内容是

{% highlight bash %}
Section "InputClass"
	Identifier "touchpad"
	Driver "synaptics"
	MatchIsTouchpad "on"
	Option "HorizTwoFingerScroll" "on"
EndSection
{% endhighlight %}

## 参考文献

  * [archlinux wiki](https://wiki.archlinux.org/index.php/Touchpad_Synaptics)

