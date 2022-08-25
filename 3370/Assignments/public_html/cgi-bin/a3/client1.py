# Echo client program
import socket
import json
import sys 
import uuid
import select

serversocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# non-blocking, so that select can deal with the multiplexing
serversocket.setblocking(False)

# bind the socket to a public host, and a well-known port
global hostname 
global host
global myPort
global ip 

hostname = socket.gethostname()
host = "The Chosen on " + hostname
myPort = 55556
ip = socket.gethostbyname(hostname)
def init_dictionaries():
    consensus = {}
  


    consensus_r = {}
    query = {}
    query_r = {}
    flood = { "command": "FLOOD",
  "host": "",
  "port": "",
  "name": "",
  "messageID": "90062caa-2bb9-4ba5-bc3d-d8bd627986d6"}
    flood_r = {
  "command": "FLOOD-REPLY",
  "host": "130.179.28.113",
  "port": 16000,
  "name": "Name of replying peer!"}
    SET = {}
    SET_R = {}

    return consensus, consensus_r,query,query_r,flood,flood_r,SET,SET_R

def flood_reply(data, flood_r):
  #prepare flood reply
  
  flood_r['host'] = data['host']
  flood_r['port'] = data['port']
  flood_r['name'] = host
  
  #flood is a dictionary
  reply = json.dumps(flood_r).encode('utf_8')
  print(reply)
  return reply



  

consensus, consensus_r, query,query_r,flood,flood_r,SET,SET_R = init_dictionaries()
flood['host'] = ip
flood['port'] = myPort
flood['name'] = host
HOST = 'heron.cs.umanitoba.ca'    # The remote host
PORT = 16000 # The same port as used by the server

#x = '{"command": "FLOOD", "host": "130.179.28.51", "port": 16000, "name": "Me!", "messageID": "90062caa-2bb9-4ba5-bc3d-d8bd627986d6"}'
#x = '{"command": "FLOOD", "host": "127.0.0.1", "port": 42000, "name": "Me!", "messageID": "90062caa-2bb9-4ba5-bc3d-d8bd627986d6"}'
#x= '{"command": "QUERY"}'
x = {
  "command": "FLOOD",
  "host": "130.179.28.123",
  "port": 5555,
  "name": "Me!",
  "messageID": "90062caa-2bb9-4ba5-bc3d-d8bd627986d6"}
y = json.dumps(x).encode('utf-8')
#print(y)

#print(consensus)

y =json.dumps(flood).encode('utf_8')
print(y)

serversocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# non-blocking, so that select can deal with the multiplexing
serversocket.setblocking(False)

# bind the socket to a public host, and a well-known port
hostname = socket.gethostname()
host = socket.gethostbyname(hostname)
print("listening on interface " + hostname)
# This accepts a tuple...
serversocket.bind((socket.gethostname(), myPort))
print("host = " +host)
# also listen on local
localsocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# non-blocking, so that select can deal with the multiplexing
localsocket.setblocking(False)
# This accepts a tuple...
localsocket.bind(('127.0.0.1', 42000))

inputs = [serversocket, localsocket]
outputs = [] # None

addr1 = (HOST, PORT)
serversocket.sendto(y, addr1)
while True: #FOREVAR 
  try:
    
    print("waiting for input")
    readable, writable, exceptional = select.select(inputs, outputs, inputs)
    # Read what we can, from where we can
    for source in readable:
      data, addr = source.recvfrom(1024)
      if source is localsocket:
        print("heard locally:")
      elif source is serversocket:
        print("heard externally:")
        data = data.decode('UTF-8')
        data = json.loads(data)
        reply_back = ''
        if "FLOOD" in data.keys:
          #send flood reply
          reply_back = flood_reply(data, flood_r)
      print(data)
      # just say something
      print("Connection from:")
      print(addr)


  except KeyboardInterrupt:
    print("I guess I'll just die")
    serversocket.close()
    localsocket.close()
    sys.exit(0)
  except Exception as e:
    print("SOMETHING IS BAD")
    print(e)

