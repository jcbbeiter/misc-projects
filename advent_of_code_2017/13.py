#!/usr/bin/env python2.7

import itertools

# Old, more readable way
def old_solution(scanners):

    # OLD
    severity = 0
    for t in scanners.keys():
        if t % (2*(scanners[t]-1)) == 0:
            severity = severity + t*scanners[t]
    print "The severity of the trip is",severity

    # Second part

    delay = 0

    caught = True
    while caught:
        delay = delay + 1
        caught = False
        for depth in scanners.keys():
            if (delay+depth) % (2*(scanners[depth]-1)) == 0:
                caught = True
                break
    print "The shortest delay to make it through uncaught is",delay

# Second, more one-linery try

def new_solution(scanners):
    severity = sum(d*scanners[d] for d in scanners.keys() if d%(2*(scanners[d]-1)) == 0)
    print "The severity of the trip is",severity

    # Second part

    delay = next(delay for delay in itertools.count() if not any((delay+d)%(2*(scanners[d]-1)) == 0 for d in scanners.keys()))
    print "The shortest delay to make it through uncaught is",delay



if __name__ == '__main__':
    scanners = {}
    with open('input/13_input.txt') as f:
        for line in f.readlines():
            [d, r] = [int(n.strip()) for n in line.split(':')]
            scanners[d] = r
    new_solution(scanners)

