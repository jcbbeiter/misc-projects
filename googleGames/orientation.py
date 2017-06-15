#!/usr/bin/env python2.7

def operate(nums):
    newset = set()
    for element in nums:
        newset.add(3*element)
        newset.add(5+element)
        newset.add(int(str(element)[::-1]))

    return newset

nums = {100}
for _ in range(0,16):
    nums =  operate(nums)
print "did 16"

last = operate(nums)
print "did 17"

print [element for element in last if element not in nums and len(str(element)) == 4]

