---
layout: blog
comments: true
used3: true
title: draw critical points classification of planar system using tikz
---

The code is 

{% highlight latex %}
\usetikzlibrary{calc,intersections,positioning,arrows,decorations.markings,decorations.pathreplacing}
\begin{tikzpicture}
\draw[-stealth] (-2,0) -- (5,0) node[below] {$\det A$};
\draw[-stealth] (0,-3)--(0,3.5) node[below left]{$tr(A)$};
\draw[red] (0,0) to[out=90,in=206.6] (1,1) to[out=26.6,in=14] (4,2) node[above right]{$\Delta=0$};
\draw[red] (0,0) to[out=270,in=153.4] (1,-1) to[out=-26.6,in=-14] (4,-2);
% helix
\begin{scope}[xshift=1.5cm,yshift=0.6cm,scale=0.4,decoration={markings,mark=at position 0.5 with{\arrow{stealth}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\foreach \i in {0,180} {
\begin{scope}[rotate=\i]
\draw[postaction={decorate}] (0.2,0) to[out=-45,in=350] (0,-0.2) to[out=170,in=270] (-0.9,0.5) to[out=90,in=150] (0.5,0.5);
\end{scope}
}
\end{scope}
% helix
\begin{scope}[xshift=1.5cm,yshift=-0.6cm,scale=0.4,decoration={markings,mark=at position 0.5 with{\arrow{stealth reversed}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\foreach \i in {0,180} {
\begin{scope}[rotate=\i]
\draw[postaction={decorate}] (0.2,0) to[out=-45,in=350] (0,-0.2) to[out=170,in=270] (-0.9,0.5) to[out=90,in=150] (0.5,0.5);
\end{scope}
}
\end{scope}
% center
\begin{scope}[xshift=3cm,yshift=0cm,scale=0.05,decoration={markings,mark=at position 0.5 with{\arrow{stealth reversed}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\begin{scope}[rotate=-50]
\draw[postaction={decorate}] (0,0) circle(2 and 4);
\draw[postaction={decorate}] (0,0) circle(4 and 6);
\draw[postaction={decorate}] (0,0) circle(6 and 2);
\end{scope}
\end{scope}
% unstable node
\begin{scope}[xshift=1.2cm,yshift=2.5cm,scale=0.5,decoration={markings,mark=at position 0.8 with{\arrow{stealth}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\foreach \i in {0,180} {
\begin{scope}[rotate=\i]
\draw[postaction={decorate}] (0,0)  -- (1,1);
\draw[postaction={decorate}] (0,0) to[out=45,in=180] (1.2,0.3);
\draw[postaction={decorate}] (0,0) to[out=45,in=270] (0.3,1.2);
\draw[postaction={decorate}] (0,0) -- (-1,1);
\end{scope}
}
\end{scope}
% stable node
\begin{scope}[xshift=1.2cm,yshift=-2.5cm,scale=0.5,decoration={markings,mark=at position 0.8 with{\arrow{stealth reversed}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\foreach \i in {0,180} {
\begin{scope}[rotate=\i]
\draw[postaction={decorate}] (0,0)  -- (1,1);
\draw[postaction={decorate}] (0,0) to[out=45,in=180] (1.2,0.3);
\draw[postaction={decorate}] (0,0) to[out=45,in=270] (0.3,1.2);
\draw[postaction={decorate}] (0,0) -- (-1,1);
\end{scope}
}
\end{scope}
% unstable star node
\begin{scope}[xshift=2cm,yshift=1.4cm,scale=0.5,decoration={markings,mark=at position 0.7 with{\arrow{stealth}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\foreach \i in {30,60,120,150,210,240,300,330} {
	\begin{scope}[rotate=\i]
	\draw[postaction={decorate}] (0,0) -- (1,0);
	\end{scope}
}
\end{scope}
% stable star node
\begin{scope}[xshift=2cm,yshift=-1.4cm,scale=0.5,decoration={markings,mark=at position 0.7 with{\arrow{stealth reversed}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\foreach \i in {30,60,120,150,210,240,300,330} {
	\begin{scope}[rotate=\i]
	\draw[postaction={decorate}] (0,0) -- (1,0);
	\end{scope}
}
\end{scope}
% unstable  node
\begin{scope}[xshift=3.5cm,yshift=1.85cm,scale=0.5,decoration={markings,mark=at position 0.7 with{\arrow{stealth}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\draw[postaction={decorate}] (0,0) -- (1,1);
\draw[postaction={decorate}] (0,0) -- (-1,-1);
\foreach \i in {60,100,150,240,280,330} {
\begin{scope}[rotate=\i]
\draw[postaction={decorate}] (0,0) to[out=0, in=240] (1,0.4);
\end{scope}
}
\end{scope}
% stable  node
\begin{scope}[xshift=3.5cm,yshift=-1.85cm,scale=0.5,decoration={markings,mark=at position 0.7 with{\arrow{stealth reversed}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\draw[postaction={decorate}] (0,0) -- (1,1);
\draw[postaction={decorate}] (0,0) -- (-1,-1);
\foreach \i in {60,100,150,240,280,330} {
\begin{scope}[rotate=\i]
\draw[postaction={decorate}] (0,0) to[out=0, in=240] (1,0.4);
\end{scope}
}
\end{scope}
% degenerate
\begin{scope}[xshift=0cm,yshift=2cm,scale=0.5,decoration={markings,mark=at position 0.5 with{\arrow{stealth}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\foreach \i in {0.2,0.4,0.6,0,-0.2,-0.4,-0.6} {
\pgfmathsetmacro\Scale{1-abs(\i)}
\begin{scope}[xshift=\i cm,yshift=-\i cm,scale=\Scale]
\draw[postaction={decorate}] (0,0) -- (0.8,0.8);
\draw[postaction={decorate}] (0,0) -- (-0.8,-0.8);
\end{scope}
}
\end{scope}
% degenerate
\begin{scope}[xshift=0cm,yshift=-2cm,scale=0.5,decoration={markings,mark=at position 0.5 with{\arrow{stealth reversed}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\foreach \i in {0.2,0.4,0.6,0,-0.2,-0.4,-0.6} {
\pgfmathsetmacro\Scale{1-abs(\i)}
\begin{scope}[xshift=\i cm,yshift=-\i cm,scale=\Scale]
\draw[postaction={decorate}] (0,0) -- (0.8,0.8);
\draw[postaction={decorate}] (0,0) -- (-0.8,-0.8);
\end{scope}
}
\end{scope}
% saddle
\begin{scope}[xshift=-1.3cm,yshift=0cm,scale=0.5,decoration={markings,mark=at position 0.5 with{\arrow{stealth}}}]
\draw (-1,0)--(1,0);
\draw (0,-1)--(0,1);
\foreach \i in {0,180} {
\begin{scope}[rotate=\i]
\draw[postaction={decorate}] (1.1,0.9) to[out=225,in=135] (1.1,-0.9);
\draw[postaction={decorate}] (0.9,1.1) to[out=225,in=-45] (-0.9,1.1);
\draw[postaction={decorate}] (1,1) -- (0,0);
\draw[postaction={decorate}] (0,0) -- (-1,1) ;
\end{scope}
}
\end{scope}
\end{tikzpicture}
{% endhighlight %}

After exporting from `ktikz`, the result is 

![](../img/critical_classfication.png)

The result is satisfying, however, it takes me a lot of time to adjust the coordinates. Maybe using parameterized curve will be a better choice.

The main point in this example is to use `\draw (P0) to[out=angle1, in=angle2] (P1)` syntax to draw any smooth curves with tangent angle at each control point. `angle1` means tangent algle of curve `P0-P1` at point `P0` pointing to `P1`, and `angle2` means tangent angle at `P1` pointing to `P0`.

<div id="vis">
<style>
.curve, .line , .dash, .arc {
fill: none;
stroke-width: 1px;
}
.curve {
stroke: red;
stroke-width: 3px;
}
.line, .arc{
stroke: white;
stroke-width: 1px;
}
.dash {
stroke: white;
stroke-width: 1px;
stroke-dasharray: 5,5;
}
</style>
<script>
var w = 300, h = 180;
var A = {x:100,y:60,t:"P0"};
var B = {x:200,y:70,t:"P1"};
var M1 = {x:130,y:130,t:"M1"};
var M2 = {x:170,y:130,t:"M2"};
var A1 = {x:150, y:60, t:"A1"};
var B1 = {x:250, y:70, t:"B1"};
var level = 20;
var svg = d3.select("#vis").append("svg:svg")
		.attr("width", w)
		.attr("height", h);
function x(d) { return d.x; }
function y(d) { return h-d.y; }
var lineFunc = d3.svg.line().x(x).y(y);
function interpolate(points, ratio) {
	if(arguments.length < 2 || ratio==undefined) ratio = 0.5;
	var r = [];
	r.push(points[0]);
	for(var i=1; i<points.length; i++) {
		var p0 = points[i-1], p1 = points[i];
		r.push({x:p0.x*(1-ratio)+p1.x*ratio, y:p0.y*(1-ratio)+p1.y*ratio});
	}
	r.push(points[points.length-1]);
	return r;
}
function getBezierCurve(points, level, ratio) {
	if(arguments.length < 2 || ratio==undefined) ratio = 0.5;
	var curve = points;
	for(var i=0;i<level;i++) {
		curve = interpolate(curve, ratio);
	}
	return curve;
}
function addArc(pos, startAngle, endAngle, innerRadius, outerRadius) {
	var arc = d3.svg.arc()
		.innerRadius(innerRadius)
		.outerRadius(outerRadius)
		.startAngle(startAngle)
		.endAngle(endAngle);
	return svg.append("path")
		.attr("class", "arc")
		.attr("d", arc)
		.attr("transform", "translate(" + x(pos) + "," + y(pos) + ")");
}
function getLineAngle(p1, p2) {
	var dx=x(p2)-x(p1), dy=y(p2)-y(p1);
	return Math.atan2(dy,dx);
}
function addAngleMark(center, p1, p2) {
	var angle1=getLineAngle(center, p1) + Math.PI/2.0;
	var angle2=getLineAngle(center, p2) + Math.PI/2.0;
	console.log(angle1);
	console.log(angle2);
	return addArc(center, angle1, angle2, 15,15);
}

var lines = svg.selectAll("path")
	.data([[A,M1],[B,M2]])
	.enter()
	.append("path")
	.attr("class", "line")
	.attr("d", lineFunc);
var dash1 = svg.append("path")
	.attr("d", lineFunc([A,A1]))
	.attr("class", "dash");
var dash2 = svg.append("path")
	.attr("d", lineFunc([B,B1]))
	.attr("class", "dash");
var arc1 = addAngleMark(A, A1, M1);
var arc2 = addAngleMark(B, B1, M2);
var curve = svg.selectAll("path.curve")
	.data([getBezierCurve([A,M1,M2,B],level)])
	.enter()
	.append("path")
	.attr("class", "curve")
	.attr("d", lineFunc);
var texts = svg.selectAll("text")
	.data([A,B])
	.enter()
	.append("text")
	.attr("x", x)
	.attr("y", function(d) { return y(d)+20; })
	.text(function(d) { return d.t; });
</script>
</div>

And one lesson from this example is that you should always use big enough(or normal) coordinates to draw curves(e.g. circles) and then scale it to smaller one as required when you use decoration.

