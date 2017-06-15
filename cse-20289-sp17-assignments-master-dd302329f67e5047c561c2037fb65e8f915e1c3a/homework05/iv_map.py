#!/usr/bin/env python2.7

import sys


for num, line in enumerate(sys.stdin):
    # Make everything lowercase and trim unwanted chars
    line = [char.lower() for char in line if char.lower() in 'abcdefghijklmnopqrstuvwxyz-' or char.isspace()]
    # Split line into words
    words =  (''.join(line)).split(' ')
    # remove all whitespace and blank elements
    words = [word.rstrip() for word in words if len(word.rstrip()) >0]
    # print words and numbers in Hadoop Streaming format
    for word in words:
        print (word + '\t' + str(num+1))
