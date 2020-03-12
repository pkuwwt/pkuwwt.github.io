---
layout: blog
comments: true
tags: OpenGL python programming
title: Python下写OpenGL代码示例
---

类似的代码，Python明显比C要舒服一些，因为无需编译。使用PyOpenGL可以实现在Python下编写与C类似的OpenGL代码。

在Linux下安装很方便，比如Feodra下是`sudo yum install PyOpenGL`。

{% highlight python %}
#!/usr/bin/python

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

def init():
    glClearColor(0,0,0,1)
    gluOrtho2D(-1,1,-1,1)

def plotpoints():
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(1,0,0)
    glBegin(GL_TRIANGLES)
    glVertex2f(0,0)
    glVertex2f(1,0)
    glVertex2f(1,1)
    glEnd()
    glFlush()

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(500,500)
    glutInitWindowPosition(50,50)
    glutCreateWindow("Plot Points")
    glutDisplayFunc(plotpoints)
    init()
    glutMainLoop()

main()
{% endhighlight %}
