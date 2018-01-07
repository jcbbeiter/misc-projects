#!/usr/bin/env python2.7

from collections import Counter

reg = Counter()

highest_val = 0

with open('input/08_input.txt') as f:
    for line in f.readlines():
        [op_reg, op, val, if_word, cmp_reg, cmp_op, cmp_val] = line.strip().split()
        if cmp_op == '>':
            if reg[cmp_reg] <= int(cmp_val):
                continue
        elif cmp_op == '>=':
            if reg[cmp_reg] < int(cmp_val):
                continue
        elif cmp_op == '<':
            if reg[cmp_reg] >= int(cmp_val):
                continue
        elif cmp_op == '<=':
            if reg[cmp_reg] > int(cmp_val):
                continue
        elif cmp_op == '==':
            if reg[cmp_reg] != int(cmp_val):
                continue
        elif cmp_op == '!=':
            if reg[cmp_reg] == int(cmp_val):
                continue

        if op == 'inc':
            reg[op_reg] = reg[op_reg] + int(val)
        else:
            reg[op_reg] = reg[op_reg] - int(val)

        if reg[op_reg] > highest_val:
            highest_val = reg[op_reg]

print "The highest register value after operation is " + str(max(reg.values()))
print "The highest register value during operation was " + str(highest_val)
