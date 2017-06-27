#!/usr/bin/env python2.7

import requests

def query(key):
    r = requests.get(url + ''.join(key))
    return r.text

url = 'https://ggpuzzles.appspot.com/disarm?key='

key = ['0'] * 128

# crack each digit sequentially
for i in range(0,128):
    print i,
    # check number wrong when digit is 0 or 1
    initial = query(key)
    key[i] = '1'
    after = query(key)
    # if fewer were wrong with 0, it's zero
    if(initial < after):
        key[i] = '0'
        print ' = ' + key[i]
        continue
    # if fewer with 1, it's one
    elif initial > after :
        print ' = ' + key[i]
        continue
    # otherwise, increase until we find it
    else:
        while(initial == after):
            key[i] = str(int(key[i])+1)
            after = query(key)
        print ' = ' + key[i]
print ''.join(key)


