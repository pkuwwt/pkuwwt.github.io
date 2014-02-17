---
layout: blog
comments: true
title: 用wget下载C++的手册
---


在Linux下，一般的软件的文档都是比较全的，但是C++的文档却没有，虽然存在libstdc++-docs这个包，但里面只不过是由源码生成的类库文档，对于普通用户来说并没有太多用处。

因此，常常只能到[www.cplusplus.com/reference](www.cplusplus.com/reference)网站上查看文档和用法。

如果能够将此[网站](www.cplusplus.com/reference)上的文档下载下来，放在本地使用，就可以省却连网的麻烦。这点对于不能连网的用户是很有用的。

我们自然会想到使用wget来"扒"网页。

{% highlight bash %}
wget -r -l 5 -np -k www.cplusplus.com/reference/
{% endhighlight %}

这里的`-r`表示递归，`-l`表示递归下载的层次，这里是5层，`-np`表示不下载上层的文件，以免将整个网站都荡下来, `-k`则表示在下载完之后修改网页中的链接，以供本地使用。最后，不要忘了网址最后的斜划线。

结果会得到一个目录www.cplusplus.com , 用浏览器访问即可。

{% highlight bash %}
firefox ./www.cplusplus.com/reference/index.html
{% endhighlight %}

但是有一个问题，如果你没有联网，则网页的整洁的页面就变乱了。这是因为每个网页中都用到了`www.cplusplus.com/v320/main.js`和`www.cplusplus.com/v320/main.css`这两个文件，用来生成网页的布局。

现在，我们单独将这两个文件下载下来，放在目录`www.cplusplus.com/reference/v320/`中。剩下的问题就是如何将所有的html文件中的main.js和main.css的指向外网的绝对路径改成本地的相对路径。

我的脚本是`www.cplusplus.com/reference/script.sh`

{% highlight bash %}
#!/bin/bash

handle() {
	dir=`dirname "$@"`
	dir=${dir##./}
	exp=`echo "$dir"| sed 's/[^/]\+/../g'`
	if [[ $dir == "." ]] then exp="." fi
	sed -i "s,http://www.cplusplus.com/v320,$exp/v320,g" "$@" 
	sed -i "s,show_ad,show_ad_,g" "$@" 
	sed -i "s,DonateBox,DonateBox_,g" "$@" 
}
export -f handle

find . -name '*.html' -exec bash -c 'handle "$0"' {} \;
{% endhighlight %}

执行脚本即可处理所有html文件

{% highlight bash %}
cd www.cplusplus.com/reference
bash ./script.sh
{% endhighlight %}

此脚本并不是很复杂，功能是将网址`http://www.cplusplus.com/v320`换成类似于`../../v320`之类的相对路径，并去掉广告。脚本里面有两个好用的功能需要备忘一下：

  - sed命令中的分隔符不一定是`/`，你可以用任何分隔符，比如本例中用的是`,`。
  - `export -f`可以将函数定义传递到子shell中，从而可以在find中调用此函数。当然先获得所有文件名，再处理也是可以的，但在find中逐个文件处理可以处理文件名中包含空格的情况。

最后，我把我整理的[文档](../img/www.cplusplus.com.tar.gz)贡献出来。

