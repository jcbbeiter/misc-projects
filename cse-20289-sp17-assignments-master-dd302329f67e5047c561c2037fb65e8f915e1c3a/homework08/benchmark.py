#!/usr/bin/env python2.7

import subprocess
import os
import sys

def dotest(size,load):
    cmd =  os.popen('shuf -i1-' + str(size) + ' -n ' + str(size) + ' | ./measure ./freq -l ' + str(load) + ' 2>&1 > /dev/null')
    results = cmd.read().split()
    time = results[0]
    memory = results[2]

    print '| ' + str(size).rjust(10) + ' |',
    print str(load).rjust(10) + ' |',
    print str(round(float(time),2)).rjust(10) + ' |',
    print str(round(float(memory),2)).rjust(10) + ' |'


print "|   NITEMS   |    ALPHA   |    TIME    |   SPACE    |"
print "| ---------- | ---------- | ---------- | ---------- |"

sizes = [10**pow for pow in range(0,8)]
loads = [0.5,0.75,0.9,1.0,2.0,4.0,8.0,16.0]

for size in sizes:
    for load in loads:
	dotest(size,load)
