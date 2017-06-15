#!/usr/bin/env python2.7

import re

fields = []

# read /etc/passwd and store the 5th field of each line
with open('/etc/passwd', 'r') as f:
    for line in f.readlines():
        fields.append(line.split(':')[4])

# keep lowercase field iff it has "U/user" in it
fields = [field.lower() for field in fields if re.search('[uU]ser',field)]

# sort and print
for field in sorted(fields):
    print field
