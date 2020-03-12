---
vim: wrap expandtab ft=markdown
layout: blog
comments: true
title: Jekyll中使用MathJax
---

在网页中使用latex最流行的解决方案应该是MathJax。这是一个基于JavaScript的Latex渲染引擎，它将网页中的Latex公式转变成多个不同字体的文字或图片的组合。

在Github的Page中使用数学公式，也就是在Jekyll中使用数学公式，MathJax似乎是唯一的选择。

唯一担心的是，Latex中的一些符号，比如下划线会与Markdown中的下划线冲突，但似乎实用过程中又没遇到什么问题。

## 第一步，将`_config.yml`中的markdown修改为
{% highlight html %}
markdown: kramdown
{% endhighlight %}

本地使用jekyll时可能需要额外安装kramdown
{% highlight bash %}
gem install kramdown
{% endhighlight %}

kramdown是一个Markdown解析器，它能够正确解释公式内部的符号，不会与Markdown语法冲突，比如不会将`^`符号变成`<sup></sup>`标签。


## 第二步，在header中添加引用和设置代码。

也就是`_include/header.html`中。
{% highlight html%}
<script type="text/x-mathjax-config">
MathJax.Hub.Config({
                  tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}
                          });
</script>
<script type="text/javascript"
  src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML">
</script>
{% endhighlight %}

## 第三步，在Markdown中使用Latex数学公式

比如行内公式：
{% highlight latex %}
$$E=mc^2$$ is a inline formula
{% endhighlight %}


比如行间公式(Lorentz方程)：
{% highlight latex %}
$$ 
\begin{aligned} \dot{x} &= \sigma(y-x) \\ 
\dot{y} &= \rho x - y - xz \\ 
\dot{z} &= -\beta z + xy \end{aligned} 
$$
{% endhighlight %}

注意，行间公式前后应该都留空行，使得公式能够居中显示。

另外，kramdown的latex语法行内和行间公式都是`$$`符号作为分隔符。虽然和一般的使用习惯不同，但是可以保证`_`, `^`, `\`之类符号能够正确解析。


## 示例
Markdown代码参见[github.com/pkuwwt/pkuwwt.github.com/](http://github.com/pkuwwt/pkuwwt.github.com/)

### Lorentz方程 

$$ 
\begin{aligned} \dot{x} &= \sigma(y-x) \\ 
\dot{y} &= \rho x - y - xz \\ 
\dot{z} &= -\beta z + xy \end{aligned} 
$$

### Cauchy-Schwarz不等式 

$$ 
\left( \sum_{k=1}^n a_k b_k \right)^2 \leq \left( \sum_{k=1}^n a_k^2 \right) \left( \sum_{k=1}^n b_k^2 \right)
$$

### 某种诡异的叉乘公式

$$
\mathbf{V}_1 \times \mathbf{V}_2 =  \begin{vmatrix} \mathbf{i} &\mathbf{j} &\mathbf{k} \\ 
\frac{\partial X}{\partial u} &  \frac{\partial Y}{\partial u} & 0 \\ 
\frac{\partial X}{\partial v} &  \frac{\partial Y}{\partial v} & 0 \end{vmatrix} 
$$

### 二项概率分布(抛$n$次硬币出现$k$次头的概率)

$$ 
P(E)   = {n \choose k} p^k (1-p)^{ n-k} 
$$

### Ramanujan恒等式

$$ 
\frac{1}{\Bigl(\sqrt{\phi \sqrt{5}}-\phi\Bigr) e^{\frac25 \pi}} 
= 1+\frac{e^{-2\pi}} {1+\frac{e^{-4\pi}} {1+\frac{e^{-6\pi}} 
    {1+\frac{e^{-8\pi}} {1+\ldots} } } } 
$$

### Rogers-Ramanujan恒等式

$$ 
1 +  \frac{q^2}{(1-q)}+\frac{q^6}{(1-q)(1-q^2)}+\cdots =
\prod_{j=0}^{\infty}\frac{1}{(1-q^{5j+2})(1-q^{5j+3})},
    \quad\quad \text{for $|q|<1$} 
$$

### Maxwell方程

$$
\begin{aligned} \nabla \times \vec{\mathbf{B}} -\, \frac1c\, \frac{\partial\vec{\mathbf{E}}}{\partial t} & = \frac{4\pi}{c}\vec{\mathbf{j}} \\   
\nabla \cdot \vec{\mathbf{E}} & = 4 \pi \rho \\ 
\nabla \times \vec{\mathbf{E}}\, +\, \frac1c\, \frac{\partial\vec{\mathbf{B}}}{\partial t} & = \vec{\mathbf{0}} \\ 
\nabla \cdot \vec{\mathbf{B}} & = 0 \end{aligned} 
$$


