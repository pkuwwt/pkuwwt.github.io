---
layout: blog
comments: true
title: bit操作
---

用`unsigned char`或`unsigned int`作为bool数组是常用的编程手法。对于第$n$位上的bit位，有如下几种操作。

### 设置bit ###

  number |= 1<<n;

### 清除bit ###

  number &= ~(1<<n);

### 切换bit ###

  number ^= 1<<n;

### bit位取值 ###

  bit = number & (1<<n);
  

参考: [How do you set, clear and toggle a single bit in C/C++?](http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c)
