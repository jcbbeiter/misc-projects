#!/usr/bin/env python2.7

import math

# learned about hexes from https://www.redblobgames.com/grids/hexagons/!

with open('input/11_input.txt') as f:
    path = [word for word in f.read().strip().split(',')]


x = 0
y = 0
z = 0
furthest = 0
for step in path:
    if step == 'n':
        y = y + 1
        z = z - 1
    elif step == 's':
        y = y - 1
        z = z + 1
    elif step == 'nw':
        x = x - 1
        y = y + 1
    elif step == 'se':
        x = x + 1
        y = y - 1
    elif step == 'ne':
        x = x + 1
        z = z - 1
    elif step == 'sw':
        x = x - 1
        z = z + 1
    furthest = max(furthest,max(abs(x),abs(y),abs(z)))
print "It will take",max(abs(x),abs(y),abs(z)),"steps to reach the child process."
print "The furthest away he ever got was",furthest,"steps."
