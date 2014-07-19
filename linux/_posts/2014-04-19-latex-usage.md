---
layout: blog
comments: true
title: LaTeX使用方法集锦
---

## 如何让每一页的`footnote`重新编号
`\footnote`的默认行为是全文统一编号，有时候看起来完全不顺眼，可以使用`perpage`包来改变这种行为

{% highlight latex %}
\usepackage{perpage}
\MakePerPage{footnote}
{% endhighlight %}


## 为数学公式逐行增加注释
使用`amsmath`包中的`align`环境。
{% highlight latex %}
\documentclass{article}
\usepackage{amsmath}

\begin{document}
\begin{align*}
    3+x &=4 && \text{we are trying to solve for } x\\
	  x &=4-3 && \text{Subtract 3 from both sides}\\
	  x &=1   && x \text{ must be one}
\end{align*}
\end{document}
{% endhighlight %}
注意，这里不能把公式写到`\text`命令里面，而在里面嵌入行内公式`$x$`是不行的。另一个命令`\textrm`中可以嵌入行内公式。:w

