---
comments: true
layout: blog
title: Null Ostream Class in C++
---

# Code 

{% highlight cpp %}
#include <iostream>
class NulStreambuf : public std::streambuf
{
    char                dummyBuffer[ 64 ];
protected:
    virtual int         overflow( int c ) 
    {
        setp( dummyBuffer, dummyBuffer + sizeof( dummyBuffer ) );
        return (c == traits_type::eof()) ? '\0' : c;
    }
};
class NulOStream : private NulStreambuf, public std::ostream
{
public:
    NulOStream() : std::ostream( this ) {}
    NulStreambuf* rdbuf() { return this; }
};
{% endlighlight %}

# Reference 

  * [is there a null stdostream implementation in c++ or libraries](http://stackoverflow.com/questions/8243743/is-there-a-null-stdostream-implementation-in-c-or-libraries/8244052#8244052)

