#!/usr/bin/env python2.7

def process(stream):
    garbage = False
    depth = 0
    score = 0
    garbage_count = 0

    i = 0
    while i < len(stream):
        if garbage:
            if stream[i] == '!':
                i = i + 1
            elif stream[i] == '>':
                garbage = False
            else:
                garbage_count = garbage_count + 1
        elif stream[i] == '<':
            garbage = True
        elif stream[i] == '{':
            depth = depth + 1
            score = score + depth
        elif stream[i] == '}':
            depth = depth-1
        i = i + 1
    return [score, garbage_count]

with open('input/09_input.txt') as f:
    stream = f.read().strip()

[score, garbage_count] = process(stream)

print "Total score for all groups in the stream is " + str(score)
print "The stream has " + str(garbage_count) + " non-canceled garbage characters"
