---
layout: blog
comments: true
title: 隐函数定理
---

## 隐函数定理表述
令$f:\mathbf{R}^n\times\mathbf{R}^m\to\mathbf{R}^m$为连续可微函数。$f(x,y)=c$确定了一个区域$D\subset\mathbf{R}^{n+m}$。
对于任意$(a,b)\in\mathbf{R}^n\times\mathbf{R}^m$，若方阵$[\partial f/\partial y](a,b)$可逆，则存在包含$a$的开集$U\subset\mathbf{R}^{n}$，和包含$b$的开集$V\subset\mathbf{R}^m$，以及连续可微函数$g:U\to V$，满足

$$
\{(x,g(x)): x\in U\} = \{(x,y)\in U\times V: f(x,y)=c\}
$$

## 示例
以单位圆$f(x,y)=x^2+y^2=1$为例，$1\times1$方阵$\partial f/\partial y$为$2y$，因此，在$(\pm1,0)$处，无隐函数存在，这是符合实际情况的。

## 参考文献

  * [Wikipedia:Implicit function theorem](http://en.wikipedia.org/wiki/Implicit_function_theorem)

