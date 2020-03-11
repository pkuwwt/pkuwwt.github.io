---
layout: blog
comments: true
d3: true
title: 两个平面三角形的相交测试
---


## 平面三角形求交

下面给出两个平面三角形的求交测试。测试过程分两步，第一步检测两个三角形边与边之间是否相交(9次)，第二步检测一个三角形是否完全在一个三角形内部。


## 线段相交
检测线段是否相交是一个简单的解析几何问题。设第一条线段为AB, 起始坐标分别为$$(x_1,y_1),(x_2,y_2)$$，第二线段为CD，起始坐标分别为$$(x_3,y_3),(x_4,y_4)$$，交点为$E$。令$$AE=\lambda_1AB, CE=\lambda_2CD$$。则有

$$
\begin{array}{rcl}
A + \lambda_1(B-A) &=& C+\lambda_2(D-C)\\
x_1 + \lambda_1(x_2-x_1) &=& x_3 + \lambda_2(x_4-x_3) \\
y_1 + \lambda_1(y_2-y_1) &=& y_3 + \lambda_2(y_4-y_3) 
\end{array}
$$

因此，可以求得两个系数

$$
\begin{array}{rcl}
\lambda_1 &=& \frac{(x_4-x_3)(y_1-y_3)-(y_4-y_3)(x_1-x_3)}{(y_4-y_3)(x_2-x_1)-(x_4-x_3)(y_2-y_1)}\\
\lambda_2 &=& \frac{(x_2-x_1)(y_1-y_3)-(y_2-y_1)(x_1-x_3)}{(y_4-y_3)(x_2-x_1)-(x_4-x_3)(y_2-y_1)}
\end{array}
$$

只需要求$$0\le\lambda_1,\lambda_2\le1$$即可。具体计算时，并不需要真正地把系数求出来，只需要计算出分子分母三个数，然后，比较符号和大小即可。如果分母为0，说明两条线段平行，如果分子为0，表明两线段交于某一端点。此算法中主要涉及到6次乘法和若干次加法。python代码如下

{% highlight python %}
def line_intersect2(v1,v2,v3,v4):
    '''
    judge if line (v1,v2) intersects with line(v3,v4)
    '''
    d = (v4[1]-v3[1])*(v2[0]-v1[0])-(v4[0]-v3[0])*(v2[1]-v1[1])
    u = (v4[0]-v3[0])*(v1[1]-v3[1])-(v4[1]-v3[1])*(v1[0]-v3[0])
    v = (v2[0]-v1[0])*(v1[1]-v3[1])-(v2[1]-v1[1])*(v1[0]-v3[0])
    if d<0:
        u,v,d= -u,-v,-d
    return (0<=u<=d) and (0<=v<=d)
{% endhighlight %}

## 三角形内部判定
判别点P是否在三角形ABC内部，最直观的想法是绕三角形逆时针旋转时，判断此点是否在三角形所有边的左侧即可。但这个方法计算量较大，更好的办法是使用重心坐标系(实际上新坐标系原点不在三角形重心上)。具体而言，以A为坐标原点，AC和AB分别坐标系的两个轴(这不是直角坐标系)，只要它们不重合，就可以为空间中任意一点指定一个坐标。在AC轴上的0坐标对应着A点，1坐标对应着C点。同理，AB轴上0对应A，1对应B。另一方面，两个坐标值之和如果都大于等于0，且和小于1，则此点位于三角形内部(或边上)。

那么，现在的问题就变成了，如何求重心坐标。它实际上是将矢量AP分解为平行于AB和AC的两个矢量。下面是用D3写的一个演示图。

<div id="chart1">
</div>
<script>
var dataset = [5,10,15,20,25];
var w = 300, h=150;
var A={x:100,y:40,t:"A"}, B={x:200,y:40,t:"B"}, C={x:150,y:120,t:"C"};
var P = {x:100,y:100,t:"P"};
var svg = d3.select("#chart1")
.append("svg:svg")
.attr("width",w)
.attr("height",h);
svg.append("svg:defs").selectAll("marker")
.data(["suit", "licensing", "resolved"])
.enter().append("svg:marker")
.attr("id", String)
.attr("viewBox", "0 -5 10 10")
.attr("refX", 8)
.attr("refY", 0)
.attr("markerWidth", 6)
.attr("markerHeight", 6)
.attr("orient", "auto")
.append("svg:path")
.attr("d", "M0,-5L10,0L0,5");
var lineFunc = d3.svg.line()
.x(function(d) { return d.x; })
.y(function(d) { return d.y; })
.interpolate("linear");
var line = svg.append("path")
.attr("d", lineFunc([A,B,C,A]))
.attr("stroke", "blue")
.attr("stroke-width", 1)
.attr("fill", "none");
var cross = function(u,v) {
return u.x*v.y-u.y*v.x;
};
var dot = function(u,v) {
return u.x*v.x+u.y*v.y;
}
var minus = function(u,v) {
return {x:u.x-v.x,y:u.y-v.y};
}
var decomp = function(A,B,C,P) {
var v0 = minus(C,A);
var v1 = minus(B,A);
var v2 = minus(P,A);
var dot00 = dot(v0,v0);
var dot01 = dot(v0,v1);
var dot02 = dot(v0,v2);
var dot11 = dot(v1,v1);
var dot12 = dot(v1,v2);
var d = (dot00*dot11-dot01*dot01);
var u = (dot11*dot02-dot01*dot12);
var v = (dot00*dot12-dot01*dot02);
return {x:u/d,y:v/d};
}
var scale = function(A,B,u) {
return {x:A.x+u*(B.x-A.x), y:A.y+u*(B.y-A.y)};
}
svg.selectAll("text")
.data([A,B,C])
.enter()
.append("text")
.attr("x", function(d) {return d.x;})
.attr("y", function(d) {return d.y;})
.text(function(d) { return d.t;})
;
var labelP = svg.append("text")
.attr("x", P.x)
.attr("y", P.y)
.text("P");
var tmp = decomp(A,B,C,P);
var u=tmp.x,v=tmp.y;
var labelu = svg.append("text")
.attr("x", 0)
.attr("y", 15)
.text("u: " + u);
var labelv = svg.append("text")
.attr("x", 0)
.attr("y", 30)
.text("v: " + v);
var line2 = svg.append("path")
.attr("d", lineFunc([A,P]))
.attr("stroke", "red")
.attr("stroke-width", 1)
.attr("fill", "none")
.attr("marker-end","url(#licensing)");
var line3 = svg.append("path")
.attr("d", lineFunc([A,scale(A,C,u)]))
.attr("stroke", "red")
.attr("stroke-width", 1)
.attr("fill", "none")
.attr("marker-end", "url(#licensing)");
var line4 = svg.append("path")
.attr("d", lineFunc([A,scale(A,B,v)]))
.attr("stroke", "red")
.attr("stroke-width", 1)
.attr("fill", "none")
.attr("marker-end", "url(#licensing)");
var dashline = svg.append("path")
.attr("d", lineFunc([scale(A,B,v), P, scale(A,C,u)]))
.attr("stroke", "red")
.attr("stroke-dasharray", "5,5")
.attr("stroke-width", 1)
.attr("fill", "none");
svg.on("mousemove", function(){
P = d3.mouse(this);
P = {x:P[0],y:P[1]};
tmp = decomp(A,B,C,P);
u=tmp.x,v=tmp.y;
line2.attr("d", lineFunc([A,P]));
line3.attr("d", lineFunc([A,scale(A,C,u)]));
line4.attr("d", lineFunc([A,scale(A,B,v)]));
dashline.attr("d", lineFunc([scale(A,B,v), P, scale(A,C,u)]));
labelP.attr("x",P.x).attr("y",P.y);
labelu.text("u: " + u);
labelv.text("v: " + v);
if(u>=0 && v>=0 && u+v<=1) {
labelu.attr("fill","red");
labelv.attr("fill","red");
}
else {
labelu.attr("fill","black");
labelv.attr("fill","black");
}
}
);
</script>

令$$AP=v AB + u AC$$，则构成一个线性方程组

$$
\begin{array}{rcl}
x_P-x_A &=& v(x_B-x_A) + u(x_C-x_A) \\
y_P-y_A &=& v(y_B-y_A) + u(y_C-y_A) 
\end{array}
$$

即

$$
\begin{bmatrix}x_B-x_A & x_C-x_A \\ y_B-y_A & y_C-y_A\end{bmatrix} 
\begin{bmatrix}v \\ u\end{bmatrix}
= 
\begin{bmatrix}x_P-x_A \\ y_P-y_A\end{bmatrix}
$$

结果为

$$
\begin{array}{rcl}
\begin{bmatrix}v \\ u\end{bmatrix} &=& \frac{1}{(x_B-x_A)(y_C-y_A)-(x_C-x_A)(y_B-y_A)}
\begin{bmatrix}y_C-y_A& -(x_C-x_A) \\-(y_B-y_A)  &x_B-x_A  \end{bmatrix} 
\begin{bmatrix}x_P-x_A \\ y_P-y_A\end{bmatrix} \\
	&=& \frac{1}{(x_B-x_A)(y_C-y_A)-(x_C-x_A)(y_B-y_A)}
\begin{bmatrix}(y_C-y_A)(x_P-x_A)-(x_C-x_A)(y_P-y_A) \\-(y_B-y_A)(x_P-x_A)+(x_B-x_A)(y_P-y_A)  \end{bmatrix} 
\end{array}
$$

此算法同样只涉及到6次乘法和若干次加法。python代码如下

{% highlight python %}
def point_in_triangle2(A,B,C,P):
    v0 = [C[0]-A[0], C[1]-A[1]]
    v1 = [B[0]-A[0], B[1]-A[1]]
    v2 = [P[0]-A[0], P[1]-A[1]]
    cross = lambda u,v: u[0]*v[1]-u[1]*v[0]
    u = cross(v2,v0)
    v = cross(v1,v2)
    d = cross(v1,v0)
    if d<0:
        u,v,d = -u,-v,-d
    return u>=0 and v>=0 and (u+v) <= d
{% endhighlight %}

最后总的三角形相交测试代码为
{% highlight python %}
def tri_intersect2(t1, t2):
    '''
    judge if two triangles in a plane intersect 
    '''
    if line_intersect2(t1[0],t1[1],t2[0],t2[1]): return True
    if line_intersect2(t1[0],t1[1],t2[0],t2[2]): return True
    if line_intersect2(t1[0],t1[1],t2[1],t2[2]): return True
    if line_intersect2(t1[0],t1[2],t2[0],t2[1]): return True
    if line_intersect2(t1[0],t1[2],t2[0],t2[2]): return True
    if line_intersect2(t1[0],t1[2],t2[1],t2[2]): return True
    if line_intersect2(t1[1],t1[2],t2[0],t2[1]): return True
    if line_intersect2(t1[1],t1[2],t2[0],t2[2]): return True
    if line_intersect2(t1[1],t1[2],t2[1],t2[2]): return True
    inTri = True 
    inTri = inTri and point_in_triangle2(t1[0],t1[1],t1[2], t2[0])
    inTri = inTri and point_in_triangle2(t1[0],t1[1],t1[2], t2[1])
    inTri = inTri and point_in_triangle2(t1[0],t1[1],t1[2], t2[2])
    if inTri == True: return True
    inTri = True
    inTri = inTri and point_in_triangle2(t2[0],t2[1],t2[2], t1[0])
    inTri = inTri and point_in_triangle2(t2[0],t2[1],t2[2], t1[1])
    inTri = inTri and point_in_triangle2(t2[0],t2[1],t2[2], t1[2])
    if inTri == True: return True
    return False
{% endhighlight %}

最后给出一个测试程序，程序中有两个可拖动的三角形，如果三角形相交，则会在标题栏上显示'intersect'，否则显示'non-intersect'。
{% highlight python %}
#!/usr/bin/python
import numpy as np
from numpy.random import random
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon

def line_intersect2(v1,v2,v3,v4):
    '''
    judge if line (v1,v2) intersects with line(v3,v4)
    http://thirdpartyninjas.com/blog/2008/10/07/line-segment-intersection/
    '''
    v12 = [v2[0]-v1[0],(v2[1]-v1[1])]
    v34 = [v4[0]-v3[0],(v4[1]-v3[1])]
    v31 = [v1[0]-v3[0],(v1[1]-v3[1])]
    cross = lambda u,v: u[0]*v[1]-u[1]*v[0]
    d = cross(v12,v34)
    u = cross(v34,v31)
    v = cross(v12,v31)
    if d<0:
        u,v,d= -u,-v,-d
    return (0<=u<=d) and (0<=v<=d)

def point_in_triangle2(A,B,C,P):
    v0 = [C[0]-A[0], C[1]-A[1]]
    v1 = [B[0]-A[0], B[1]-A[1]]
    v2 = [P[0]-A[0], P[1]-A[1]]
    cross = lambda u,v: u[0]*v[1]-u[1]*v[0]
    u = cross(v2,v0)
    v = cross(v1,v2)
    d = cross(v1,v0)
    if d<0:
        u,v,d = -u,-v,-d
    return u>=0 and v>=0 and (u+v) <= d


def tri_intersect2(t1, t2):
    '''
    judge if two triangles in a plane intersect 

    e.g.
        tri_intersect2([(0,0),(1,0),(0,1)], [(1,0),(2,0),(1,1)])

    '''
    if line_intersect2(t1[0],t1[1],t2[0],t2[1]): return True
    if line_intersect2(t1[0],t1[1],t2[0],t2[2]): return True
    if line_intersect2(t1[0],t1[1],t2[1],t2[2]): return True
    if line_intersect2(t1[0],t1[2],t2[0],t2[1]): return True
    if line_intersect2(t1[0],t1[2],t2[0],t2[2]): return True
    if line_intersect2(t1[0],t1[2],t2[1],t2[2]): return True
    if line_intersect2(t1[1],t1[2],t2[0],t2[1]): return True
    if line_intersect2(t1[1],t1[2],t2[0],t2[2]): return True
    if line_intersect2(t1[1],t1[2],t2[1],t2[2]): return True
    inTri = True 
    inTri = inTri and point_in_triangle2(t1[0],t1[1],t1[2], t2[0])
    inTri = inTri and point_in_triangle2(t1[0],t1[1],t1[2], t2[1])
    inTri = inTri and point_in_triangle2(t1[0],t1[1],t1[2], t2[2])
    if inTri == True: return True
    inTri = True
    inTri = inTri and point_in_triangle2(t2[0],t2[1],t2[2], t1[0])
    inTri = inTri and point_in_triangle2(t2[0],t2[1],t2[2], t1[1])
    inTri = inTri and point_in_triangle2(t2[0],t2[1],t2[2], t1[2])
    if inTri == True: return True
    return False

class DraggableTriangles:
    def __init__(self,tri):
        self.tri = tri
        self.center0 = tri.get_xy().mean(0)
        self.offset = np.zeros((2,))
        self.press = None
    def connect(self):
        'connect to all events we need'
        self.cidpress = self.tri.figure.canvas.mpl_connect(
                'button_press_event', self.on_press)
        self.cidrelease = self.tri.figure.canvas.mpl_connect(
                'button_release_event', self.on_release)
        self.cidmotion = self.tri.figure.canvas.mpl_connect(
                'motion_notify_event', self.on_motion)
    def on_press(self,event):
        if event.inaxes != self.tri.axes: return
        contains, attrd = self.tri.contains(event)
        if not contains: return
        self.press = event.xdata,event.ydata
    def on_motion(self,event):
        if self.press is None: return
        if event.inaxes != self.tri.axes: return
        xpress, ypress = self.press
        dx = event.xdata - xpress + self.offset[0]
        dy = event.ydata - ypress + self.offset[1]
        trans = mpl.transforms.Affine2D().translate(dx,dy)+self.tri.axes.transData
        self.tri.set_transform(trans)
        self.tri.figure.canvas.draw()
    def on_release(self,event):
        if self.press is None: return
        xpress, ypress = self.press
        dx = event.xdata - xpress + self.offset[0]
        dy = event.ydata - ypress + self.offset[1]
        self.offset = (dx,dy)
        self.press = None
        self.tri.figure.canvas.draw()
    def disconnect(self):
        self.tri.figure.canvas.mpl_disconnect(self.cidpress)
        self.tri.figure.canvas.mpl_disconnect(self.cidrelease)
        self.tri.figure.canvas.mpl_disconnect(self.cidmotion)

fig = plt.figure()
ax = fig.add_subplot(111)
dtris = []
tris = [Polygon(random((3,2))*4) for i in range(2)]

def on_motion(event):
    t1 = tris[0].get_verts()
    t2 = tris[1].get_verts()
    if tri_intersect2(t1[0:3],t2[0:3]):
        ax.set_title('intersect')
    else:
        ax.set_title('non-intersect')

fig.canvas.mpl_connect('motion_notify_event', on_motion)


for tri in tris:
    tri.set_color((random(),random(),random()))
    ax.add_patch(tri)
    dtri = DraggableTriangles(tri)
    dtri.connect()
    dtris.append(dtri)

ax.autoscale_view()
plt.show()
{% endhighlight %}

## 参考文献
  - http://thirdpartyninjas.com/blog/2008/10/07/line-segment-intersection/
  - http://www.blackpawn.com/texts/pointinpoly/default.html

注意，本文中的三角形内部判定算法要优于参考文献中的算法，不过两者的基本原理是一致的。

