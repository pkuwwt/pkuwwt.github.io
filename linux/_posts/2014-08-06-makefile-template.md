---
layout: blog
comments: true
title: Makefile模板
---

由于很多小项目的Makefile都是大同小异，因此，每次都重复写代码是一件烦琐的事情。下面的模板适用于如下的情况

  * 源码由.h,.cpp两种文件组成
  * 当需要生成可执行文件时，恰好有一个.cpp文件中有main函数
  * 若所有.cpp源码都没有main函数，则支持静态库和动态库的生成

{% highlight vim %}
BIN=
STATIC_LIB=
DYNAMIC_LIB=
CC=g++
AR=ar 
CFLAG=-g -Wall  
LIB=-lm
CPP_SRC=$(wildcard *.cpp)
HEAD_SRC=$(wildcard *.h)
OBJ=$(CPP_SRC:%.cpp=%.o)

all: ${BIN} ${STATIC_LIB} ${DYNAMIC_LIB}

%.o: %.cpp %.h
    ${CC} -c ${CFLAG} $< -o $@ 
${BIN}: ${OBJ} ${HEAD_SRC}
    ${CC} -o $@ ${OBJ} ${CFLAG} ${LIB}
${STATIC_LIB}: ${OBJ} ${HEAD_SRC}
    ${AR} -cvq $@ ${OBJ}  
${DYNAMIC_LIB}: ${CPP_SRC} ${HEAD_SRC}
    ${CC} -fPIC -c ${CPP_SRC} ${CFLAG}
${CC} -shared -o $@ ${OBJ} 

clean:
    rm -f ${BIN} ${OBJ} ${STATIC_LIB} ${DYNAMIC_LIB}

# vim: noexpandtab
{% endhighlight %}

使用方法很简单，如果要生成可执行文件，给`BIN`变量赋值即可，如果要生成静态库，给`STATIC_LIB`变量赋值，如果要生成动态库，给`DYNAMIC_LIB`变量赋值即可。显然，可以同时生成一个静态库和动态库，但静态库或动态库不能与可执行文件同时生成。

此模板的缺陷是自然的，它无法像CMakefile那样指定详细的依赖关系，也无法同时生成多个目标。

为方便在vim中使用，可将如下代码写入`~/.vimrc`中。这样，在Insert模式下，输入`#m`再回车就会自动键入此模板。

{% highlight vim %}
if has("eval") && has("autocmd")
	func! Abbrev_make()
		ia <buffer> #m 
		\BIN=
		\<CR>STATIC_LIB=
		\<CR>DYNAMIC_LIB=
		\<CR>CC=g++
		\<CR>AR=ar 
		\<CR>CFLAG=-g -Wall  
		\<CR>LIB=-lm
		\<CR>CPP_SRC=$(wildcard *.cpp)
		\<CR>HEAD_SRC=$(wildcard *.h)
		\<CR>OBJ=$(CPP_SRC:%.cpp=%.o)
		\<CR>
		\<CR>all: ${BIN} ${STATIC_LIB} ${DYNAMIC_LIB}
		\<CR>
		\<CR>%.o: %.cpp %.h
		\<CR>	${CC} -c ${CFLAG} $< -o $@ 
		\<CR>${BIN}: ${OBJ} ${HEAD_SRC}
		\<CR>	${CC} -o $@ ${OBJ} ${CFLAG} ${LIB}
		\<CR>${STATIC_LIB}: ${OBJ} ${HEAD_SRC}
		\<CR>	${AR} -cvq $@ ${OBJ}  
		\<CR>${DYNAMIC_LIB}: ${CPP_SRC} ${HEAD_SRC}
		\<CR>	${CC} -fPIC -c ${CPP_SRC} ${CFLAG}
		\<CR>${CC} -shared -o $@ ${OBJ} 
		\<CR>
		\<CR>clean:
		\<CR>	rm -f ${BIN} ${OBJ} ${STATIC_LIB} ${DYNAMIC_LIB}
		\<CR>
		\<CR># vim: noexpandtab
	endfunc
	augroup abbreviation
	au!
	au Filetype make :call Abbrev_make()
	augroup END
endif
{% endhighlight %}

