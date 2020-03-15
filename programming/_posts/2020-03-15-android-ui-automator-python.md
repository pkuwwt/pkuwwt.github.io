---
vim: wrap expandtab ft=markdown
layout: blog
tags: [android, python, functional testing, uiautomator]
title: Python-based ui-automator for Android
---

## What is ui-automator

[ui-automator](https://developer.android.com/training/testing/ui-automator) is a functional UI testing framework
for Android developed by Google. It is based on Java, and the scripting scripts have to be packaged as jar or apk
file and installed on devices before testing.

[python-uiautomator2](https://github.com/openatx/uiautomator2) on the other hand is a python-wrapper, which allows

  * scripting with Python on computer
  * controlling the mobile with computer without usb connection
  * screen-casting
  * exact and realtime device controlling

## Installation

  * Connect **ONLY ONE** mobile to the computer with developer-mode open, make sure `adb devices` works
  * Install packages: `pip3 install -U uiautomator2 weditor`
  * Install daemons to the mobile: `python3 -m uiautomator2 init`

The `weditor` is a standalone web-server to interact with the mobile through browser.

## Basic Usage

### Connection

Connect the mobile by wifi

```python
import uiautomator2 as u2
d = u2.connect('192.168.31.37')
print(d.info)
```

Connect the mobile by USB

```python
import uiautomator2 as u2
d = u2.connect('mobile-serial')  # get from "adb devices"
print(d.info)
```

### App management

Install an app

```python
d.app_install('http://url.com/some.apk')  # only support URL
```

Lauch an app

```python
d.app_start('com.example.hello_world')
```

Stop an app

```python
d.app_stop('com.example.hello_world')  # am force-stop
d.app_clear('com.example.hello_world') # pm clear
d.app_stop_all()
d.app_stop_all(excludes=['com.examples.demo'])
```

Get app info

```python
d.app_info('com.examples.demo')
```

List all running apps

```python
d.app_list_running()
```

Push files

```python
d.push('foo.txt', '/sdcard/')
d.push('foo.txt', '/sdcard/bar.txt')
with open('foo.txt', 'rb') as f:
    d.push(f, '/sdcard/')
d.push('foo.sh', '/data/local/tmp', mode=0o755)
```

Pull files

```python
d.pull('/sdcard/tmp.txt', 'tmp.txt') 
```
There seems to be permission problem for directory `/data/data`.


Key events

```python
d.screen_on()
d.screen_off()
d.press('home')
d.press('back')
d.press(0x07, 0x02)  # keycode 0x07 ('0') with META ALT(0x02)
d.unlock()
d.click(x, y)
d.double_click(x, y)
d.double_click(x, y, 0.1)  # duration is 0.1s
d.long_click(x, y)
d.long_click(x, y, 0.5)    # default 0.5s
d.swipe(sx, sy, ex, ey)
d.swipe(sx, sy, ex, ey, 0.5)
d.drag(sx, sy, ex, ey)
d.drag(sx, sy, ex, ey, 0.5)
```
