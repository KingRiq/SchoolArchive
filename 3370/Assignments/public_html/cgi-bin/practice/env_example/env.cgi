#!/usr/bin/python3

import sys
import os
from os import environ


print('''Content-type: text/text

{:}
'''.format(dict(environ)))
