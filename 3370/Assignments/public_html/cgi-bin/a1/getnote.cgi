#!/usr/bin/python3

import os
import sqlite3
from urllib.parse import unquote_plus


#setup
connection = sqlite3.connect("assignment1.db")
def init_webpage():
    # declare globals so they can be used everywhere
    global header
    global name
    global message
    global link
    global query
    
    # now initialize them for use
    header = 'Something went wrong!'
    message = 'file does not exist!'
    link = 'Click here to try again'
    name = ''
    query = ''
    
    if 'QUERY_STRING' in os.environ:
        if not os.environ['QUERY_STRING'] == query:
            k, query = os.environ['QUERY_STRING'].split('=')
            if query:
                count = 0
                for row in connection.execute("select count(*) from log where id = (?)", (query,)):
                    count = row[0]
                    if count > 0:
                        header = 'This message will disappear after this!'
                        for row in connection.execute("select name from log where id = (?)", (query,)):
                            name ='Message from '+ unquote_plus(row[0]) + '!'
                        for row in connection.execute("select message from log where id = (?)", (query,)):
                            message = 'Message: ' + unquote_plus(row[0])
                        link = 'Go home'
                        burn_note(query)
    

# notes is gone for good     
def burn_note(query):
    connection.execute("delete from log where id = (?)",(query,))
    connection.commit()

# code begins here
init_webpage()

print("Content-type:text/html\r\n\r\n")
print('<html>')
print('<head>')
print('<title></title>')
print('</head>')
print('<body>')
print('<h2> {} </h2>'.format(header))
print('<p> {} </p>'.format(name))
print('<p> {} </p>'.format(message))
print('<a href="https://www-test.cs.umanitoba.ca/~hamptone/cgi-bin/a1/index.cgi">{}</a>'.format(link))
print('</body>')
print('</html>')
connection.close()

