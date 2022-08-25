#!/usr/bin/python3

import sys
import os
from os import environ

import sqlite3

connection = sqlite3.connect("some_file1.db")
connection.execute ("""
    Create table if not exists log(
      the_ip text
    );
""")

# add the new entry
connection.execute("insert into log(the_ip) values (?)", (environ['HTTP_COOKIE'],))

connection.commit()

count = 0
for row in connection.execute("select count(*) from log"):
    count = row[0]


print('Content-type: text/html\n')


print('<html>')
print('<body>')
print('<h1>who am i</h1>')
print('<p>Your cookie is : {}</p>'.format(environ['HTTP_COOKIE']))
print('<p>total visits: {}</p>'.format(count))
print("<p>all visits</p>")
print("<ul>")
for row in connection.execute("select * from log"):
    print("<li>{}</li>".format(row[0]))
print("</ul>")
print('</body>')

print('</html>')

connection.close()
