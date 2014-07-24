---
layout: blog
comments: true
title: python的profile工具
---

`cProfile`是python自带的统计程序运行情况的profile工具。使用方法很简单，将需要测试的代码封装在一个模块的一个函数中，然后用`cProfile.run`执行即可。

{% highlight python %}
import cProfile
import re
cProfile.run('re.compile("foo|bar")')
{% endhighlight %}

