---
vim: wrap expandtab ft=markdown
layout: blog
title: 建站过程
---

## 申请域名
找到一个免费的域名提供商[Tk](http://dot.tk), 注册帐号，然后申请了域名[pkuwwt.tk](http://pkuwwt.tk)。不太显眼的tk域名都是免费的，免费域名一年之后要续约。


## 创建Github仓库
注册一个Github帐号pkuwwt，因此，我的github帐号是[github.com/pkuwwt](http://github.com/pkuwwt)。

然后，我可以建立任意的github仓库(repository)。使用过git的人应该不会陌生。

Github提供了网页托管服务，但需要注意的是，此托管服务愿意是为软件项目提供主页支持，并不是用来免费建站的。因此，它附加了一些限制。

如果你的仓库随便起名的话，称为Project Page。如果你的仓库起名为username.github.com(username.github.io好像也可以)的话，称为User/Orgnaization Page。显然Project Page仓库可以有多个，User/Orgnaization Page仓库只能有一个。

那么Github的限制条件就是，Project仓库只能绑定主域名(domain)，而User/Orgnaization仓库既可以绑定主域名，又可以绑定子域名(subdomain)。比如pkuwwt.tk是主域名，blog.pkuwwt.tk是子域名。因为每个人只有一个User/Orgnaization仓库，因此只能绑定一个子域名。这意味着，一个帐号可以绑定多个主域名，只能绑定一个子域名。

因此，建站策略只能是一个主域名，不使用子域名，用目录结构来对内容进行分类。


## Github的网络服务设置
Github仓库的网络设置很方便，只需要修改仓库根目录下的CNAME文件即可。CNAME中只有一行文字，即你的域名，Github只允许绑定到一个域名上，如果想多个域名指向同一个仓库，则只能用域名转发了。比如，在我的pkuwwt.github.com仓库下的CNAME中添加一行
{% highlight bash %}
pkuwwt.tk
{% endhighlight %}

这里的[pkuwwt.tk]是我刚申请的域名，而且是主域名。当然，我绑定到一个子域名上也是可以的。

修改完CNAME之后10分钟才会生效。

## 域名服务的DNS设置
在[dot.tk](http://dot.tk)网上修改域名[pkuwwt.tk](http://pkuwwt.tk)的DNS设置。如果是主域名，使用设置

  * A Record
  * hostname: pkuwwt.tk
  * IP Address: 204.232.175.78

如果是子域名，使用设置

  * CNAME Record
  * hostname: blog.pkuwwt.tk
  * IP Address: pkuwwt.github.io

使用pkuwwt.github.io的好处在于，它会自动更新IP地址。但对于我的这个建站来说意义不大，因为只被允许使用一个子域名，我干脆就不用。

另外，查看一个域名的DNS可以使用命令
{% highlight bash %}
$ dig pkuwwt.tk +nostats +nocomments +nocmd
{% endhighlight %}

详细过程参考[Github文档](https://help.github.com/categories/20/articles)。


现在，你应该可以访问[pkuwwt.tk](http://pkuwwt.tk)了。但是如果显示404页面，要么是你没有等10分钟，要么是你没有index.html文件，要么是DNS设置错了。

## 选择静态网页生成工具
因为Github并不提供主机服务，动态网页是没指望了，服务端编程和数据库更是没影，因此只能使用静态网页。

但是，问题是，谁会愿意去手动编写html文件？

一个较好的解决方案是，用wiki或Markdown之类的类文本格式写文档，然后，用工具生成静态网页。ruby有一个工具是[jekyll](http://jekyllrb.com/)，而python对应的工具是[hyde](http://hyde.github.io)。

jekyll的优点在于，它和Github是有关系的，Github的Page功能就是它提供的。因此，你根本不需要将生成的静态传到Github上去。

jekyll的安装步骤很简单
{% highlight bash %}
$ gem install jekyll
$ gem update --system
{% endhighlight %}

jekyll的使用步骤也很简单
{% highlight bash %}
$ jekyll new my-site
$ cd my-site
$ jekyll serve
{% endhighlight %}
然后，你就可以访问`http://127.0.0.1:4000`了。

`jekyll serve`命令会调用`jekyll build`，即在当前目录下生成`_site`目录。因此，我们可以在本地测试，测试满意了再传到网上去。

我使用Windows8+Cygwin来模拟Linux环境，可能会有一些额外的安装问题。

  * cygwin下gem需要下载rubygems的源码包安装
  * gem install jekyll可能会失败，参考[StackOverflow](http://stackoverflow.com/questions/15815574/spawn-h-not-found-while-installing-octopress-on-cygwin)
  * Windows8下面localhost默认是没有的，使用127.0.0.1即可。实在不行，关掉防火墙或增加几条规则。


## 寻找网站模板
有了方法并不一定能得到好的结果。因为，做成一件事和做好一件事还是有区别的，特别是与艺术相关的东西。要想设计一个好的网页，既需要有技术，也需要有灵感，实在是两难。

最直接的办法是拿来主义，看到好的模板，直接拿来用，最多改改标题，改改人名(这不就是小时候鄙视的坏学生作为吗)。

我发现freepiano这个软件不错，它的主页也不错，于是把其作者的网站给拿下来了。
{% highlight bash %}
$ git clone https://tiwb.github.com/tiwb/tiwb.github.com.git tmp
$ cd tmp
$ rm -rf .git
{% endhighlight %}

我把它的源码全荡下来，存到了tmp目录中。删掉了git仓库信息。

至于内容，首先我先用`jekyll serve`测试了一下，发现能用。然后，来了个全局搜索替换，把它的名字改成了我的名字。并且删掉了所有`_post`子目录中的Markdown文件。

这个模板是博客性质的，只要往`_post`中放上符合命名规则的Markdown文件，它就能按规则给你显示出一个个条目出来。

至于模板上的标签页，可以在`_includes/header.html`中找到答案。每个标签页对应着一个类别(category)，一个子目录和一个显示名称。在每个子目录下的index.html中用到了类别信息。

你想添加一个新的标签，或者修改已有标签都是很显然的事情。

## 上传至仓库
将Github上的仓库下载到本地，然后，修改其文件，再上传即可。

在上面的tmp目录所在的目录中
{% highlight bash %}
$ git clone https://pkuwwt.github.com/pkuwwt/pkuwwt.github.com.git pkuwwt.github.com
$ cd pkuwwt.github.com
$ cp -r ../tmp/* .
$ git add *
$ git commit -m "initial website"
$ git push origin master
{% endhighlight %}

之后，会提示你输用户名和密码。

需要注意的是，小心你的CNAME被覆盖了。另外，有一个.gitignore文件可以防止某些文件和目录被加到git仓库中去。比如一个典型的.gitignore文件是
{% highlight bash %}
_site
*.swp
.DS_Store
{% endhighlight %}

上传成功之后，我也就拥有了一个装逼的个人网站了。虽然没有备案，随时会被墙掉。

