---
layout: blog
comments: true
tags: scholarship zotero
title: 文献管理工具Zotero
---

## 介绍
[Zotero](https://www.zotero.org)是一个文献管理工具，除了常见的分类，标签，导出等功能之外，它的特色在于基于网页提取信息，并支持远程同步。另外，它还有一些插件处理pdf文件。

另一个吸引人的地方是，它是跨平台的。无论你是Windows, Linux还是Mac，都可以使用。它甚至只用在firefox上安装一个插件就可以用了。而且，完全免费。

## 安装
Zotero是基于firefox的，因此，你可以只使用firefox的Zotero插件。另一种选择是安装standalone版本，它其实是内置了一个firefox的。对于standalone版本，如果要和其它浏览器配合使用，则需要在这些浏览器上安装相应的Zotero Connector插件。

另外，还有一些其它插件，就看需求选择安装了。

## 使用
Zotero有一个功能是标签着色功能。右边面板上有标签(tag)管理的功能，左下角则显示有标签，并可以为其设置颜色。

最好用的功能是网页上提取文献信息。装好Zotero Connector插件之后，浏览器就会自动分析每个网页，一旦发现有文献信息，在地址栏右边会显示一个按键，点击就会将这些信息存到Zotero了。试一下google scholar，你会发现提取的文献的列表。如果有全文链接，还会自动下载并改名。自动下载全文的功能在校园网中也是很方便的。

## 同步
你需要先注册一个Zotero帐号，然后，简单设置一下就可以将文献信息同步到Zotero服务器上了。

Zotero的帐户默认是不保存附件的，但也提供了一个300M的空间来存储附件文件。这显然不够。

要想把附件也同步到云端，需要找一个支持WebDAV的云空间。国内目前只有[坚果云](http://jianguoyun.com)支持。其完整链接格式是`https://dav.jianguoyun.com/dav/DavStore/zotero`。其中，`DavStore`是你自己新建的同步文件夹(根目录，默认只有一个My Nutstore的文件夹)。当然，你还要在坚果云的设置中新建一个WebDAV应用，应用的密码就是Zotero中用到的密码。坚果云一个月限流量(上传1G，下载3G)，对论文来说够用了。

## 技巧

  - Zotero中的collection是可以嵌套的，就像目录中可以有子目标一样，直接将一个collection拖到另一个collection即可
  - Linux下按`Alt`键，Windows下按`Ctrl`，Mac下按`Option`键，可以显示一个文献在哪个collection中

## 参考

  - [https://www.zotero.org/support/collections_and_tags](https://www.zotero.org/support/collections_and_tags)

