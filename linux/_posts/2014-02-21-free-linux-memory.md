---
layout: blog
comments: true
title: 清理Linux中的不用或缓冲的内存
---

步骤1: 确认缓存或不用内存，使用如下命令

{% highlight bash %}
free -m
{% endhighlight %}

步骤2: 清理文件系统缓存，使用如下命令

{% highlight bash %}
sync
{% endhighlight %}

注意: 内核2.6.16.x和更新的内核版本提供了一种机制，在执行此命令时，令内核丢弃**页面缓存**，和/或**inode**和**目录缓存(dentry cache)**。因此有助于释放大量的内存。

步骤3: 为了只释放页面缓存，或目录缓存和inodes，或清楚所有内存，分别采用下面三个命令

  - 页面缓存: `echo 1 > /proc/sys/vm/drop_caches`
  - 目录缓存和inodes: `echo 2 > /proc/sys/vm/drop_caches`
  - 页面缓存，目录缓存和inodes: `echo 3 > /proc/sys/vm/drop_caches`

**注意**: 上述所有命令都对系统无害，且只会有助于释放不用的内存。而且`sync`还会清理僵尸(zombie)对象和它们占用的内存。

**但是，如果你执行这些命令时正在写数据，你实际上在数据到达磁盘之前就将它从文件缓存中清除掉了，这可能会造成很不好的影响。**

__所以，为了避免这种事情发生，你可以`echo`值到/proc/sys/vm/vfs_cache_pressure中，告诉内核，当清理inoe/dentry缓存时应该用什么样的优先级__。LinuxInSight对值的范围解释得很清楚:

  `vfs_cache_pressure=100`是默认值，内核会尝试重新声明dentries和inodes，并采用一种相对于页面缓存和交换缓存比较"合理"的比例。减少`vfs_cache_pressure`会导致内核倾向于保留dentry和inode缓存。而增加`vfs_cache_pressure`超过100时，则会导致内核倾向于重新声明dentries和inodes

简而言之，小于100的值不会导致缓存的大量减少。超过100的值则会告诉内核你希望以高优先级来清理缓存。其实，无论你采用什么值，内核清理缓存的速度都是比较低的。如果将此值设置为10000，系统将会将缓存减少到一个合理的水平。

## 参考文献

  - [FREE UP AND RELEASE UNUSED OR CACHED MEMORY](http://blog.midnightmonk.com/225/linux/free-up-and-release-unused-or-cached-memory.shtml)
