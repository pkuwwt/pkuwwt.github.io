---
layout: blog
title: 关于几种窗口系统的透明效果
---

# 关于几种窗口系统的透明效果

最早接触窗口的透明效果是linux下的gnome-terminal，当时就觉得非常好用，结合vim可谓敲字神器。特别是翻译的时候，不需要来回切换，或者各占一边屏幕。gnome-terminal的透明效果设置当然是很简单的，修改其profile即可。

下面分别介绍linux和windows下的透明效果设置。

## X窗口下的透明效果设置
X窗口下同样没有现成的工具，但可以借助于Xcompmgr和[transset-df](http://forchheimer.se/transset-df/transset-df-6.tar.gz)。[transset-df备份](../img/transset-df-6.tar.gz)

transset-df在一些源中没有，因此需要自己编译(源码简单，make即可)。

在运行Xcompmgr之后，就可以用transset-df来设置窗口透明度了。比如`trannset-df -a`命令就可以将当前窗口变透明。

但是，transset-df是一个命令行工具，如何与窗口系统结合起来呢。下面介绍两种使用方式

### openbox下的使用
先保证在`~/.config/openbox/autostart.sh`中已经启动了xcompmgr。比如

{% highlight bash %}
( xcompmgr -Ss -n -Cc -fF -I-10 -O-10 -D1 -t-3 -l-4 -r4 ) &
{% endhighlight %}

修改`~/.config/openbox/rc.xml`中的`<context name=”Titlebar”>`项下面的鼠标绑定内容。
{% highlight xml %}
<context name=”Titlebar”>
    <!-- 使用transset-df设置窗口透明效果 -->
    <mousebind button="C-Middle" action="Click">
        <action name="Execute">
            <execute>transset-df -p</execute>
        </action>
    </mousebind>
    <mousebind button="C-Up" action="Click">
        <action name="Execute">
            <execute>transset-df -p --inc 0.2 </execute>
        </action>
    </mousebind>
    <mousebind button="C-Down" action="Click">
        <action name="Execute">
            <execute>transset-df -p -m 0.2 --dec 0.2</execute>
        </action>
    </mousebind>
{% endhighlight %}

这样，你就可以在窗口标题栏上按`Ctrl+中键`切换透明度了，`Ctrl+向上滚动`增加透明度，`Ctrl+向下滚动`减少透明度。

### 结合devilspie的使用
devilspie支持自动绑定某类窗口，即窗口启动时会触发后台devilspie程序的相应行为。devilspie的配置文件在`~/.devilspie/`目录中，比如随便建立一个文件opacity.ds。内容为

{% highlight lisp %}
( if
  ( or
    ( contains ( window_class ) "Gvim" )
    ( contains ( application_name ) "mirage" )
    ( contains ( application_name ) "chrome" )
  )
  ( begin
    ( spawn_async (str "transset-df -t -i " (window_xid) " 0.85" ))
  )
  )
{% endhighlight %}

应该比较好理解，当启动Gvim，mirage或chrome时设置其透明度为0.85。如果确定特定应用的窗口类别或其它属性呢。执行`devilspie -a`，然后启动某个应用，它的属性就会在devilspie的输出中显示出来。或者使用`xprop`也可以确定某个窗口的属性。注意，`transset-df`应该放在系统路径中，或者使用绝对路径。

然后，在X启动配置文件`~/.xinitrc`中加入
{% highlight lisp %}
xcompmgr &
devilspie -a &
{% endhighlight %}

注意，xcompmgr和devilspie的启动不一定要放在.xinitrc中，只要在X启动之前执行即可，比如在openbox环境中，加入autostart.sh也是可以的。

## Windows下窗口透明效果设置
Windows系统没有提供工具修改窗口透明度，但第三方工具可以，它们是AutoIt和AutoHotKey。以AutoIt为例，代码是

{% highlight bash %}
WinSetTrans("[CLASS:Vim]", "", 170);
{% endhighlight %}

AutoIt3提供了工具Au3Info，可以查看窗口以及子窗口的详细信息。上面的代码可以将所有打开的Gvim窗口设置为半透明。透明度值介于0-255之间。

## cygwin终端透明效果

cygwin终端也提供半透明效果，只需要设置其选项即可(点击左上角图标->options->Looks->Transparency)。

## 参考文献

  - [Per Application Transparency](https://wiki.archlinux.org/index.php/Per_Application_Transparency)
  - [transset-df在openbox中实现透明效果](http://hi.baidu.com/dooda/item/8fce369417f5a435336eeb27)

