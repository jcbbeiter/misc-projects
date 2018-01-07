#!/usr/bin/env python2.7

def rec(blocks):
    return '|'.join([str(num) for num in blocks])

with open('input/06_input.txt') as f:
    blocks = [int(num) for num in f.read().split()]

history = set()
sizes = {}

count = 0
while rec(blocks) not in history:
    count = count + 1
    history.add(rec(blocks))
    sizes[rec(blocks)] = count

    m = max(blocks)
    start_index = 0
    while blocks[start_index] != m:
        start_index = start_index + 1

    group = blocks[start_index]
    blocks[start_index] = 0
    i = start_index
    while group > 0:
        i = (i + 1) % len(blocks)
        group = group - 1
        blocks[i] = blocks[i] + 1

print str(count) + " cycles until a configuration is repeated."
print "The size of the resulting loop is " + str(count - sizes[rec(blocks)] + 1) + "."
