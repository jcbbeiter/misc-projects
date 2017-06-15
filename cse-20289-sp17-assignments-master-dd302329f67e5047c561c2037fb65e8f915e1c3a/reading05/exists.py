#!/usr/bin/env python2.7

import sys
import os

outcode = 0

if(len(sys.argv) == 1):
    print("Error: please provide 1 or more files to check for.")
    sys.exit(1)

for arg in sys.argv[1:]:
    if(arg in os.listdir(os.curdir)):
        print(arg + " exists!")
    else:
        print(arg + " does not exist!")
        outcode = 1

sys.exit(outcode)
