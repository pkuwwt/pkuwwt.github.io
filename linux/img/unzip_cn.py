#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import zipfile

#print "Processing File " + sys.argv[1]

def unzip_file(f):
    _file=zipfile.ZipFile(f,"r");
    for name in _file.namelist():
        utf8name=name.decode('gbk')
        if os.name == 'posix':
            print "Extracting " + utf8name
        pathname = os.path.dirname(utf8name)
        if not os.path.exists(pathname) and pathname!= "":
            os.makedirs(pathname)
        data = _file.read(name)
        if not os.path.exists(utf8name):
            fo = open(utf8name, "w")
            fo.write(data)
            fo.close
    _file.close()
    
def main():
    if len(sys.argv)==1:
        print 'USAGE: %s input.zip' % sys.argv[0]
        return
    unzip_file(sys.argv[1])

if __name__ == '__main__':
    main()

