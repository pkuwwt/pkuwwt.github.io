---
layout: blog
comments: true
title: Python使用问题集锦
---

## 关于class中的成员变量
有一种成员变量需要特别小心，它们是直接声明在类定义中的成员变量，而非声明在`__init__`中。这种成员变量如果为对象类型(object)，则多个类实例会共享一个。


## 关于Warning
如果你想像Error一样捕捉Warning，可以使用`warnings`库

{% highlight python %}
import warnings
warnings.filterwarnings('error')
{% endhighlight %}

## 关于zip的逆过程
即将二元组列表，变成多个列表。

{% highlight python %}
zip(*[(1,2),(1,2),(1,2)])
zip(*[(1,2,3),(1,2,3),(1,2,3)])
{% endhighlight %}

得到的结果是元组的列表，比如`[(1,1,1),(2,2,2)]`。
