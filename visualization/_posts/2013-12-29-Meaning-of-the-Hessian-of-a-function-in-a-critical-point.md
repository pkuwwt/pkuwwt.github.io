---
layout: page
title: 函数的关键点上的海森(Hessian)矩阵的含义[译]
---


原题：[Meaning of the Hessian of a function in a critical point](http://www.math.ethz.ch/~petrache/hessian.pdf)


作者：Mircea Petrache

时间: 2012年1月1日

考察一个函数$f: R^n \to R$，假定它是可微并至少具有2阶连续性(即所有偏微分形式$f_{ij}=f_{x_ix_j}=\partial_{ij}^2f$
		
$= \partial_{x_ix_j}^2\cdot f$ $:=\frac{\partial^2f}{\partial x_i\partial x_j} : R^n \to R$都是连续的，其中$i,j\in\{1,\cdots,n\}$)。

回忆$f$上的关键点(critical point)$P$的定义：点$P\in R^n$，且满足$f$在$P$处的梯度为0。即

$$
\nabla f(P) = 0
$$

或更具体的形式是

$$
\left(\begin{array}{c}
\frac{\partial f}{\partial x_1}(P) \\
\vdots \\
\frac{\partial f}{\partial x_n}(P)
\end{array}\right) = \left(\begin{array}{c}0 \\ \vdots \\ 0\end{array}\right)
$$

然后，我们将给出一个方式(实际上也是最标准的方式)来判断一个点关键点$P$是否是局部最大，局部最小或鞍点。我们会用到函数$f$的二次微分矩阵，也称为$f$在$P$处的海森矩阵(Hessian Matrix)。此矩阵记为$Hf(P)$，并等价于(还需要给出"最佳近似"的正确含义)

$$
Hf(P) := \left(\begin{array}{cccc}
\frac{\partial^2f}{\partial x_1\partial_1}(P) & \frac{\partial^2f}{\partial x_1\partial_2}(P)  & \cdots & \frac{\partial^2f}{\partial x_1\partial x_n}(P) \\
\frac{\partial^2f}{\partial x_2\partial_1}(P) & \frac{\partial^2f}{\partial x_2\partial_2}(P)  & \cdots & \frac{\partial^2f}{\partial x_2\partial x_n}(P) \\
\vdots & \vdots & \ddots & \vdots \\
\frac{\partial^2f}{\partial x_n\partial_1}(P) & \frac{\partial^2f}{\partial x_n\partial_2}(P)  & \cdots & \frac{\partial^2f}{\partial x_n\partial x_n}(P) 
\end{array}\right).
$$

## 梯度与海森的几何含义

### 一个变量的函数的梯度表示什么意思

回忆一下，单变量函数$f: R\to R$在某个点处的微分$f'(P)$具有如下的几何含义。考虑$f$的图，记为点集$G(f) := \{(x,y) \in R^2 : y = f(x) \}$。 通常我们在2维空间上将这个$R^2$的子集绘制出来，并将其直接视为"函数$f$"，隐含将其等价于函数本身。

$f'(P)$表示为图$G(f)$在点$(P,F(P))$处的切线的倾角。

特别是，在关键点$x=P$(即$f'(P)=0$)下的切线必须是水平的。即，在$P$附近的函数$f$的最好近似是常量函数。

#### 一阶泰勒多项式
另一种寻找$f$在$P$附近的最好近似的方式是考虑所谓的一阶泰勒多项式。这种多项式记为$j^1_Pf(x)$，定义为

$$
\begin{array}{rcl}
j^1_Pf(x) &=& f(P) + f'(P)(x-P) \\
&=& f(P) ~~~~\textrm{if}~~~~ f'(P) = 0
\end{array}
$$

另一种理解$j^1_Pf(x)$的方式是，视"最容易"满足$g(P)=f(P)$且$g'(P)=f'(P)$的函数$g$。

### 单变量函数的海森表示什么意思

现在，假定我们想要知道$f$与"$j^1_Pf$在$P$附近的最佳近似"偏离多少，那该怎样测量呢?

首先考虑差分函数

$$
d(x) := f(x) - j^1_Pf(x) = f(x) - f(P) - f'(P)(x-P)
$$

现在的目标变成了用最好的方式来近似$d$。我们观察到"一阶$d(x)$的最佳近似"目前仍然只是0，而关于"最佳近似"的思想变成了：如果$d$有一个比0好的近似$D$，那么$j^1_Pf+D$是一个比$j^1_Pf$更好的$f$的近似。

如果我们按照上述的思想深入探讨，那么一个合理的想法应该是寻找一个$f$的"二阶最佳近似"。这就是所谓的二阶泰勒多项式，它是"$f(x)$的最佳近似二阶多项式"(虽然在一定程度上并不准确)，定义为：

$$
j^2_Pf(x) = f(P) + f'(P)(x-P) + \frac{1}{2!}f''(P)(x-P)^2
$$

现在，让我们集中考察表达式中由一阶最佳近似$j^1_Pf$到二阶最佳近似$j^2_Pf$所增加的新项

$$
\frac{1}{2!}f''(P)(x-P)^2
$$

它基本上依赖于$f$在$P$处的二阶微分，也就是$f$的海森。

理解$f''(P)$的意义的最好方式是考察当$P$是$f$的关键点时的几种情况。

$P$是关键点表明$f$的图在点$(P,f(P)$处切线水平(即$f'(P)=0)$。我们说$f$在$P$附近的最佳近似多项式是

$$
f(P) + \frac{1}{2!}f''(P)(x-P)^2
$$

此多项是在顶点$P$处形成一个抛物线的图，当$f''(P)>0$时两翼向上，$f''(P)<0$时两翼向下。如果$f$接近于抛物线，保持两翼向上，则$P$是$f$的一个局部最小点，如果$f$接近于抛物线保持两翼向下，则$P$是$f$的一个局部最大点。如果$f''(P)=0$，那么二阶最佳近似仍然不足以说明$f$在$P$附近的行为，因为和一阶近似一样，残差仍然是一个常值函数。我们可以总结为

$$
\textrm{if}~ f'(P)=0, P ~\textrm{is}~ \left\{ \begin{array}{rcl}
\textrm{a local maximum for}~f &\textrm{if}& f''(P)<0 \\
\textrm{a local minimum for}~f &\textrm{if}& f''(P)>0 \\
\textrm{unknown critical point for}~f &\textrm{if}& f''(P)=0 
\end{array}\right.
$$

现在，我们可以开始进行针对梯度向量和海森矩阵的类似的解读，这时的$f$有多个变量，比如$f:R^n\to R$，其中$n>1$。


### 多变量情况下的梯度和海森矩阵
如前所述，理解一阶和二阶微分含义的关键是$f$的泰勒多项式(至少在讨论关键点时如此)。所以，我需要将函数$f:R^n\to R$的一阶和二阶泰勒多项式公式写下来。其形式类似于单变量情况。我们将点$P\in R^n$的坐标记为$(\bar x_1,\cdots, \bar x_n) = P$。然后$j^1_Pf$的表达式是(观察一下，与前面章节具有相似性)：

$$
\begin{array}{rcl}
j^1_{(\bar x_1,\cdots, \bar x_n)}f(x_1,\cdots, x_n) 
&=& f(\bar x_1,\cdots, \bar x_n)  \\
&& +\partial_{x_1}f(\bar x_1,\cdots, \bar x_n)(x_1-\bar x_1) \\
&& +\partial_{x_2}f(\bar x_1,\cdots, \bar x_n)(x_2-\bar x_2) \\
&& + \cdots \\
&& +\partial_{x_n}f(\bar x_1,\cdots, \bar x_n)(x_n-\bar x_n) \\
&=& f(P) + \sum_{i=1}^n\partial_{x_i}f(P)(x_i-\bar x_i) \\
&=& f(P) + \nabla f(P)\cdot(x-P) 
\end{array}
$$

在最后一行中，运算符"$\cdot$"表示$R^n$上的向量的标量积。如果有两个向量$v=(v_1,\cdots,v_n)$和$w=(w_1,\cdots,w_n)$，标量积"$\cdot$"的定义为$v\cdot w=v_1w_1+\cdots+v_nw_n=\sum_{i=1}^nv_iw_i$。这是上面$j^1_Pf$最后一个等式的来由。

同样，$j^1_Pf(x)$是$f$在$P$附近的1阶最佳近似(这次是针对变量$x_1,\cdots,x_n$)。

我们也可以给出$\nabla f(P)$的更"几何"的含义(需要更多想象力)。考虑函数$f$的图，即所有点$(x,f(x)), x\in R^n$构成的$f$的图，也是$R^{n+1}$的子集。如果$\nabla f(P)=0$，则$f$的图的"切超平面"将与水平超平面$\{x_1,\cdots, x_n,0\in R^{n+1}\}$平行。因为这种情况下$j^1_Pf(x)=f(P)$，所以当$f$在$P$附近进行一阶多项式近似时，我们无法将残差与常函数区分。


再考虑二阶多项式，我们获得二阶泰勒多项式

$$
\begin{array}{rcl}
j^2_P f(x) &=& f(P) + \sum_{i=1}^n\partial_{x_i}f(P)(x_i-\bar x_i) + \frac{1}{2!}\sum_{i,j=1}^n\partial_{x_i}\partial_{x_j}f(P)(x_i-\bar x_i)(x_j-\bar x_j) \\
&=& f(P) + \nabla f(P)\cdot (x-P) + (x-P)^T\cdot Hf(P)\cdot (x-P)
\end{array}
$$


在上面最后两行中，我们使用了线性代数中的记号。如果$v,w$是$R^n$上的向量，而$A$是一个$n\times n$矩阵，则

$$
v^T\cdot A\cdot w = \sum_{i,j=1}^nv_iA_{ij}w_j
$$

注意$Hf(P)$是$f$在点$P$上的二阶微分，其$(i,j)$项是$\partial_i\partial_jf(P)$，这是上述$j^2_Pf(x)$最后一个等式的来由。

#### 深入海森矩阵，关于关键点$P$
我们将尽力模仿1.2节关于$f$在关键点$P$附近的二阶微分的讨论，只不过现在变量不仅仅只有一个。对于一个关键点而言，函数可以很好地近似于泰勒多项式

$$
j^2_Pf(x) =  f(P) + (x-P)^T\cdot Hf(P)\cdot (x-P)
$$

为了避免多余的记号，我们假定$P$是原点(向量$x-P$表示$x$的偏移量为$P$，现在不考虑偏移了)。因此，现在我们的关键点是原点：$\nabla f(0)=0$，上述公式变成

$$
j^2_0f(x) =  f(0) + x^T\cdot Hf(0)\cdot x
$$

为了继续讨论，我们注意到一个$C^2$-正规函数(即具有二阶微分且连续的函数)的二阶微分矩阵具有如下属性

**定理1** 如果$f: R^n\to R$是一个连续二阶可微函数，那么其两次微分可交换，即，对于所有的$i,j\in\{1,\cdots,n\}$，且所有的点$x\in R^n$，满足

$$
\frac{\partial^2f}{\partial x_i\partial x_j}(x) = \frac{\partial^2f}{\partial x_j\partial x_i}(x)
$$

对于海森矩阵而言，上述定理意味着$Hf(x)$对于所有的$x\in R^n$来说是一个对称矩阵(即$Hf(x)$的$(i,j)$项等于$(j,i)$项，换句话说此矩阵对于对角线来说是对称的)。让我们先回忆一下此类矩阵的性质。

#### 对称矩阵(回忆一下线性代数课)
回忆一下，对于一个$R$上的有限维向量空间$V$，其标量积为$<\cdot,\cdot>:V\times V\to R$(比如，$R^n$上欧氏标量积$<v,w>=v\cdot w=\sum_{i=1}^nv_iw_i$)，其线性对称算子是$L: V\to V$对于所有的$v,w\in V$满足$<v,L(w)>=<L(v),w>$。下面的命题很容易证明：

**命题2** 假设$A$是一个$n\times n$的对称矩阵，则函数$L_A:R^n\to R^n$

$$
L_A(v) = A\times v
$$

为$R^n$上的欧氏标量积($v\cdot w = \sum_{i=1}^nv_iw_i$)定义了一个线性对称算子。

我们知道如果$A\cdot V=\lambda v, \lambda\in R$，则向量$v$是$L_A$的特征向量。换句话说，$L_A$将$v$变换成其自身。如果$v$是其中一个特征向量，则数值$\lambda$称为$A$的特征值。(也许你知道正则矩阵$A$的特征值也可能是复数，但是如果$A$是对称阵时，它们事实上都是实数。)

你应该也还记得$R^n$的标准正交基：所有长度为1且互相垂直的向量构成的基底。典型的例子是常用基底，由$(1,0,\cdots,0)$, $(0,1,0,\cdots,0)$,...,等构成，这些向量只有一个分量为1其余为0。事实上，所有的标准正交基都可以通过对此常用基底进行旋转变换(同时旋转所有基底向量)和镜像变换(将一些基底向量变成反方向)得到。

在下面的定理中，我们可以看到通过旋转的方式，可以将一个对称矩阵表示的线性函数$L_A$变换为对角形式。下面是严格的表述：

**定理3(光谱定理的等价形式)** 给定一个对称$n\times n$实系数矩阵$A$，则可为其线性算子$L_A:R^n\to R^n$找到一个标准正交基。

特别是，$L_A$在新的基底下的形式为

$$
\left(\begin{array}{cccc}
\lambda_1 & 0 & \cdots & 0 \\
0 & \lambda_2 & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & \lambda_n
\end{array}\right)
$$

其中$\lambda_1, \cdots, \lambda_n$是$L_A$的特征值，并按照其重数重复出现。

如果你练习过线性代数，你还可以证明以下推论(可尝试$2\times2$矩阵，然后推广)。这对于你使用矩阵$A$的特征值会有用。

**推论4** $A$是一个对称$n\times n$矩阵，其行列式等于其线性算子$L_A:R^n\to R^n$的特征值的积。(特殊情况，如果$A$是对角形式，则行列式$det(A)$是对角线元素的积)

**推论5** $A$是一个对称$n\times n$矩阵，$A$的迹(定义为对角元素的和)等于$A$的特征值的和。

## 如何将对称矩阵的知识应用到泰勒多项式中

我们以前见过一个函数$f$如果有"好"(足够连续)的二阶微分，则关键点(假定是原点附近)附近的最好近似是二阶泰勒多项式

$$
j^2_0 f(x) = f(0) + x^T\cdot Hf(0) \cdot x
$$

现在，为了理解$f$在0附近的行为，我们可能还需要像定理3中那样"旋转坐标基底"，使得$Hf(0)$变成对角形式，即让特征值位于对角线上。为什么这种形式更方便呢？因为这使得上面的表达式更简单了：记$x$在"旋转"前在新的基底下的坐标为$y=(y_1,\cdots,y_n)$，(注意这里0仍然在0的位置上，而一般情况下需要在$P$附近旋转)，然后得到

$$
\begin{array}{rcl}
j^2_0f(y) &=& f(0) + y^T\cdot[NewHf(0)]\cdot y \\
&=& f(0) + \left(\begin{array}{c}y_1\\\vdots\\y_n\end{array}\right)^T\cdot\left(\begin{array}{cccc}\lambda_1&0&\cdots&0\\0&\lambda_2&\cdots&0\\\vdots&\vdots&\ddots&\vdots\\0&0&\cdots&\lambda_n\end{array}\right)\cdot\left(\begin{array}{c}y_1\\\vdots\\y_n\end{array}\right) \\
&=& f(0) + \sum_{i=1}^n\lambda_iy_i^2
\end{array}
$$

现在，我们开始解读最后的表达式，考察$j^2_0f(y)$在0附近相对于$y$的行为。当只变化一个坐标时此多项式会如何变换？然后，因为我们只允许一个坐标变化，我们再次获得一个只有一个变量$y_1$的函数

$$
j^2_0f(y) = \lambda_1y_1^2 + f(0) + \sum_{i=2}^n\lambda_iy_i^2 = \lambda_1y_1^2 + \textrm{constant}
$$

此函数的图又可以画在平面上了(水平坐标是$y_1$坐标，纵坐标是$j^2_0f$的值)，因此可以像1.2节那样进行讨论

  - 如果$\lambda_1>0$，则是一个两翼向上的抛物线
  - 如果$\lambda_1=0$，则是一个水平线
  - 如果$\lambda_1<0$，则是一个两翼向下的抛物线

类似的，我们可以变化任意变量$y_i$，然后延那个方向看$j^2_0f(y)$随$\lambda_i$的变化情况。

如果我们让$y$延某些不与坐标轴平等的方向变化呢？比如，我们可能让$y$延方向$(a_1,\cdots, a_n)$变化。这意味着，我们使用某个接近0的数$t$，考虑其乘积$y=t\cdot(a_1,\cdots,a_n)=(ta_1,\cdots,ta_n)$。然后得到 

$$
\begin{array}{rcl}
j^2_0f(y) &=& f(0) + \sum_{i=1}^n\lambda_i(ta_i)^2 \\
&=& f(0) + t^2\sum_{i=1}^na_i^2\lambda_i
\end{array}
$$

所以，我们再次获得一个抛物线状的图，其形状为"两翼向上"，"两翼向下"，或一条水平线，取决于$t^2$的系数是否为正/负/0。这三种情况下会发生什么呢？并没有清楚的答案，我们清楚的只有如下几条

  - 如果所有的$\lambda_i>0$，则对所有的$(a_1,\cdots,a_n)$有$\sum_{i=1}^na_i^2\lambda_i>0$
  - 如果所有的$\lambda_i<0$，则对所有的$(a_1,\cdots,a_n)$有$\sum_{i=1}^na_i^2\lambda_i<0$

在第一种情况中，我们可以推断0是$f$的局部最小点，因为$f$在0附近接近泰勒多项式，而该多项式具有此性质。类似的，第二种情况表示0是$f$的局部最大点。

如果上述情况都没有发生呢? 是否就可以和单变量一样说不足以说明是最大还是最小呢？

再一次，答案不是那么简单，因为对于一些多变量函数而言，可能一些方向是局部最小，而另外一些方向是局部最大，这种情况是不会发生在单变量函数上的，因为最坏的情形也只不过是缩点(flex)，如$f(x)=x^3$在0处。$Hf(0)$可能在某个方向上$\lambda_i>0$，而在另外一个方向上$\lambda_j<0$，因此，我们只改变$y_i$时，$f$在0处延此方向最小，而只改变$y_j$时，$f$在0处延此方向最大。这样的关键点称为鞍点。

当某个$\lambda_i=0$时，说明二阶泰勒多项式不中心预测$f$延这个方向的行为，需要考虑更好的近似(与1维情形类似)。
