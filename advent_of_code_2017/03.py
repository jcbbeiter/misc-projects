#!/usr/bin/env python2.7

import math

# First part

nums = [12, 23, 1024, 368078]

for num in nums:
    factor = 1
    while num > factor**2:
        factor = factor + 2

    largest = factor**2
    smallest = (factor-2)**2
    ring = (factor-1)/2
    ordinal = (num-smallest)%(2*ring)
    diff = ring-ordinal if ordinal < ring else ordinal-ring
    distance = ring+diff

    print "Data from square " + str(num) + " is carried " + str(distance) + " squares"

# For the second part -- this sequence is documented on OEIS!
# https://oeis.org/A141481/b141481.txt
# Lazy lookup
