#!/usr/bin/env python2.7

def even_division(nums):
    for i in range(0,len(nums)):
        for j in range(i+1,len(nums)):
            if nums[i] % nums[j] == 0:
                return nums[i]/nums[j]
            if nums[j] % nums[i] == 0:
                return nums[j]/nums[i]

sum = 0
with open('input/02_input.txt') as f:
    for line in f:
        nums = [int(num) for num in line.split()]
        sum = sum + max(nums) - min(nums)

print "first checksum is " + str(sum)

sum = 0
with open('input/02_input.txt') as f:
    for line in f:
        nums = [int(num) for num in line.split()]
        sum = sum + even_division(nums)

print "second checksum is " + str(sum)

