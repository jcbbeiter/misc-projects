#!/usr/bin/env python2.7

import sys

def evens(stream):
    for number in stream:
        if int(number)%2 == 0:
            yield number.rstrip()

print ' '.join(evens(sys.stdin))
