---
vim: wrap expandtab ft=markdown
layout: blog
title: MathJax使用示例
---

在网页中使用latex最流行的解决方案应该是MathJax。这是一个基于JavaScript的Latex渲染引擎，它将网页中的Latex公式转变成多个不同字体的文字或图片的组合。

MathJax的详细用法参见[MathJax TeX and Latex Support](http://docs.mathjax.org/en/latest/tex.html)。

下面是MathJax的一个简单示例，如何你的电脑可以连网，那你可以直接在浏览器中显示出效果。

{% highlight html %}
<!DOCTYPE html>
<html>
<head>
<title>MathJax TeX Test Page</title>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}});
  </script>
  <script type="text/javascript"
    src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML">
    </script>
    </head>
    <body>
    When $a \ne 0$, there are two solutions to \(ax^2 + bx + c = 0\) and they are
    $$x = {-b \pm \sqrt{b^2-4ac} \over 2a}.$$
    </body>
    </html>
{% endhighlight %}

[试一试](../img/test_mathjax.html)

