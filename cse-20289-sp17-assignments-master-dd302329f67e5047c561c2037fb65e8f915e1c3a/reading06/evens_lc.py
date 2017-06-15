#!/usr/bin/env python2.7

import sys

print ' '.join([number.rstrip() for number in sys.stdin if int(number)%2 == 0])
