---
layout: blog
comments: true
tags: programming C++
title: C++中打印指针
---

C++中没有默认地打印指针地址的功能，下面的代码能够提供这样的功能。

头文件`PointerPrinter.h`
{% highlight cpp %}
#ifndef __POINTER_PRINTER_H__
#define __POINTER_PRINTER_H__
#include <string>
#include <iostream>
/**
 * Print hex format of a pointer(assuming Little Endian)
 * Usage:
 *	std::cout << PointerPrinter(pointer) << std::endl;
 */
class PointerPrinter {
	public:
		PointerPrinter(const void* p=NULL);
		friend std::ostream& operator<<(std::ostream& os, const PointerPrinter& pp);
	protected:
		const void* _p;
		std::string _str;
};
#endif
{% endhighlight %}

源文件`PointerPrinter.cpp`
{% highlight cpp %}
#include "PointerPrinter.h"
#include <sstream>
PointerPrinter::PointerPrinter(const void* p) : _p(p) {
		unsigned char const *first = reinterpret_cast<unsigned char const*>(&p);
		unsigned char const *last = reinterpret_cast<unsigned char const*>(&p+1);
		int n = last - first;
		if(_p==NULL) {
			_str = "0";
			return;
		}
		int stop = n-1;
		for(int i=n-1;i>=0;--i) {
			if((int)*(first+i)!=0) {
				stop = i;
				break;
			}
		}
		std::ostringstream oss;
		for(int i=stop;i>=0;--i) {
			oss << std::hex << (int)*(first+i);
		}
		_str = oss.str();
}
std::ostream& operator<<(std::ostream& os, const PointerPrinter& pp) {
	os << "0x" << pp._str;
	return os;
}
{% endhighlight %}

使用方法如下
{% highlight cpp %}
#include "PointerPrinter.h"
int main(int argc, char* argv[]){ 
	int *a = NULL;
	std::cout << PointerPrinter(a) << std::endl;
	int b = 1;
	a = &b;
	std::cout << PointerPrinter(a) << std::endl;
	return 0;
}
{% endhighlight %}

参考文献: [How to print function pointers with cout?](http://stackoverflow.com/questions/2064692/how-to-print-function-pointers-with-cout)

