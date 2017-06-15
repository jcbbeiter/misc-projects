#!/usr/bin/env python2.7

import subprocess
import os

def dotest(size,quick):
    if(quick):
        flags = '-n -q'
    else:
        flags = '-n'
    cmd =  os.popen('shuf -i1-' + str(size) + ' -n ' + str(size) + ' | ./measure ./lsort ' + flags +' | tail -n 1')
    results = cmd.read().split()
    time = results[0]
    memory = results[2]

    print '| ' + str(size).ljust(9) + '|',
    if(quick):
        print " Quick   |",
    else:
        print " Merge   |",
    print str(time).ljust(10) + '|',
    print str(memory).ljust(10) + '|'


print "| NITEMS   | SORT     | TIME (s)  | SPACE (Mb)|"
print "| -------- | -------- | --------- | --------- |"

sizes = [10**pow for pow in range(0,8)]

for size in sizes:
    dotest(size,0)
    dotest(size,1)
