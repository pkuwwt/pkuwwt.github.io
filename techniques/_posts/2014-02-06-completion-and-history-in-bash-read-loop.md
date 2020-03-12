---
layout: blog
comments: true
title: 在Bash的输入循环中使用readline和历史记录
---

在Bash编程中，有时候会希望交互式地从终端获取输入。比如
{% highlight bash %}
while read -p "input: " input; do
	echo "output:  ${input}"
done
{% endhighlight %}

一个显而易见的需求是像终端那样的交互性，比如TAB补全和历史记录。TAB补全是由readline库支持，而历史记录则是bash本身的功能。

从`man read`中可以知道`read -e`是支持readline的。而历史记录则由bash的内建命令history来实现：

  - `history -r file` 读取一个历史记录文件为当前历史记录，一行一个记录
  - `history -s line` 添加一行到当前历史记录中
  - `history -w file` 将当前历史记录文件写到文件中去

因此，上面的程序修改为

{% highlight bash %}
history -r ~/.bash_history
while read -e -p "input: " input; do
	history -s ${input}
	echo "output:  ${input}"
done
history -w ~/.bash_history
{% endhighlight %}

顺便记录一下终端下bash的常用快捷键:

  - `Ctrl-a` 光标回到开头
  - `Ctrl-e` 光标移到结尾
  - `Ctrl-f` 光标后移一位(forward)
  - `Ctrl-b` 光标前移一位(back)
  - `Ctrl-p` 前一个历史记录(previous)
  - `Ctrl-n` 后一个历史记录(next)

注意，上面所列是默认的快捷键，来自于emacs快捷键，要想修改为vim模式，使用`set -o vi`。你也可以用`set -o`查看当前的选项。

