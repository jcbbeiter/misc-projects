#!/usr/bin/env python2.7

with open('input/01_input.txt') as f:
    num = f.read().strip()

#sum = 0
#for i in range(0,len(num)):
#    if num[i] == num[(i+1) % len(num)]:
#        sum = sum + int(num[i])
#print "first part: " + str(sum)

#sum = 0
#for i in range(0,len(num)):
#    if num[i] == num[(i + len(num)/2) % len(num)]:
#        sum = sum + int(num[i])
#print "second part: " + str(sum)

# Old more readable solution above, list comprehensions below

sum1 = sum([int(num[i]) for i in range(0,len(num)) if num[i] == num[(i+1)%len(num)]])
print "first part: " + str(sum1)

sum2 = sum([int(num[i]) for i in range(0,len(num)) if 
                                    num[i] == num[(i+len(num)/2)% len(num)]])
print "second part: " + str(sum2)
