#!/usr/bin/python3

import sys
import os
from os import environ


print('Content-type: text/text\n')

print('Your ip address is: {}'.format((environ['REMOTE_ADDR'])))
