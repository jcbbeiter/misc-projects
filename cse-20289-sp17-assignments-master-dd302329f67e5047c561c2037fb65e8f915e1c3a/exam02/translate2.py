#!/usr/bin/env python2.7

import re
import requests

# Fetch web data and store it as text
URL = 'http://yld.me/aJt?raw=1'
r = requests.get(URL)
text = r.text

# search text for regex (phone numbers ending in odd numbers)
regex = '[0-9]{3}-[0-9]{3}-[0-9]{3}[13579]'
nums =  re.findall(regex,text)

# print matches
for num in nums:
    print num

