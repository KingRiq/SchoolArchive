#!/usr/bin/python3

import sys
import os
from os import environ

# create or open a file, that has
# the count (or... database URI would be rad, but...)

count = 0
if os.path.exists("counter.txt"):
  # yay, read it
  try: 
    with open("counter.txt") as f:
      numStr = f.read()
      count = int(numStr.strip()) 
      # self-closes, but...
      f.close()
  except:
    # why are we here? bad int, file messed up?
    # fact: I don't care... but I don't want to
    # crash
    pass
else:
  # it's not there...
  # ... No else needed? Already set count = 0
  pass

# we have a count... count++
count = count + 1

# write it back to the file
# should have try?
with open("counter.txt", "w") as f:
  f.write(str(count))
  f.close()

print('''Content-type: text/text

{:d}
'''.format(count))
