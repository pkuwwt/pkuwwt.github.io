---
layout: blog
comments: true
tags: geometry programming python
title: 平面三角形求交测试(Planar Triangles Intersection)
---

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
def point_in_triangle2_v1(A,B,C,P):
    '''
    http://www.blackpawn.com/texts/pointinpoly/default.html
    '''
    v0 = [C[0]-A[0], C[1]-A[1]]
    v1 = [B[0]-A[0], B[1]-A[1]]
    v2 = [P[0]-A[0], P[1]-A[1]]
    dot = lambda u,v: u[0]*v[0]+u[1]*v[1]
    dot00 = dot(v0,v0)
    dot01 = dot(v0,v1)
    dot02 = dot(v0,v2)
    dot11 = dot(v1,v1)
    dot12 = dot(v1,v2)
    d = (dot00*dot11-dot01*dot01)
    u = (dot11*dot02-dot01*dot12)
    v = (dot00*dot12-dot01*dot02)
    if d<0:
        u,v,d = -u,-v,-d
    return u>=0 and v>=0 and (u+v) <= d
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

