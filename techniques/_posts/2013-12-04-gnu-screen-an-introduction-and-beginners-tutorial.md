---
vim: wrap expandtab ft=markdown
layout: blog
comments: true
title: GNU Screen--介绍和初学者指南[译]
---

[Source](http://www.kuro5hin.org/story/2004/3/9/16838/14935)

作者: 来自于[Technology](http://www.kuro5hin.org/section/tech)的[jeduthun](http://www.kuro5hin.org/user/jeduthun)

大部分的类Unix操作系统，比如Linux, MacOS X, 以及BSD，都有一个称为[GNU Screen](http://www.gnu.org/software/screen/screen.html)的终端小工具。在终端武士手中，这是一个强悍的工具，在文本人机交互世界中堪称是多功能的瑞士军刀。

这个工具虽然非常有用，但是用者寥寥。为何？一则少有人知道它的存在，二则即使知道也不清楚它是干什么用的。在本文中，我会解释这个屏幕(screen)到底能为你做神马，并且提供一些简单的指令来帮助你使用screen来完成基本的任务。我的听众应该是那些熟练使用命令行却少有使用screen者。

## screen能干啥

Screen的最准确的描述是终端选择器(terminal multiplexer)。通过它，你可以在一个终端内运行任意多个基于终端的应用，包括交互式命令shell，基于文本光标的应用，文本编辑器等。大部分沉迷于屏幕的人都有这样的需求。我曾经在登陆后开启十多个终端模拟器：一个用来读邮件，一个用来编辑代码，一个编译代码，一个读新闻，一个用于登陆网站的shell，诸如此类。现在，我只启动一个终端模拟器，然后在里面运行screen。问题解决了。

screen其它主要的功能是能够将终端模拟器与正在运行的程序解耦合。这表示你可以让程序继续运行，即使你不小心关掉了终端模拟器，甚至登出帐户后它依然在运行，然后，你可以原样恢复到你面前。这实际上构成了一个"会话"，你可以在里面运行多个终端程序，这些程序仿佛飘浮不定，你可以将它们绑定到任何终端上去，没有终端也木有关系。


## 开始使用screen：启动并在程序之间切换

启动screen只需要在你最喜欢的命令提示符中输入`screen`命令即可。你很可能会看到一个欢迎信息。忽略之，你得到的是一个包含了shell提示符的空的终端界面，和启动screen之前没有两样。发生了什么？

每个在screen下运行的程序都是在一个窗口中运行，每个窗口都由唯一的数字标识。screen生成一个新窗口，标号为0，然后在里面启动一个命令行shell。在你的新窗口中输入一些命令，以便你能够呆会儿切换回来时还能识别出来。

现在创建另外一个窗口，其标号应该是1。要实现这一点，输入`C-a c`，也就是按着`Ctrl-a`，然后再按`c`(你可以记为: *c*reate window)。

现在，你有了两个窗口，可以来回切换了。切换的快捷键是`C-a C-a`，它会在最近的两个窗口中来回切换。在你拥有多个程序时，其它一些窗口切换方法会派上用场：

  * `C-a n`和`C-a p`，按窗口标号进入前一个/后一个窗口。
  * `C-a N`，其中N指的是0-9之间的数字，切换至指定的窗口
  * `C-a "`，获得窗口列表的全屏显示。你可以在这个列表中使用方向键导航(或vi风格的`j`,`k`键)，选中一个窗口之后(高亮)，使用回车键`Enter`去激活。
  * `C-a w`，给出一个小的，不可交互的窗口列表。有可能显示在终端的标题栏上。

当你使用一个窗口时，输入`C-a A`给它设置一个名称。这个名称会被用于窗口列表，也可以帮助你记忆多个窗口中每个窗口的用途。

退出窗口中的最后一个程序会导致这个窗口消失。你也可以用`C-a K`来终止运行异常的程序。


## 分离与再附着：终端解耦合的魔法

如果你操练了上述的功能，你已经成功创建了一个screen会话。你可以从这个会话中分离，快捷键是`C-a d`。你也可以直接关闭包含该会话的终端模拟器。但是，这两种操作都没有实际终止会话。它们所做的只不过是将会话与当前终端解除绑定。你用screen运行的所有程序仍然在后台运行。我不骗你。


试验一下：只关闭你做上面的练习所用的终端模拟器。然后，登出当前用户，然后再登陆进去。开启一个新的终端模拟器，执行`screen -r`(这里的`r`明显指的是reattach)。你会回到你分离时的那个状态。

**译者注：对linux系统是如此，但对于cygwin可能并非如此。cygwin中如果关闭了所有的窗口也就相当于关机了。**

你可以充分利用想像力，将这种功能用到很多场合中。你可以让所有必要的程序运行一遍，让它们保留在一个持久的screen会话中。有些人可以让这种"screen运行"维持数月。

另外一个分离和再附着的好的用途是作为一个控制台模式的"远程桌面"。你可以从一个工作时的screen会话中分离出来，然后登陆到家里的机器上，最后再附着。非常，非常贴心。只需要再费一点点力气，你甚至可以让多个终端都附着到同一个会话上----这对于协作和会议是非常有用的。

## 复制，粘贴，和回滚缓冲区

screen记录了一定数量的回滚行(大小是可配置的)，你会用到这个功能，因为在使用screen时，你就不能再用终端模拟器的回滚功能了。可以通过进入"复制模式"来访问回滚缓冲区，快捷键是`C-a [`，退出按`ESC`即可。你可以在回滚缓冲区中标记文字，然后用`C-a ]`进行粘贴。screen还能够记录日志到文件，在这里就不多介绍了。

## 监控沉寂与活动

一个批量执行程序的缺点是不能同时监控所有程序的运行，因为一般你只能一次看到一个。(事实上，你可以将screen分裂成多个，然后同时看多个，但这个高级功能不在本文讨论范围之内。) 为了缓解这个问题，screen支持用户监控沉寂了的窗口(比如一个编译已经结束了)，或活动窗口(比如有人在你的IRC通道上呼叫你了)。

开启或结束当前窗口的30秒沉寂的快捷键是`C-a _`，而监控活动窗口的开关快捷键是`C-a M`。

## 让它离开

如你所见，screen并不容易被终止。你不能通过关闭终端来关闭screen。(事实上，你可以做到，只不过那些进程仍然运行在系统中，随时准备再附着。) 那么，有没有一个"退出"键来完全退出screen呢？

据我所知，唯一正确的方式是关闭每个screen窗口(当然，给进程发信号的方法不在此列)。退出每一个正在运行的程序和shell，窗口也就关闭了。当最后一个运行在screen中的程序退出之后，screen自己也会知趣离开。


## 其它

screen的功能远超本文内容，但这些内容已经足够你开始使用screen了。你可以执行`C-a ?`来获取screen的命令列表。screen的man页面也包括了大量的信息。另外，如果你有问题，下面还有一些网络资源。

  * [Yahoo GNU Screen Group](http://groups.yahoo.com/group/gnu-screen/) 一个screen的非常活跃的邮件列表。许多博学的人才在上面挂着。
  * [Sven Guckes' Screen Page](http://www.guckes.net/screen/) 另外一个概述页面，当然，内容要比本文丰富。
  * [官方screen主页](http://www.gnu.org/software/screen/screen.html) 不需解释。这个页面上的细节比较少。
  * [screen的manual](http://www.cis.ohio-state.edu/cgi-bin/info/info/screen,Top) 排版很好，章节分明。是一个很好的参考。重点看一下关于使用`.screenrc`配置screen的章节。
  * [Screen FAQ](http://www4.informatik.uni-erlangen.de/~jnweiger/screen-faq.html) 不是给新手用的，但是解决问题的很好的资源。


## 翻译对照表

  * detach: 分离
  * attach:  附着
  * reattach:  再附着
  * terminal: 终端
  * console: 控制台
  * multiplexer: 选择器
  * silence: 沉寂。本文中指的是一个程序执行完成或一直没有动静。
