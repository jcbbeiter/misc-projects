#!/usr/bin/env python2.7

from collections import defaultdict

edges = defaultdict(lambda: set())

with open('input/12_input.txt') as f:
    for line in f.readlines():
        words =  line.replace(',',' ').strip().split()
        for i in range(2,len(words)):
            edges[words[0]].add(words[i])

marked = set()
frontier = []
frontier.append('0')

while len(frontier) > 0:
    curr = frontier.pop(0)
    marked.add(curr)
    for next in edges[curr]:
        if next not in marked:
            frontier.append(next)
print "There are", len(marked), "programs in the group that contains PID 0."

# Second part

groups = 1
while len(marked) < len(edges):
    if len(frontier) == 0:
        groups = groups + 1
        for node in edges.keys():
            if node not in marked:
                frontier.append(node)
                break
    curr = frontier.pop(0)
    marked.add(curr)
    for next in edges[curr]:
        if next not in marked:
            frontier.append(next)
print "There are", groups, "groups of programs."
