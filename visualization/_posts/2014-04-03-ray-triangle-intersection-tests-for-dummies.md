---
layout: blog
comments: true
title: 光线-三角形求交测试算法[译]
---


## 前言
光线-三角形测试算法有很多。这此，我将描述几种最有趣的，因为我以为不存在"终极"的光线三角求交方法，方法的选择取决于应用类型。测试通过(击中)的方法更快。否则(早期拒绝)会更慢。一些方法占用内存更大，尽可能地预计算，在没有碰撞缓存的场景(比如，没有大三角和空间划分的场景)中，它速度会很快，其它方法则内存占用小，也没有预计算。预计算通常会很重要，所以，我会讲得更多。预计算有两种，第一种是逐帧预计算(整个场景的预计算，考虑了每个三形，只需要更新每一帧变化了的三角形)。另外一种是光线束预计算(具有相同源点的光线的预计算，比如，摄像机首次击中光线或阴影光线)。第二种只适用于少量三角形的实时光线追踪，因为预计算的数据量可能很大，以致于不得不避免缓存击中(一个缓存击中通常比求交计算消耗更多)，如果有一些大三角和好的空间划分，我们常常需要在首次测试和阴影光线测试中在一个三角上测试很多个像素，所以缓存更多更有利。好的做法是，将预计算信息缓存起来(比如存于阴影缓存中)并且只对少数几个三角形预计算，或只在需要时预计算(只更新首次击中的三角形)。大量预计算可让算法更快，但是过多预计算也并不一定好。

每种算法都需要以下两样东西:

  - 三角形的3个顶点(v1,v2,v3，如果是正面朝外则为逆时针顺序，这种约定对有些算法有用)
  - 光线。通常用参数形式描述$$R=r_o+t*r_d$$，其中$$r_o$$是光源，$$r_d$$是光线方向矢量。


几乎每一种方法都使用三角平面的重心坐标(u,v)来计算交点，即

$$
i_p = (1-u-v)v_1 + u*v_2 + v*v_3 = v_1 + (v_2-v_1)*u + (v_3-v_1)*v
$$

此点位于三角内部，如果$$0\le u,v$$且$$u+v\le 1$$。此点在三角边上，如果$$u,v=0$$或$$u+v=1$$。当我们对顶点上的属性插值时，u,v权重是很有用的。比如，纹理坐标，表面颜色值(Gouraud shading)等。。。

## Moller-Trumbore方法(Journal of Graphic Tools, 1997)
此法出现在"Real time rendering"一书中，此方法就是以书的两个作者的名称命名的。这是最好的方法之一，并且也很流行。

整个方法是基于找到一个变换，将矢量从世界坐标变换到由两个三角边加上精心选择的另外一个矢量构成的基底的空间中。具体原理参考任何一本线性代数课本。算法过程如下:

  - 将$$v_1,v_2,v_3,r_o$$同时变换，使得$$v_1=(0,0,0)$$。
  - 构造变换矩阵，将其应用于$$r_o$$。此矩阵$$T_M$$找起来相当容易，因为它满足$$M*T_M=I$$，其中，基底向量为$$v_1-v_2,v_1-v_3,-r_d$$(后面会解释为何这样选择)，它们构成$M$的列。这意味着将基底变换到(1,0,0),(0,1,0),(0,0,1)。因此$$T_M=inv(M)$$，将其应用到$$r_o$$得到求交平面上的u,v坐标和作为光线参数的t(这也是为什么选择$$-r_d$$作为第三个基底的原因)。

注意，矩阵求逆要求矩阵是不平凡的，即3个基底不在一个平面上，因此光线不能与求交平面平行或接近平行。

目前为止，算法涉及到矩阵求逆，行列式，矩阵乘法等运算，因此还是比较复杂。通过添加一些优化和早期拒绝测试，可以进一步简化和更为高效。注意，此算法内存占用量已经是最小的了，因为它只需要最少的三角形的信息，你也无需计算法向量等其它东西。接下来，我会使用Crammer规则来计算矩阵逆和简化公式(来自于Moller和Haines在DrDobb上的期刊文章)。

记$$e_1=v_2-v_1,e_2=v_3-v_1$$(即两条边)，$$s=r_o-v_1$$(光源平移)，并且已知$$det(a,b,c)=(a\times b)\cdot c = -(a\times c)\cdot b = - (c\times b)\cdot a$$，因此有

$$
\begin{bmatrix}t\\u\\v \end{bmatrix} = \frac{1}{det(-d,e_1,e_2)} * 
\begin{bmatrix}det(s,e_1,e_2)\\det(-d,s,e_2)\\det(-d,e_1,s)\end{bmatrix}
$$

也就是说

$$
\begin{bmatrix}t\\u\\v \end{bmatrix} = \frac{1}{(d\times e_2)e_1} * 
\begin{bmatrix}(s\times e_1)e_2)\\(d\times e_2)s)\\(s\times e_1)d)\end{bmatrix}
$$

算法的代码如下(u,v是重心坐标，t是光线直线方程的参数)

{% highlight c %}
MollerTrumbore_IntersectRayTri(vec3d r_o,vec3d r_d,vec3d v1,vec3d v2,vec3d v3)
returns (float u,float v,float t,bool intersect,bool frontfacing)
{ vec3d e2=v3-v1;       // second edge
	vec3d e1=v2-v1;       // first edge
	vec3d r=cross(d,e2);  // (d X e2) is used two times in the formula
	// so we store it in an appropriate vector
	vec3d s=r_o-v1;       // translated ray origin
	vec3d a=dot(e1,r);    // a=(d X e2)*e1
	real f=1/a;           // slow division*
	vec3d q=cross(s,e1);
	real u=dot(s,r);
	bool frontfacing=true;
	if (a>eps)      // eps is the machine fpu epsilon (precision), 
                   	// or a very small number :)
	{ // Front facing triangle...
		if (u<0)||(u>a) return 0,0,0,false,frontfacing;
		vec3d v=dot(d,q);
		if (v<0)||(u+v>a) return 0,0,0,false,frontfacing;
	}
	else if (a<-eps)
	{ // Back facing triangle...
		frontfacing=false;
		if (u>0)||(u<a) return 0,0,0,false,frontfacing;
		vec3d v=dot(d,q);
		if (v>0)||(u+v<a) return 0,0,0,false,frontfacing;
	} else return 0,0,0,false,false; // Ray parallel to triangle plane
	real t=f*dot(e2,q);
	u=u*f; v=v*f;
	return u,v,t,true,frontfacing;
}
{% endhighlight %}

*) 我们希望浮点运算(fpu)可以并行(多管线)，因而可以在代码结束前完成。如果这样的并行没有实现，则除法`1/a`最好置于每次早期拒绝测试之后。如果我们确定大部分时候光线都会击中三角形，则这个优化也是没有必要的(比如，如果我们使用粒度很细的划分方法，或多层次空间划分)。

此算法的优点在于:

  - 内存占用少
  - 没有那么多早期拒绝测试(第一次前你已经做了两次叉乘和点乘)
  - 如果有必要，可以做背面剔除
  - 它甚至可以在混合浮点/定点操作机器上实现，来充分利用某些CPU的fpu/alu的并行机制(比如intel pentium系列)，即在fpu上计算除尘，而在alu上同时做定点运算。

缺点是:

  - 没有多少预计算


## Dan Sunday方法

Dan Sunday提出的方法与Moller的很类似，只不过计算交点的重点坐标的方式有所不同。他使用的是Hill的垂直点积的3维扩展：对一个法向量为n的平面$$P$$，以及平面内的任何矢量a，我们有$$perp(a) = n\times a$$，这是平面内的另外一个矢量，它与a和n都垂直。此算子是线性的，即任意标量x,y和P内的矢量a,b, 我们有perp(xa+yb) = x*perp(a)+y*perp(b)。如果P是xy平面，n=(0,0,1)，则这就是Hill的2维垂直点积。现在，我们使用这个垂直点积来解决光线-平面求交问题。平面的参数方程是$$P(u,v)=v_1+u*e_1+v*e_2$$, 其中u,v是标量，而$$e_1=v_2-v_1,e_2=v_3-v_1$$。你应该已经意识到了，这就是在计算重心坐标。令i为交点，则有

$$
i-v_1 = ue_1 + ve_2
$$

如果在两边同时点乘$$perp(e_2)$$，并用w取代$$i-v_1$$，则有

$$
w\cdot perp(e_2) = ue_1\cdot perp(e_2) + ve_2 perp(e_2) = ue_1\cdot perp(e_2)
$$

从而，我们可以得到交点的u坐标。同理，如果点乘$$perp(e_1)$$，我们可以得到v。因而，我们有

$$
\begin{array}{rcl}
u &=& \frac{w\cdot perp(e_2)}{e_1\cdot perp(e_2)} = \frac{w\cdot(n\times e_2)}{e_1\cdot(n\times e_2)} \\
v &=& \frac{w\cdot perp(e_1)}{e_2\cdot perp(e_1)} = \frac{w\cdot(n\times e_1)}{e_2\cdot(n\times e_1)}
\end{array}
$$

注意，如果三角形退化了(面积为0)，而分母仍然非零，所以此法仍然适用(当然数值稳定性问题仍然是存在的)。我们进一步优化此算法，使用公式$$(a\times b)\times c = (a\cdot c) b - (b\cdot c) a$$，得到$$perp(e_1) = n\times e_1 = (e_1\times e_2) \times e_1 = (e_1\cdot e_1)e_2-(e_1\cdot e_2)e_1$$，同理$$perp(e_2) = (e_1\cdot e_2)e_2 - (e_2\cdot e_2)e_1$$, 因此有

$$
\begin{array}{rcl}
u &=& \frac{(e_1\cdot e_2)(w\cdot e_2) - |e_2|^2(w\cdot e_1)}{(e_1\cdot e_2)^2 - |e_2|^2|e_1|^2} \\
v &=& \frac{|e_1|^2(w\cdot e_2) -(e_1\cdot e_2)(w\cdot e_1)}{|e_1|^2|e_2|^2 -(e_1\cdot e_2)^2}
\end{array}
$$

上式中只包含点乘而没有叉乘，但是仍然比Moller算法慢。但是，其中只有少量与w有关，也就是说我们可以预计算很多东西。所以，此算法经过预计算之后，只剩下两次点乘，两次标量乘法，和一次减法。而参数t的计算方法是

$$
t = \frac{n\cdot(v_1-r_o)}{n\cdot r_d}
$$

同样，如果$$n\cdot r_d=0$$，则光线与平面平行，没有交点。

此算法的优点是

  - 预计算很多(如果缓存未命中不是问题，则速度很快)，预计算可调

缺点是

  - 没有那么多早期拒绝测试(和M-T方法类似)
  - 在基础版本中比M-T慢
  - 在预计算版本中存储不高效(这意味着在复杂网格上会慢)

## Badouel算法(Graphic Gems, 1990)

据我所知，这是第一个使用重心坐标的算法，和M-T算法同样有名(但是更慢:P)。它是将重心坐标分解为三角形的点($$p-v_1 1= u(v_2-v_1) + v(v_3-v_1)$$)，从而得到包含3个方程的方程组，其中p是交点。

$$
\begin{array}{rcl}
p.x - v_1.x &=& u(v_2.x - v_1.x) + v(v_3.x-v_1.x) \\
p.y - v_1.y &=& u(v_2.y - v_1.y) + v(v_3.y-v_1.y) \\
p.z - v_1.z &=& u(v_2.z - v_1.z) + v(v_3.z-v_1.z) 
\end{array}
$$

然后，将三角形投影到xy,yz或yz平面中的一个上，以消除一个坐标，从而得到

$$
\begin{array}{rcl}
p.s - v_1.s &=& u(v_2.s - v_1.s) + v(v_3.s-v_1.s) \\
p.t - v_1.t &=& u(v_2.t - v_1.t) + v(v_3.t-v_1.t)
\end{array}
$$

其中，s,t是剩余的两个坐标。从而，我们可以解出u,v来。消除的那个坐标是在法向量分量最大的那个。此算法非常直接，但是对于很复杂网格，比M-T算法要慢，因为我们必须存储三角形法向量，或执行叉乘而算它。另外，分支运算更多(在现代CPU上比较耗时)，而且还多两次除法，同样没有很多早期拒绝测试。

{% highlight c %}
Badouel_IntersectRayTri(vec3d r_o,vec3d r_d,vec3d v1,vec3d v2,vec3d v3)
// No precalculated normal version
returns (vec3d ip,u,float v,float t,bool intersect)
// We return ip too because the algorithm computes it internally,
// so it's less expensive than recomputing it via the t parameter
{ // Compute the triangle normal vector
	vec3d norm=cross(v1,v2);
	float tmp=dot(norm,r_d);

	if (abs(tmp)<eps) return (0,0,0),0,0,0,false; // ray is parallel to tri.plane
	float t=dot(norm,v1-r_o)/tmp;

	// Compute the two coordinates that we'll use
	int i1,i2,i3;
	if (norm[1]>norm[2])
		if (norm[1]>norm[3]) { i1=2; i2=3; }
		else { i1=1; i2=2; }
	else
		if (norm[2]<norm[3]) { i1=1; i2=2; }
		else { i1=1; i2=3; }
	u3=6-i1-i2;

	// Compute the intersection point (only the two needed coordinates)
	vec3d ip;
	ip[i1]=r_o[i1]+r_d[i1]*t;
	ip[i2]=r_o[i2]+r_d[i2]*t;

	// Tranlsate everything
	float u0 =ip1-v1[i1];
	float v0 =ip2-v1[i2];
	float u1 =v2[i1]-v1[i1];
	float v1 =v2[i1]-v1[i2];
	float u2 =v3[i1]-v1[i1];
	float v2 =v3[i1]-v1[i2];

	// Do the barycentric stuff... 
	if (abs(u1)<eps) // uncommon
	{ v=u0/u2;
		if(v<0||v>1) return (0,0,0),0,0,0,false;
		u=(v0-v*v2)/v1;
	}
	else 
	{ v=(v0*u1-u0*v1)/(v2*u1-u2*v1);
		if(v<0||v>1) return (0,0,0),0,0,0,false;
		u=(u0-v*u2)/u1;
	}
	if(u<0||(u+v)>1) return (0,0,0),0,0,0,false;
	// compute the missing coordinate of the intersection point
	ip[i3]=r_o[i3]+r_d[i3]*t;
	return ip,u,v,t,true;
}
{% endhighlight %}

你应该注意到此方法只不过是M-T算法的2维版本(事实上M-T是此方法的3维版本)。我们平移三角形的投影，然后得到的方程的解可视为一个矩阵向量乘法，即同样是线性变换，只不过是2维的。


优点:

  - 如果预计算法向量和/或投影面，效率不错。
  - 早期拒绝

缺点:

  - 在复杂网格上比M-T法慢，而在简单网格上也不会更快
  - 没有很多早期拒绝测试


## Segura-Feito方法和S-F方法的修改版


此方法使用一个线段，而非光线。此线段可由两个起止点表示: $$r_s,r_e$$。三角形顶点应该逆时针排列(和M-T一样)。此外，此方法只测试线段是否与三角形相交，而没有求出相交点本身。交点必须由标准的光线-平面相交方法来计算，此计算可以置于线段-三角形相交测试之前或之后。这与M-T中的早期除法问题类似。如果在之前执行，我们容易计算出$$r_s$$和$$r_e$$: 如果t是光线参数，则

$$
\begin{array}{rcl}
tmp &=& t*r_d \\
r_s &=& r_o + tmp - r_d \\
r_e &=& r_o + tmp + r_d 
\end{array}
$$

否则，我们就只能令$$r_s = r_o, r_e = r_o + farvalue * r_d$$，其中farvalue是远裁剪距离。此线段-三角求交测试用到如下定理(Segura,1998):

令ABC是3维空间中的三角形，而P,Q在3维空间中确定一个线段，它们位于ABC决定的平面的两侧，且满足四面体PABC的方向为正(即PABC的有向体积为正，表示它的朝向为正)。则线段PQ与三角形相交当且仅当QAPB,QCBP,QACP的符号都不小于0。这是因为，PQ与ABC相交当且仅当Q被包含于PA,PB,PC构成的锥形区域中，即从Q的角度看，APB,BCP,CAP都是顺时针三角形，因此四面体QAPB, QCBP和QACP都具有正的方向。如果其中一个符号为0，则Q与ABP, BCP, CAP中的一个三角形共面，即相交点在边界上。如果两个符号为0，则交点为其中一个顶点。所以此算法的伪码为

{% highlight c %}
SeguraFeito_TestSegmTri(vec3d r_s,vec3d r_e,vec3d v1,vec3d v2,vec3d v3)
returns (bool intersect)
{ int i=area_sign(r_s,r_e,v1,v3);
	if i<=0 return false;
	i=area_sign(r_s,r_e,v2,v3);
	if i<=0 return false;
	i=area_sign(r_s,r_e,v1,v2);
	if i<=0 return false;

	return true;
}

SeguraFeito_IntersectRayTri(vec3d r_o,vec3d r_d,vec3d v1,vec3d v2,vec3d v3)
returns (vec3d ip,float t,bool intersect)
{ vec3d n=cross(v1,v2); // Compute the normal vector
	float t=(dot(n,(v1-r_o)))/dot(n,r_d); // get the parameter t for the 
	// ray plane intersection
	vec3d tmp=r_o+t*r_d;
	vec3d r_s=tmp-r_d;
	vec3d r_e=tmp+r_d;
	if SeguraFeito_TestSegmTri(r_s,r_e,v1,v2,v3) return(tmp,t,true);
	else return(tmp,t,false);
}
{% endhighlight %}

那么，如何计算符号呢? 我们知道，如果A是一个$$n\times n$$实矩阵，则det(A)可理解为由列向量张成的平行多面体的有向体积。这里的"有向"指的是列向量的顺序。如果与标准排序一致，则为正，否则为负。此平行多面体中的点是这些列向量的线性组合，系数位于[0,1]中。

Segura-Feito文章中的函数area\_sign是由Yamaguchi(1990)提出的，用来计算4x4行列式。此工作的目标是解决高精度几何问题，并使用一个精度可变的矩阵表达。所以，这里，我使用另外一种计算方式(不保证没错误)。

如果我们将我们的世界平移至rs=(0,0,0,1)(摄像机空间)，则可将4x4行列式变成3x3：

$$
\begin{array}{rcl}
ar_ea\_sign(r_s,r_e,v_1,v_2) &=& sign(v_3.z*(r_e.x*v_1.y-v_1.x*r_e.y)+v_3.y*(v_1.z*r_e.x-r_e.z*v_1.x)+ \\
		&& v_3x*(v_1.y*r_e.z-r_e.y*v_1.z))=sign(v_3\cdot(r_e \times v_1)); \\
ar_ea\_sign(r_s,r_e,v_1,v_2) &=& sign(v_2.z*(r_e.x*v_1.y-v_1.x*r_e.y)+v_2.y*(v_1.z*r_e.x-r_e.z*v_1.x)+ \\
		&& v_2x*(v_1.y*r_e.z-r_e.y*v_1.z))=sign(v_2\cdot(r_e \times v_1)); \\
ar_ea\_sign(r_s,r_e,v_2,v_3) &=& sign(v_3.z*(r_e.x*v_2.y-v_2.x*r_e.y)+v_3.y*(v_2.z*r_e.x-r_e.z*v_2.x)+ \\
		&& v_3x*(v_2.y*r_e.z-r_e.y*v_2.z))=sign(v_3\cdot(r_e \times v_2));
\end{array}
$$


你会注意到计算量与M-T是一样的(两次叉乘，和几次点乘)，但是这里不需要除法(计算交点时需要，只检测是否相交则不需要)。此符号函数可以用一个条件分支来实现，或通过剥离浮点数的符号比特。我们可以将计算进一步简化为

$$
\begin{array}{rcl}
ar_ea\_sign(r_s,r_e,v_1,v_3)&=&-ar_ea_sign(r_s,v_3,v_1,r_e)=-sign(r_e\cdot(v_3 \times v_1))=sign(r_e\cdot(v_1 \times v_3)); \\
ar_ea\_sign(r_s,r_e,v_1,v_2)&=&-ar_ea_sign(r_s,v_2,v_1,r_e)=-sign(r_e\cdot(v_2 \times v_1))=sign(r_e\cdot(v_1 \times v_2)); \\
ar_ea\_sign(r_s,r_e,v_2,v_3)&=&-ar_ea_sign(r_s,v_3,v_2,r_e)=-sign(r_e\cdot(v_3 \times v_2))=sign(r_e\cdot(v_2 \times v_3)); 
\end{array}
$$

交换矩阵中的两行或两列会变换行列式的符号。现在，我们由一次叉乘变成了两次，但是我们可以预计算，从而增加速度。现在，我们可以用几何方式来解释，如果我们使用下面的方程来表示平面

$$
N\cdot p + D = 0
$$

其中，N是平面法向，p是平面上的点，D是源点与平面的距离。因此，我们可以将$$v_1\times v_3$$, $$v_1\times v_2$$, $$v_2\times v_3$$理解为穿过原点(D=0)的3个平面的法向量，并且与每条三角边相交。所以，$$r_e\cdot(v_1\times v_3)$$只不过是检测点$$r_e$$位于平面的哪一边。如果$$r_e$$位于3个裁剪面定义的体的内部，则光线会与三角相交(这种方式也适用于多边形)。在这个解释中，你可以发现$$r_e$$可以是光线上的任意点，因此，最终，我们可以将Segura-Feito测试写成这样:

{% highlight c %}
SeguraFeito_TestSegmTri(vec3d r_o,vec3d r_d,vec3d v1,vec3d v2,vec3d v3)
returns (bool intersect)
{ 
	v1-=r_o; v2-=r_o; v3-=r_o;
	vec3d tmp=cross(r_d,v1); // we use r_d as our r_e
	int i=sign(dot(v3,tmp));
	if(i<=0) return false;
	i=sign(dot(v2,tmp);
	if(i<=0) return false;
	i=sign(dot(v3,cross(re,v2));
	if(i<=0) return false;

	return true;
}

// TestSegmTriPrecalc (idea...)
SeguraFeito_TestSegmTriPrecalc(vec3d r_o,vec3d r_d,triangle tri,frame currframe)
returns (bool intersect)
{
	if(tri.updateframe!=currframe) {
	    tri.v1xv3=cross(tri.v1-r_o,tri.v3-r_o);
	    tri.v1xv2=cross(tri.v1-r_o,tri.v2-r_o);
	    tri.v2xv3=cross(tri.v2-r_o,tri.v3-r_o);
	    tri.updateframe=currframe;
	}

	int i=sign(dot(r_d,tri.v1xv3));
	if(i<=0) return false;
	i=sign(dot(r_d,tri.v1xv2);
	if(i<=0) return false;
	i=sign(dot(r_d,tri.v2xv3);
	if(i<=0) return false;
	return true;
}
{% endhighlight %}

此方法最后一个提示。它很适用于三角条带，因为你可以缓存每条边的计算，然后用于下一个三角形(你只需要修改符号，因为指向原三角的方向是远离相邻三角形的)。知道这一点你会发现你得到一个阴影测试的光线树。是不是说光线树就适用阴影测试呢? 我不同意，因为阴影测试是一种"任意查询"(任意撞击会返回此表面点是阴影)，但是我们不应太在意是否存在快的任意撞击(通过一个小的阴影缓存已经可以足够高效)，而应该关心是否不存在，并且，我们总是在大部分时间里让物体位于光照中(完全阴影的场景是难看的)。所以我们必须使用某种形式的空间划分，这就不是本教程的主题了。

标准版本优点:

  - 或多或少与M-T等价
  - 早期拒绝
  - 应该比M-T更稳定
  - 如果我们只进行相交测试(而不求相交点)，则应比M-T更快


预计算版本优点:

  - 比M-T快很多
  - 早期拒绝
  - 应该比M-T更稳定
  - 很适于阴影光线，因为我们在阴影缓存中存储了预计算结果(每个人都应该使用阴影缓存:P)

缺点:

  - 不计算重心坐标，因此不适用于一些应用

## 高效和可靠的求交测试: 光线-三角形求交(Journal of Graphic Tools, 1998)

现在，我们将给出另一种3维到2维的投影方法。事实上，此算法或多或少是基于和S-F同样的思想，只不过是2维情况。事实上，它在S-F之前提出，只不过Badouel和M-T喜欢首先解释3维情形，理解一般情况之后理解2维投影会更容易。此方法与Badouel的相当类似，区别在于将三角形和交点投影之后。它不计算重心坐标，而是检测2维点是否位于三角形内，即检测$$det(v_1,v_2,i_p)$$, $$det(v_2,v_3,i_p)$$, $$det(v_3,v_1,i_p)$$的符号。注意，$$v_1,v_2,v_3$$的方向可以由法向量$$n=(v_2-v_1)\times(v_3-v_1)$$获得。它的作者(Martin Held)声称此算法要优于计算重心坐标的算法(Badouel)和无穷金字塔方法(修改版S-F)，但我没看出来好在哪里。不管怎样，我不认为它比M-T或S-F要好。此外，它拥有S-F所有的缺点，再加上它会在任意其它测试之前进行求交运算(类似于Badouel或Sunday)，因此在低光线击中的场合中，它会很慢。


## Plucker(Grassmann)坐标光线-三角求交

Plucker坐标是一种表达3维有向线的方法。它构成一个6维齐次空间，所谓齐次坐标，就是用n维向量表示n+1维向量，第n+1个分量变成了前面n个分量的分母。一条光线$$R(r_o,r_d)$$可以用plucker坐标$$(r_d, r_d\times r_o)$$来编码。在plucker空间中，我们可以做很多有趣的事，但是我们真正关心的是，如果有两条光线$$R_1=(U_1,V_1),R_2=(U_2,v_2)$$，且$$w=U_1\cdot V_1 + U_2\cdot V_2$$(转换内积,permutated inner product)，则如果w=0则它们相交，如果w>0则$$R_1$$看到$$R_2$$是逆时针的，如果w<0则$$R_1$$看到$$R_2$$是顺时针的。

至于如何用于三角形求交，则完全取决于你了，这应该是非常直接的。

## 结论
这些算法，最有用的应该是M-T，但是我们认为，你应该对于光线-三角形求交有更多的想法，并提出新的方法，或定制这些方法来用于你的应用。比如，你可以考虑预计算$$(v_2-v_1)/|v_2-v_1|$$和$$(v_3-v_1)/|v_3-v_1|$$。

## 参考文献

  - 原文 [Ray(/segment)-triangle intersection tests for dummies](http://hugi.scene.org/online/hugi25/hugi%2025%20-%20coding%20corner%20graphics,%20sound%20&%20synchronization%20ken%20ray-triangle%20intersection%20tests%20for%20dummies.htm)
  - 一篇论文 [ALGORITHMS TO TEST RAY-TRIANGLE INTERSECTION COMPARATIVE STUDY, Segura, 1998](http://wscg.zcu.cz/wscg2001/Papers_2001/R75.pdf)
