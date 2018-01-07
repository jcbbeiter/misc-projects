#!/usr/bin/env python2.7

# First Part

with open('input/05_input.txt') as f:
    jumps = [int(line.strip()) for line in f.readlines()]

steps = 0
pos = 0

while pos < len(jumps):
    next = pos + jumps[pos]
    jumps[pos] = jumps[pos] + 1
    pos = next
    steps = steps+1

print "With initial rules, it takes " + str(steps) + " steps to escape."


# Second part

with open('input/05_input.txt') as f:
    jumps = [int(line.strip()) for line in f.readlines()]

steps = 0
pos = 0

while pos < len(jumps):
    next = pos + jumps[pos]
    if jumps[pos] >= 3:
        jumps[pos] = jumps[pos] - 1
    else:
        jumps[pos] = jumps[pos] + 1
    pos = next
    steps = steps+1

print "With updated rules, it takes " + str(steps) + " steps to escape."
