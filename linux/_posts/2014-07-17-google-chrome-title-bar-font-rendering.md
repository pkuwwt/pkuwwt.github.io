---
title: google-chrome浏览器的标题栏字体渲染问题
layout: blog
comments: true
---

在有些情况下，linux下安装的google-chrome浏览器会出现中文字体渲染不了的问题，比如，标题栏，字体栏，弹出窗口等。

经搜索和实验，发现，这个问题来源于`google-droid-sans-fonts`这个包中的`/etc/font/conf.d/65-google-droid-sans.conf`文件。当然，文件名不一定完全一样，在`/etc/font/conf.d`中找包含`*google-droid*`文件即可，然后将其备份后删除。

参考自[superuser页面](http://superuser.com/questions/705658/unicode-characters-cannot-be-displayed-on-chrome-tab-title-on-linux)和[google code讨论页面](https://code.google.com/p/chromium/issues/detail?id=316723)

