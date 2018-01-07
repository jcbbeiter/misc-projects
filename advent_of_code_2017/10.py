#!/usr/bin/env python2.7

with open('input/10_input.txt') as f:
    lengths = [int(num) for num in f.read().strip().split(',')]

nums = [i for i in range(0,256)]

skip = 0
pos = 0

for length in lengths:
    flip = []
    for i in range(0,length):
        flip.append(nums[(pos+i)%len(nums)])
    flip = list(reversed(flip))
    for i in range(0,length):
        nums[(pos+i)%len(nums)] = flip[i]

    pos = (pos + skip + length) % len(nums)
    skip = skip + 1
    
print "The product of the first two elements is " + str(nums[0]*nums[1])

# Second part

with open('input/10_input.txt') as f:
    values = [ord(char) for char in f.read().strip()] + [17,31,73,47,23]

nums = [i for i in range(0,256)]

skip = 0
pos = 0

for i in range(0,64):
    for length in values:
        flip = []
        for i in range(0,length):
            flip.append(nums[(pos+i)%len(nums)])
        flip = list(reversed(flip))
        for i in range(0,length):
            nums[(pos+i)%len(nums)] = flip[i]

        pos = (pos + skip + length) % len(nums)
        skip = skip + 1

dense = []

for block in range(0,16):
    xor_sum = nums[16*block]
    for i in range(1,16):
        xor_sum = xor_sum ^ nums[16*block+i]
    dense.append(xor_sum)
    
hash = [format(num,'02x') for num in dense]
print "The Knot Hash is",''.join(hash)
