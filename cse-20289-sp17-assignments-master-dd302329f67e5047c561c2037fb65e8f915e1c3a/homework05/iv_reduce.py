#!/usr/bin/env python2.7

import sys

reduced = {}

for line in sys.stdin:
    # reads key/num pair
    key, num = line.split()
    # if this entry already exists
    if key in reduced.keys():
        # only add line number if it's not already there
        if num not in reduced[key]:
            reduced[key].add(num)
    # otherwise, add new key entry
    else:
        reduced[key] = set([num])

# print alphabetized output
for key in sorted(reduced):
    print (key + '\t' + ' '.join(sorted(reduced[key],key=int)))

