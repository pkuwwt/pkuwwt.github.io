---
layout: blog
comments: true
title: 使用tikz绘制函数
---

虽然tikz具备计算功能，但是要想绘制解析函数，确实非其长项。然而，tikz有一种使用gnuplot的机制，gnuplot可是绘制这种图像的好手。

直接上代码

{% highlight latex %}
\documentclass{article}
\usepackage{tikz}

\begin{document}
\begin{center}\begin{tikzpicture}[domain=0.25:4]
	\draw[->] (-0.2,0) -- (4.2,0) node[right] {$x$};
	\draw[->] (0,-1.2) -- (0,4.2) node[above] {$y$};
	\draw[color=red] plot[id=x] function{1/x} node[above] {$y=\frac{1}{x}$};
\end{tikzpicture}\end{center}
\end{document}
{% endhighlight %}

代码中的`function{1/x}`的作用当然就是指定函数啦。

这里的`id=x`的作用是生成一个`jobname.<id>.table`，比如test.x.table。但是这个文件其实是离散点的数据文件，它依赖于`gnuplot`。具体来说，latex生成一个`jobname.<id>.gnuplot`文件，然后会尝试用`gnuplot`来处理此文件，并生成`jobname.<id>.table`文件。

但是，由于安全原因，latex很可能不会调用`gnuplot`，因此，需要手动执行`gnuplot jobname.<id>.gnuplot`。有了`jobname.<id>.table`，latex编译tikz图片时就不需要`gnuplot`了。

