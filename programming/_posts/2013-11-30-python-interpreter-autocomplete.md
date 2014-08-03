---
vim: wrap expandtab ft=markdown
layout: blog
comments: true
title: python解释器中的自动补全
---

只需要启动时执行一条命令即可
{% highlight python %}
import rlcompleter, readline
readline.parse_and_bind('tab:complete')
{% endhighlight %}

可以将上述的代码存于`~/.pythonrc.py`文件中。

然后，在`~/.bashrc`中设置
{% highlight python %}
export PYTHONSTARTUP=~/.pythonrc.py
{% endhighlight %}

这样，每次启动终端，bash就会设置PYTHONSTARTUP这个环境变量，然后，python启动时就会使用这个变量指定的文件中的初始化代码。

在python解释器中，输入一个变量的一部分，或者变量后面加句点，再按TAB键就可以看到自动补全的威力。

