import socket
import sys
import select
import time
global HOST
global PORT

if(len(sys.argv) < 3):
  print('not enough args')
  sys.exit(0)

print(len(sys.argv))
PORT = sys.argv[1]

print(PORT)

global WORKERNUM
WORKERNUM = len(sys.argv) - 2


print (WORKERNUM)

# LOCAL HOST for now
HOST = "127.0.0.1"  # The server's hostname or IP address

# ARGV[1]
PORT = int(sys.argv[1]) # The same port as used by the server


def getWorkers():
  print(sys.argv)
  somelist = []
  for num in range(WORKERNUM):
    parts = sys.argv[num+2].split(':')
    somelist.append((parts[0], parts[1]))
  return somelist
  
#HOST = socket.gethostbyname(hostname)    # The remote host

LISTOFWORKERS = [getWorkers()]
print(HOST,PORT)
print(LISTOFWORKERS)



'''with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.settimeout(1)
    s.sendall(b'did this work?')
    data = s.recvfrom(1024)
print('Received', repr(data))'''



'''
server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# https://docs.python.org/3/library/socket.html#notes-on-socket-timeouts
server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# overall timeout
server_sock.setblocking(False)
server_sock.bind((HOST, PORT))
server_sock.listen()

# list of current clients
myClients = []

while True:
    try:
        #block!
        readable, writable, error = select.select(
                    [server_sock, ] + myClients, [], [])

        for aSocket in readable:
            if aSocket is server_sock:
                conn, addr = server_sock.accept()
            
                print('Request from', addr)
                #print('Timeout set to 60')
                conn.settimeout(1)
                print('Timeout set to', conn.gettimeout())
                # I can set a timeout here, for the client socket, too.
                #conn.setblocking(False)
                myClients.append(conn)
                #conn.sendall(data)
        
            else: # must be in a client socket
                data = aSocket.recv(1024)
                time.sleep(4)
                print(aSocket.gettimeout())
                
                asText = data.decode('utf-8')
                # is it done?
                if len(data) == 0:
                    myClients.remove(aSocket)
                    aSocket.close()
                elif asText.strip() == "exit":
                    # also close
                    print('exit')
                    myClients.remove(aSocket)
                    aSocket.close()
                else:
                    # send to everyone
                    for c in myClients:
                        print('telling friends')
                        c.sendall(data)


                    # pretty print 
                    # json.dumps(myObj, indent=2)
    except socket.timeout as e:
        #print('timeout')
        pass
    except KeyboardInterrupt as e:
        print("RIP")
        server_sock.close()
        sys.exit(0)
    except Exception as e:
        print("Something happened... I guess...")
        print(e)
        '''