#!/usr/bin/env python2.7

import requests

def query(key):
    r = requests.get(url + ''.join(key))
    return r.text

url = 'https://ggpuzzles.appspot.com/disarm?key='

key = ['0']
for _ in range (0,127):
    key.append('0')

for i in range(0,128):
    print i,
    initial = query(key)
    key[i] = '1'
    after = query(key)
    if(initial < after):
        key[i] = '0'
        print ' = ' + key[i]
        continue
    elif initial > after :
        print ' = ' + key[i]
        continue
    else:
        while(initial == after):
            key[i] = str(int(key[i])+1)
            after = query(key)
        print ' = ' + key[i]
print ''.join(key)


