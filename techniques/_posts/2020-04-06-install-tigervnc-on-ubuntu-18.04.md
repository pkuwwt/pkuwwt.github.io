---
vim: wrap expandtab ft=markdown
layout: blog
tags: tighervnc ubuntu
title: Install tigervnc on Ubuntu18.04
---

In this post, I will introduce how to install tighervnc on Ubuntu18.04 with LXDE desktop. LXDE is a lightwight and very clean desktop environment.

## Installation of vncserver

First, we install some packages.
```
sudo apt install lxterminal lxdession ibus tigervnc-standalone-server
```

`ibus` is just an input-method engine, which is not required.

Then we have a script `~/.vnc/xstartup`

```
#!/bin/bash

xrdb $HOME/.Xresources
xsetroot -solid grey

export XKL_XMODMAP_DISABLE=1
/etc/X11/Xsession

lxterminal &
/usr/bin/lxsession -s LXDE &
ibus-daemon &
```

Maybe we need a restart script `~/.vnc/restart.sh`

```
#!/bin/bash
vncserver -kill :1
vncserver -localhost no -geometry 1920x1260 :1
```

Then we run
```
~/.vnc/restart.sh
```

Now, the vncserver is ready.

## Client

Any tigervnc viewer will be OK. For example, the client for windows can be downloaded from [here](https://bintray.com/tigervnc/stable/download_file?file_path=tigervnc-1.10.1.exe).

