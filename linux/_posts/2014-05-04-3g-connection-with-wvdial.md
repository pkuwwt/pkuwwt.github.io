---
layout: blog
comments: true
title: Linux下用wvdial为3G上网卡拨号
---

虽然，主流的3G网卡都有Linux下的驱动，但是那些界面往往并不友好，更何况不是所有的3G网卡都有Linux驱动。

不管有没有驱动，一般都是可以搞定的。因为不同专家的芯片其实都大同小异，山寨3G网卡用的也都是大厂家的货，而Linux内核驱动中已经集成了那些常见的驱动。

3G网卡本质上是一种具有两种模式的USB设备，一种模式下它可视为存储设备(装了Windows下的驱动软件)，另一种模式则是USB接口的Modem。如果Linux内核中已经包含了相应的驱动，使用`lsusb`命令就应该看到Modem字样。另外，`ls /dev/ttyUSB*`也会看到一些相应的设备文件。

如果`/dev/ttyUSB*`之类的设备文件不存在，说明3G网卡的模式不对，需要用`usb_modeswitch`命令处理。

网上有人介绍了一些用NetworkManager之类的图形界面工具，但经过实验，发现还是`wvdial`这个纯情命令行工具好用。

只需要三步。第一步是生成配置文件，第二步修改DNS，第三步执行`wvdial`。

配置文件需要在root权限下执行命令`wvdialconf`，它会生成配置文件`/etc/wvdial.conf`文件。你需要改这个文件内容。默认情况下，`Phone`，`Username`，`Password`为空，你需要补上，且`Password`不能为空，可随便选一个字符串。下面是联通3G的配置文件。其中的`Auto Reconnect`和`Auto DNS`也是额外加的选项，分别表示自动重连和自动处理DNS。

{% highlight kconfig %}
[Dialer Defaults]
Init2 = ATQ0 V1 E1 S0=0 &C1 &D2 +FCLASS=0
Modem Type = Analog Modem
Phone = *99#
ISDN = 0
Username = uninet
Init1 = ATZ
Password = password
Modem = /dev/ttyUSB0
Baud = 9600
Auto Reconnect = on
Auto DNS = on
{% endhighlight %}

生成配置文件之后，就可以执行`wvdial`了，但是此时仍然不能上网，因为还需要设置DNS。也就是修改`/etc/resolv.conf`文件内容。

{% highlight kconfig %}
nameserver 202.106.195.68
nameserver 202.106.46.151
{% endhighlight %}

最后，就是执行`wvdial`了。

