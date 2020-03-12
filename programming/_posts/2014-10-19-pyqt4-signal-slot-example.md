---
layout: blog
comments: true
tags: python PyQt programming
title: PyQt4 signal and slot Example
---

{% highlight python %} 
import PyQt4.QtGui as QtGui
import PyQt4.QtCore as QtCore
class Test(QtCore.QObject):
    # define a signal
    mysignal = QtCore.pyqtSignal(int)
    def __init__(self):
        # IMPORTANT for subclass of QObject
        super(Test, self).__init__()
        # signal-slot connection, 2 methods
        self.mysignal.connect(self.myslot1)
        self.connect(self, QtCore.SIGNAL("mysignal(int)"), self.myslot2)
    # define a slot
    @QtCore.pyqtSlot(int)
    def myslot1(self, num):
        print "myslot1: ", num
    @QtCore.pyqtSlot(int)
    def myslot2(self, num):
        print "myslot2: ", num
class Test2(QtCore.QObject):
    def __init__(self):
        super(Test2, self).__init__()
    @QtCore.pyqtSlot(int)
    def myslot3(self, num):
        print "myslot3: ", num
t = Test()
t2 = Test2()
t.mysignal.connect(t2.myslot3)
t.mysignal.emit(1)
{% endhighlight %}


