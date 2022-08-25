#!/usr/bin/python3

import os
import sys
import re
import random
import tempfile
import sqlite3
from urllib.parse import unquote_plus



# constants
link = 'http://www-test.cs.umanitoba.ca/~robg/cgi-bin/3010/a1/getnote.cgi?key='
key ='abcdefghijklmnopqrstuvwxyz1234567890'
redirect = 'Go home'
name = ''
message = ''
connection = sqlite3.connect("assignment1.db")
# initialize a database table
def init_sql_table():
    
    
    #id = is the temp key
    #name = the name of the poster
    #message = the message
    connection.execute ("""
        Create table if not exists log(
        id text PRIMARY KEY,
	    name text NOT NULL,
        message text NOT NULL
        );
    """)

# if user wants to create note a tracking cookie will be created and updating
def init_cookie():

  COOKIE={}
  messages = 'message'
  number = 1 
  
  if 'HTTP_COOKIE' in os.environ:
    cookies = os.environ['HTTP_COOKIE'].split(';')
    for i in cookies:
      i, v=i.split('=',1)
      COOKIE[i]=v
      
  #if tracking cookie does not exists... Create! if it does increment it
  if messages in COOKIE:
    number = int(COOKIE['message'])
    number = number+1
  print('Set-Cookie: message = {}'.format(str(number)))
  return number

# get post params and return it.
def get_post():
  POST={}
  something = sys.stdin.read().split('&')
  for param in something: 
      k = param.split('=')
      POST[k[0]]=k[1]
  return POST

# distributes a key
def process_key():    
    key ='abcdefghijklmnopqrstuvwxyz1234567890'
    temp = 'temp'
    for i in range(8):
        temp += ''.join(random.choice(key))
    return temp

# inserts not into database
def exe_sql(temp, name, message):
    # add the new entry
    connection.execute("insert into log(id,name,message) values (?,?,?)", (temp,name, message))
    connection.commit()
    connection.close()

def save_message():
  print('Content-type:text/html\r\n\r\n')
  print('<html>')
  print('<head>')
  print('<title>Eriq Hampton Assignment 1</title>')
  print('</head>')
  print('<body>')
  print('<p>')
  print('The key for you note is {}'.format(temp))
  print('<p> Or give them this link: http://www-test.cs.umanitoba.ca/~hamptone/cgi-bin/a1/getnote.cgi?key={}</p>'.format(temp))
  print('<p> you have made {} notes</p>'.format(notes_created))
  print('<a href="https://www-test.cs.umanitoba.ca/~hamptone/cgi-bin/a1/index.cgi">{}</a>'.format(redirect))
  print('</p>')
  print('</body>')
  print('</html>')

# code begins here
init_sql_table()
temp = process_key()
POST={}

# checks if request was a post
if os.environ['REQUEST_METHOD'] == 'POST':
  POST = get_post()

# check params in POST and print the info
if 'name' in POST and 'message' in POST:
  name = POST['name']
  message = POST['message']
  exe_sql(temp, name, message)
  notes_created = str(init_cookie())
  save_message()

# else print a blank page
else: 
  print('Content-type:text/html\r\n\r\n')
