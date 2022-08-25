# Echo client program
import socket
import json
import sys 
HOST = 'silicon.cs.umanitoba.ca'    # The remote host
PORT = 16000 # The same port as used by the server
#x = '{"command": "FLOOD", "host": "130.179.28.51", "port": 16000, "name": "Me!", "messageID": "90062caa-2bb9-4ba5-bc3d-d8bd627986d6"}'
#x = '{"command": "FLOOD", "host": "127.0.0.1", "port": 42000, "name": "Me!", "messageID": "90062caa-2bb9-4ba5-bc3d-d8bd627986d6"}'
#x= '{"command": "QUERY"}'
x = {
  "command": "FLOOD",
  "host": "130.179.28.125",
  "port": 55558,
  "name": "Me!!!",
  "messageID": "90062caa-2bb9-4ba5-bc3d-d8bd627986d6"}
y = json.dumps(x).encode('utf-8')
print(y)

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    addr = (HOST, PORT)
    s.sendto(y, addr)
   # data = s.recv(1024)
   # x = json.loads(data)
#print('Received', repr(data))
#print(x)

'''
echo '{"command": "QUERY"}' | nc -u -w2 silicon.cs.umanitoba.ca 16000'''
