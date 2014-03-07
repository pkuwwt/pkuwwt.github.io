---
layout: blog
comments: true
title: LaTeX笔记(texlive)
---

# 帮助系统
texdoc和texdef两条命令。
{% highlight latex %}
% documentation for package caption
texdoc caption
% source of definition of \bibliography
texdef -t latex -s bibliography
{% endhighlight %}

# 日常使用
论文中的竖直的beta，而非math模式下的斜体beta

{% highlight latex %}
%\usepackage{textgreek}
% may need texlive-babel-greek and texlive-cbfonts
this is upright \textbeta, rather than italic $\beta$
{% endhighlight %}


在mdframed或minipage中不能用float/figure/table等浮动环境，如果你还想要有标题(比如添加了一张图片)，这时候你可以使用`caption`包的`\captionof`命令，它的第一个参数表示使用哪种float环境的格式。
{% highlight latex %}
%\usepackage{caption}
\begin{minipage}{\textwidth}
\includegraphics{pic.png}
\captionof{figure}{This is a picture caption.\label{fig:pic}}
\end{minipage}

This is reference to a picture\ref{fig:pic}.
{% endhighlight %}


# 包介绍

  * tabu: 将longtable和tabularx结合起来，既可以跨页，又可以控制单元格式

