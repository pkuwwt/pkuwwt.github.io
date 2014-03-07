---
layout: blog
comments: true
title: Linux下使用github
---

基本步骤是

  - 申请注册github帐号: 用户名`myusername`和邮箱`mymail@gmail.com`
  - 创建仓库: `myrepos`
  - 创建本地仓库: `git clone https://github.com/myusername/myrepos.git`
  - 修改本地仓库
  - 上传本地仓库
  - 使用ssh，避免每次都输入密码

## 修改本地仓库
假如你先进入到你的本地仓库中，生成一个文件`myfile.txt`

{% highlight bash %}
cd myrepo
echo "hello world" >myfile.txt
{% endhighlight %}

生成完成之后，本地仓库并没有意识到`myfile`的存在性(更准确地讲，git已知知道仓库中多了文件，只不过，需要你显式地加进来而已)，因此，需要显式地加入进来

{% highlight bash %}
git add myfile.txt
export EDITOR=vim
git commit -a
{% endhighlight %}

`git add`的作用是将文件加入到索引中(index)，`git commit -a`的作用是将索引中的部分提交到仓库中，这中间还会要求你写日志。它会用系统定义的编辑器(即`EDITOR`)来打开日志文件，因此，你有必要先定义一个`EDITOR`之后，再执行`git commit`。最好是把`export EDITOR=vim`写到`~/.bashrc`中去，这样就不需要再管它了。

## 上传本地仓库
本地作了修改，就需要同步到github服务器上。命令很简单

{% highlight bash %}
git push origin master
{% endhighlight %}

这条命令会要求你输入用户名和密码，比较烦，你可以用ssh来避免这个问题。

## 使用ssh
首先，你要生成ssh的公钥和私钥对。公钥是给别人的，私钥自己留着，一对这样的密钥中，公钥的作用是加密，而只有匹配的私钥可以解密。这样，你去登陆别人的服务器时，对方用你的公钥加密一个随机数，然后，你解密之后再发给服务器，如果两个数相同，你的认证也就通过了。

生成密钥的命令是

{% highlight bash %}
ssh -t rsa -C "mymail@gmail.com"
{% endhighlight %}

过程中会有交互，如果你不输入密码，则ssh的认证过程是没有密码，即免密码。否则，你以后还是得输一遍密码，则避免了输服务器密码，但是要输自己的ssh密码。

然后，将自己的公钥，即`~/.ssh/id_rsa.pub`文件内容，交给github。在自己的github的[ssh设置页面](https://github.com/settings/ssh)里面，加入公钥内容即可(用个leafpad/gedit之类的记事本打开，拷到指定位置即可)。

现在，你需要确认认证是否成功
{% highlight bash %}
ssh -T git@github.com
{% endhighlight %}
它会告诉你是否成功的，否则，参见github官方[文档](https://help.github.com/articles/generating-ssh-keys)。

现在，你和github服务器之间，相当于就达成了ssh认证的协议。但是，还有一个问题，本地仓库不知道如何用ssh啊。

因此，最后一步，你需要修改一下本地仓库。在本地仓库根目录执行

{% highlight bash %}
git remote set-url origin git@github.com:myusername/myrepo.git
{% endhighlight %}

然后，一切就都OK了。

