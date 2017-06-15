#!/usr/bin/env python2.7

import sys

print ' '.join(filter(lambda x: int(x)%2 == 0,[number.rstrip() for number in sys.stdin]))
