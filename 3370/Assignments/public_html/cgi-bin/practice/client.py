# Echo client program
import socket

HOST = 'cormorant.cs.umanitoba.ca'    # The remote host
PORT = 8998 # The same port as used by the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'itsa me mario')
    data = s.recv(1024)
print('Received', repr(data))

