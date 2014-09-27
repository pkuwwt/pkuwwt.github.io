---
layout: blog
comments: true
title: 用VTK生成非结构化网格上的矢量场
---

在ParaView中，使用Calculator是件很酷的事，写一个算式就可以生成一个数据场。但是交互往往不适于批量生成数据。下面给出vtk的代码，用于生成一个非结构化网格上的Lorentz矢量场。

{% highlight python %}
#!/usr/bin/python

import vtk

def lorentzFunc(sigma,rho,beta):
    return "iHat*%f*(coordsY-coordsX) + jHat*(coordsX*(%f-coordsZ)-coordsY) + kHat*(coordsX*coordsY-%f*coordsZ)" % (sigma, rho, beta)

points = vtk.vtkPointSource()
points.SetNumberOfPoints(1000)
points.SetCenter([0,0,0])
points.SetRadius(10)

tets = vtk.vtkDelaunay3D()
tets.SetInputConnection(points.GetOutputPort())

calc = vtk.vtkArrayCalculator()
calc.SetInputConnection(tets.GetOutputPort())
calc.SetAttributeModeToUsePointData()
calc.AddCoordinateScalarVariable("coordsX",0)
calc.AddCoordinateScalarVariable("coordsY",1)
calc.AddCoordinateScalarVariable("coordsZ",2)
calc.SetFunction(lorentzFunc(20,18, 8/3.0))
calc.SetResultArrayName("vectors")

writer = vtk.vtkUnstructuredGridWriter()
writer.SetInputConnection(calc.GetOutputPort())
writer.SetFileName("out.vtk")
writer.Write()

mapper = vtk.vtkDataSetMapper()
mapper.SetInputConnection(calc.GetOutputPort())

actor = vtk.vtkActor()
actor.SetMapper(mapper)

ren = vtk.vtkRenderer()
ren.AddActor(actor)

win = vtk.vtkRenderWindow()
win.AddRenderer(ren)

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(win)

iren.Start()
{% endhighlight %}


