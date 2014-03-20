---
layout: blog
comments: true
title: 使用maxima求解非线性方程组
---

下列的方程，手算实在是没有胜算。

$$
\begin{bmatrix}
	x_0 & -x_1 & -x_2-2 & -x_3-1 \\
	0   & 2x_0 & -1 & -2 \\
	2   & 1    & 2x_0 & 0 \\
	1   & 2    &   0 & 2x_0 
\end{bmatrix}
\begin{bmatrix}
	x_0 \\ x_1 \\ x_2 \\ x_3 
\end{bmatrix} = 0
$$

如果你不是想存心考验自己的手算心算笔算水平的话，还是用现在的工具的好。`maxima`可以满足这个需求。直接上指令

{% highlight bash %}
A: matrix(
[x0,-x1,-x2-2,-x3-1],
[0,2*x0,-1,-2],
[2,1,2*x0,0],
[1,2,0,2*x0]);
c: transpose(matrix([x0,x1,x2,x3]));
B: A.c;
algsys([B[1,1],B[2,1], B[3,1], B[4,1]], [x0,x1,x2,x3]);
{% endhighlight %}

其中，有几个地方需要注意，赋值不是等号，而是冒号。矩阵最小下标是1，不是0。矩阵乘法是`A.c`，`A*B`表示对应元素相乘。`algsys`第一个参数是表达式列表，
第二个参数是未知变量，每个表达式中后面的`=0`都是省略了的。

结果如下：

$$
\begin{bmatrix}0\\0\\0\\0\end{bmatrix}
\begin{bmatrix}0\\0\\-\frac{6}{5}\\\frac{3}{5}\end{bmatrix}
\begin{bmatrix}-\frac{3i}{2}\\-\frac{3i}{2}\\-\frac{3}{2}\\-\frac{3}{2}\end{bmatrix}
\begin{bmatrix}\frac{3i}{2}\\\frac{3i}{2}\\-\frac{3}{2}\\-\frac{3}{2}\end{bmatrix}
\begin{bmatrix}-\frac{i}{2}\\\frac{i}{2}\\-\frac{1}{2}\\\frac{1}{2}\end{bmatrix}
\begin{bmatrix}\frac{i}{2}\\-\frac{i}{2}\\-\frac{1}{2}\\\frac{1}{2}\end{bmatrix}
$$
