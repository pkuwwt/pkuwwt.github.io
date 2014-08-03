---
layout: blog
comments: true
title: Java Usage
---

Compile a source code, with a name identical to the public class in it, and the result of the compilation is file with extention `.class`.
{% highlight bash %}
javac Test.java
{% endhilight %}

If a class contains `main` method, you can run it with
{% highlight bash %}
java Test
{% endhilight %}

`jar` file is essential a compressed directory. It can be a executable application when there is main manifest in it. So you can execute it with
{% highlight bash %}
java -jar file.jar
{% endhilight %}

In most cases, `jar` file is just a package, and a container for classes. For example, there is main class `Test`, and it is contained in `package1.jar`, which depends on `package2.jar`, you can run it by
{% highlight bash %}
java -cp .:package1.jar:package2.jar Test
{% endhilight %}

If you want to increase size of JVM heap space, you can use `-Xmx` option. And `-Xss` option corresponds to JVM stack size. All these options can be found by `java -h`. An example is 
{% highlight bash %}
java -Xmx1g -Xss4m Test
{% endhighlight %}
