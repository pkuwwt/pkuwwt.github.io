---
layout: blog
title: GNU screen 保存会话
---

GNU Screen支持在一个终端内(但超越了终端)保存了多个shell状态，非常实用，用户可以像对待多个桌面那样将工作分类，一个shell对应一个工作目录，拥有唯一的名称，只干一件事情。但是，电脑重启了怎么办，之前的工作环境就丢失了。怎样将当前的screen运行实例作为一个会话保存起来供下次使用呢？

办法是有的，那就是用配置文件`~/.screenrc`。

下面是一个配置文件的例子

{% highlight bash linenos %}
screen -t "bzr"
stuff "bzr diff | colordiff"
screen -t "misc"
screen -t "devsvr"
stuff "cd ~/google_appengine^M"
stuff "./dev_appserver.py -p 8084 ~/shared/appengine/conquer-on-contact/root/"
screen -t "update"
stuff "cd ~/google_appengine^M"
stuff "./appcfg.py update ~/shared/appengine/conquer-on-contact/root/"
 
#change the hardstatus settings to give an window list at the bottom of the
#screen, with the time and date and with the current window highlighted
hardstatus alwayslastline 
hardstatus string '%{= kG}[ %{G}%H %{g}][%= %{= kw}%?%-Lw%?%{r}(%{W}%n*%f%t%?(%u)%?%{r})%{w}%?%+Lw%?%?%= %{g}][%{B} %d/%m %{W}%c %{g}]'
vbell on
defscrollback 1024
startup_message off
autodetach on
defutf8 on
{% endhighlight %}

`screen`的`-t`选项显然就是指定标题或名称，`stuff`的作用是为当前的shell指定任务，实际上相当于粘贴文本。注意，如果想执行命令，需要在文本末尾加上`^M`字符，注意，这是一个字符，也就是`CR`字符，即`\r`。它在vim如果显示出来看起来就是`^M`。

给出在vim中输入`CR`字符的几种方法：

  - 插入模式下，`C-V Enter`
  - 插入模式下，`C-V C-M`。命令行模式中也可以。
  - 插入模式下使用digraph，`C-K C R`

如果`C-V`已经有其它用途了，那就只好使用`C-K C R`了。另外，也可以用其它命令生成这个字符
{% highlight bash %}
echo -e "\r" >file
{% endhighlight %}

你也可以将配置文件存储到任意文件`screensc`中，然后，用下面命令加载
{% highlight bash %}
screen -S "SESSION_NAME" -c screensc
{% endhighlight %}


## 参考文献

  - [Saving your sessions with GNU Screen](http://log.brandonthomson.com/2009/06/saving-your-sessions-with-gnu-screen.html)
