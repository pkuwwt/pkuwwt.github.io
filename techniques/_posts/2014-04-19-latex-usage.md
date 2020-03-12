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

## 如何将论文作者的地址写到脚注里
对于`\documentclass{article}`，答案是用`\thanks`。

{% highlight latex %}
\documentclass{article}

\title{My great paper}
\author{One author\thanks{some info} \and Another author\thanks{more info}}

\begin{document}
\maketitle

\end{document}
{% endhighlight %}

那么，如果有多个作者，而一个作者属于多个部门，而不同作者属于同一部分怎么办？可以定义一个重用脚注的命令。还是用`\thanks`来定义脚注，然后，后面再引用此脚注。下面定义的`\samethanks`要么没有参数，直接引用前一个`\thanks`内容，要么用一个可选参数指定重用哪一个。

{% highlight latex %}
\newcommand*\samethanks[1][\value{footnote}]{\footnotemark[#1]}
\author{Foo\thanks{University of Podunk, Timbuktoo}
	\and Bar\samethanks
		\and Baz\thanks{Somewhere Else}
	\and Bof\samethanks[1]
		\and Hmm\samethanks}
{% endhighlight %}

