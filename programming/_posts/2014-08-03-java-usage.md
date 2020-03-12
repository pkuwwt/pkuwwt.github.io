---
layout: blog
comments: true
tags: programming java
title: Java Usage
---

Compile a source code, with a name identical to the public class in it, and the result of the compilation is file with extention `.class`.
{% highlight bash %}
javac Test.java
{% endhighlight %}

If a public class contains `main` method, you can run it with
{% highlight bash %}
java Test
{% endhighlight %}

`jar` file is essential a compressed directory. It can be a executable application when there is main manifest in it. So you can execute it with
{% highlight bash %}
java -jar file.jar
{% endhighlight %}

In most cases, `jar` file is just a package, and a container for classes. For example, there is main class `Test`, and it is contained in `package1.jar`, which depends on `package2.jar`, you can run it by
{% highlight bash %}
java -cp .:package1.jar:package2.jar Test
{% endhighlight %}
Paths or `jar` file specified by `-cp` option can be used as either runtime searching path or compile-time searching path, so you can use it in `javac` command. `.` means current dir, `:` is path separator.

By the way, if there is a main class in location `dir/Test.class`, you can execute it with 
{% highlight bash %}
java -cp dir Test
{% endhighlight %}
If you declare `package dir` in `src/Test.java`, you can also execute it by
{% highlight bash %}
java dir.Test
{% endhighlight %}

If you want to increase size of JVM heap space, you can use `-Xmx` option. And `-Xss` option corresponds to JVM stack size. All these options can be found by `java -h`. An example is 
{% highlight bash %}
java -Xmx1g -Xss4m Test
{% endhighlight %}

