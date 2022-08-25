import sqlite3

# connects to, or creates the file
connection = sqlite3.connect("some_file.db")

# For your application, you can assume the file is already
# created. Or, you can be clever:
connection.execute ("""
    Create table if not exists notes (
      note_id integer primary key autoincrement,
      owner text,
      note text
    );
""")

# Add some data
name = "Bob the angry Flower"
connection.execute("insert into notes(owner, note) values (?,?)", (name, "Punctuation"))

# write it to disk
connection.commit()

# add a whole bunch more
for i in range(40):
    connection.execute("insert into notes(owner, note) values (?,?)", (name, "more stuff {:d}".format(i)))

# now read it
# note the funky , after name. It makes sure that python forces the
# brackets () to be interpreted as "make me a tuple"
for row in connection.execute("select owner, note from notes where owner=?", (name,)):
    # this returns a tuple with 2 pieces
    print("Hi, my name is {} and I said >{}<".format(row[0], row[1]))

# end the connection
connection.close()
