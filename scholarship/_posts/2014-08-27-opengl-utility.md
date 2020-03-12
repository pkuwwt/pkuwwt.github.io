---
tags: visualization OpenGL
title: OpenGL使用技巧
---

## 好用的宏
显示OpenGL中可能出现的错误，能显示文件名和行号。
{% highlight c %}
#define GLERROR_LINENO                                             \
    {                                                              \
        GLenum code = glGetError();                                \
        while (code!=GL_NO_ERROR)                                  \
        {                                                          \
            printf("(%s:%d) %s\n",__FILE__,__LINE__,               \
					(char *) gluErrorString(code));                \
                code = glGetError();                               \
        }                                                          \
    }
{% endhighlight %}

