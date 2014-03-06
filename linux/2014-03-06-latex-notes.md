---
layout: blog
comments: true
title: LaTeX笔记
---

# 日常使用
论文中的竖直的beta，而非math模式下的斜体beta

{% highlight latex %}
%\usepackage{textgreek}
% may need texlive-babel-greek and texlive-cbfonts
this is upright \textbeta, rather than italic $\beta$
{% endhighlight %}


# 包介绍

  * tabu: 将longtable和tabularx结合起来，既可以跨页，又可以控制单元格式

