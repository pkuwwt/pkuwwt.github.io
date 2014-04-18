---
layout: blog
comments: true
title: LateX使用方法集锦
---

## 如何让每一页的`footnote`重新编号
`\footnote`的默认行为是全文统一编号，有时候看起来完全不顺眼，可以使用`perpage`包来改变这种行为

{% highlight latex %}
\usepackage{perpage}
\MakePerPage{footnote}
{% endhighlight %}

