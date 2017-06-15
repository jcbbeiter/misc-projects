#!/usr/bin/env python2.7

import os

# gets output of ps aux
aux = os.popen('ps aux')

# reads first field (usernames) into a set - this takes care of uniqueness
users = set()
for line in aux:
    users.add(line.split()[0])

# print length of set, which is the number of unique users
print len(users)
