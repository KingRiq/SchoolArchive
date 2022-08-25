import socket
import sys

def process_args(n):
    name = ''
    message = ''
    if(n > 2):
        name = str(sys.argv[1])
        for i in sys.argv[2:n]:
            message += i + ' '
    content_length = int(15)
    content_length = content_length + len(name)+ len(message) 
    return content_length, name, message

def post():
    # create an INET, STREAMing socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # now connect to the web server on port 80 - the normal http port
    s.connect(("www-test.cs.umanitoba.ca", 80))

    s.sendall(b'POST /~hamptone/cgi-bin/a1/createnote.cgi HTTP/1.1\r\nHost: www-test.cs.umanitoba.ca\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length:%d\r\n\r\nname=%s&message=%s\r\n\r\n' % (content_length, name.encode('utf_8'), message.encode('utf_8')))
    data = s.recv(1024)
    print('Response Received!')

    # It's in bytes, convert to text
    data = data.decode("utf-8")
    
    #find the key 
    key = ''
    check = data.find('temp')
    if not check < 0:
        key = data[check:check+12]
    else:
        print('key not found')

    s.close()
    return key, data, check_success

def get(key):
    # create an INET, STREAMing socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # now connect to the web server on port 80 - the normal http port
    s.connect(("www-test.cs.umanitoba.ca", 80))
    s.sendall(b'GET /~hamptone/cgi-bin/a1/getnote.cgi?key=%s HTTP/1.1\r\nHost: www-test.cs.umanitoba.ca\r\n\r\n' % (key.encode('utf_8')))
    data = s.recv(1024)
    print('Response Received!')
    # It's in bytes, convert to text
    data = data.decode("utf-8")
    s.close()
    return data

#constants
n = len(sys.argv)
if n <= 2:
    print('Please add more arguments and try again')
else:
    global name
    global message
    global check_success
    check_success = 'HTTP/1.1 200 OK'

    #process argv
    print("\nProcessing arguements")
    content_length,name,message = process_args(n)
    print("Complete\n")

    #run post
    print('Posting response with \nName: %s \nMessage: %s\n' % (name, message))
    key, data, check_success = post()
    
    # Assert that we got OK
    print('Checking for successful response')
    assert(check_success in data)
    print ('Successful 200 response\n')
    print('Complete \n')
    print('The Key is %s' % key)

    #run GET
    print('Requesting GET using the key')
    data = get(key)
    
    # Assert that we got OK and message is displayed in dataset
    print('Checking successful response and if message and name is in dataset')
    assert(check_success and message and name in data)
    print ('Successful 200 and message and name found!\n')
    print('Complete\n')

    #run get a second time
    print('Requesting GET for message already burned')
    data = get(key)

    # Assert that message is not in our dataset
    print('Checking successful response and if name and message is NOT in dataset')
    assert(check_success in data and name and message not in data)
    print("Successful 200 and message and name NOT found!")
    print('Complete\n')
    print ("\nProcess Complete..\n")
