---
layout: blog
comments: true
title: 用djvulibre来设置djvu文件的索引
---

djvulibre中的`djvused`工具堪称djvu文件操作的瑞士军刀，在此记录一下如何修改其索引/目录，也就是所谓的outline。

首先，如果djvu文件中已经有了索引，可以将其导出来，一来可以参考其语法，二来不需要自己从头动手。
{% highlight bash %}
djvused file.djvu -e "print-outline"
{% endhighlight %}
`-e`选项用来指定命令，这几乎是你唯一需要的选项。

outline文件的语法很简单，比如
{% highlight xml %}
(bookmarks
 ("Contents"
  "#2")
 ("Chapter 1: Title"
  "#4"
  ("1.1. section title"
  "#5")
  ("1.2. section title"
  "#6")
  )
)
{% endhighlight %}
最外层是`(bookmarks ...)`，里面的内容是嵌套的列表`("title" "#page-id" [subitem1 [subitem2 [...]]])`。列表只有前两项是必须的，即标签和页面标识，然后后面可以接任意个类似语法的子列表。

需要注意的是，这里的`page-id`其实应该叫`page-title`，你可以将其理解成页码，一般情况下也确实是页码。但是，很多书将前几页的页码表示成`I,II`之类的数字。换句话说，`page-title`起到唯一标识页面的作用，只要求唯一性，而不要求它必然是数字。

另外一方面，实际的物理上的文件页面数自然也能够唯一地标识页面，`select`命令后面确实使用是这个页码，只不过，outline文件中使用的则是`page-title`。你可以显式地将`page-title`全改成文件页面数。
{% highlight bash %}
for (( i=800;i>=1;i-- ));do
	djvused file.djvu -e "select $i;set-page-title $i;save"
done
{% endhighlight %}
这里假设共有800页。或者，在前面留三页(I,II,III)，然后从第4页起重编号
{% highlight bash %}
for (( i=800;i>=4;i-- ));do
	djvused file.djvu -e "select $i;set-page-title $((i-3));save"
done
djvused file.djvu -e "select 1;set-page-title I;save"
djvused file.djvu -e "select 2;set-page-title II;save"
djvused file.djvu -e "select 3;set-page-title II;save"
{% endhighlight %}
操作过程中不允许违反`page-title`唯一性原则。

修改`bookmarks`格式的outline文件和页码之后，就可以将outline文件写进djvu中去了。
{% highlight bash %}
djvused file.djvu -e "set-outline outline.txt;save"
{% endhighlight %}

不过，用这种方法修改的outline在djviewer中可用，但evince中不一定能够正确显示。所以最好是全部用数字。

