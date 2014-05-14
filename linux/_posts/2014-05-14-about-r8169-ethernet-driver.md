---
layout: blog
comments: true
title: 关于Linux下有线网卡不能连接的问题
---

我的Fedora19之前用得好好的，不知从什么时候开始，有线网偶尔会连不上，既开机前网口灯是亮的，一旦启动进入系统，灯立刻会灭，而NetworManager则显示断线。但是，偶尔它又会连上。于是一开始给人造成设备有问题的假象。实际上是r8169驱动的问题。

可以看一下`dmesg | grep -i net`和`cat /var/log/message`中相关内容，里面会告诉你关于r8169的加载信息，以及"link down"之类的提示。

为装官方最新驱动，需要查看一下网卡类型

{% highlight bash %}
lspci | grep -i ethernet
{% endhighlight %}

不过，好像realtek的以太网驱动[下载页面](http://www.realtek.com.tw/downloads/downloadsView.aspx?Langid=1&PNid=13&PFid=5&Level=5&Conn=4&DownTypeID=3&GetDown=false)中，并不怎么区分网卡类型，这一类网卡都是用同一个驱动。

下载得到[r8168-8.038.00.tar.bz2](../img/r8168-8.038.00.tar.bz2)。解压缩，在root下执行autorun.sh即可，它将r8169.ko备份为r8168.bak，用r8168.ko取而代之。尝试用README中的方法，应该就可以恢复网络了。`lsmod | grep r816`可以发现驱动确实被替换了。

为防止系统重启后重新加载r8169，可以在`/etc/modprobe.d/blacklist.conf`中添加

{% highlight kconfig %}
blacklist r8169
{% endhighlight %}

