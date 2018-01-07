#!/usr/bin/env python2.7
from collections import Counter

count = 0
with open('input/04_input.txt') as f:
    for line in f.readlines():
        wordCounts = Counter(line.strip().split(' '))
        if max(wordCounts.values()) == 1:
            count = count + 1

print str(count) + " lines have no repeated words"

count = 0
with open('input/04_input.txt') as f:
    for line in f.readlines():
        words = [''.join(sorted(word)) for word in line.strip().split(' ')]
        wordCounts = Counter(words)
        if max(wordCounts.values()) == 1:
            count = count + 1

print str(count) + " lines have no repeated anagrams"
