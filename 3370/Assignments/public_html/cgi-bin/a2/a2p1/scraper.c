#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netdb.h> //For get addrinfo
#include <unistd.h> //for close
#include <stdlib.h> //for exit
#include <assert.h>

int post_request(char *key, char *content_length, char *name, char *message );
int get_request(char *key, char *name, char *message, int pass);
int main(int argc, char *argv[])
{
    int content_length = 15;
    char *name;
    char message[200];

    // check for more than 2 args
    if(argc <= 2) {
        printf("Please add more arguments and try again");
    }
    else{
        printf("Processing Arguments\n");
        name = argv[1];
        for(int i = 2; i< argc; i++) {
            strcat(message, argv[i]);
            strcat(message, " ");
        }
        // increase content length but convert it to a str
        content_length = content_length + strlen(name) + strlen(message);
        char buffer[5];
        sprintf(buffer, "%d", content_length);

        char *key = malloc(13*sizeof(char));
        printf("Complete\n");

        printf("Posting response with \nName: %s \nMessage: %s\n\n" ,name, message);
        post_request(key, buffer, name, message);
        printf("Complete\n");

        int pass = 1;
        printf("The Key is %s\n\n", key);

        printf("Requesting GET using the key\n\n");
        get_request(key, name,message, pass);
        printf("Complete\n");
        pass++;
        printf("Requesting GET using key with burned message\n\n");
        get_request(key,name,message, pass);
        printf("Complete\n");
        free(key);
    }

    printf("\nProcess Complete\n ");
    return 0;
}
int post_request(char *key, char *content_length, char *name, char *message ){

    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000];
    char address[100];

    struct addrinfo *result;

    // Clean buffers:
    memset(server_message,'\0',sizeof(server_message));


    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }

    printf("Socket created successfully\n");

    struct addrinfo hints;
    memset(&hints, 0 , sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_CANONNAME;

    // get the ip of the page we want to scrape
    int out = getaddrinfo ("www-test.cs.umanitoba.ca",NULL, &hints, &result);

    if(out != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(out));
        exit(EXIT_FAILURE);
    }

    // ai_addr is a struct sockaddr
    // so, we can just use that sin_addr
    struct sockaddr_in *serverDetails = (struct sockaddr_in *)result->ai_addr;

    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    server_addr.sin_addr = serverDetails->sin_addr;

    // convert to octets
    printf("Convert...\n");
    inet_ntop(server_addr.sin_family, &server_addr.sin_addr, address, 100);
    printf("Connecting to %s\n", address);

    // Send connection request to server:
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        printf("Unable to connect\n");
        exit(EXIT_FAILURE);
    }
    printf("Connected with server successfully\n");

    // Parse request (this is messy)
    char content_len[200];
    strcat(content_len,"Content-Length:");
    strcat(content_len, content_length);
    strcat(content_len, "\r\n\r\n");
    char post_body[200];
    strcat(post_body, "name=");
    strcat(post_body, name);
    strcat(post_body, "&message=");
    strcat(post_body, message);
    strcat(post_body, "\r\n\r\n");
    char part1[] = "POST /~hamptone/cgi-bin/a1/createnote.cgi HTTP/1.1\r\nHost: www-test.cs.umanitoba.ca\r\nContent-Type: application/x-www-form-urlencoded\r\n";
    char request[20000];
    strcat(request, part1);
    strcat(request, content_len);
    strcat(request, post_body);

    // Send the message to server:
    if(send(socket_desc, request, strlen(request), 0) < 0){
        printf("Unable to send message\n");
        return -1;
    }

    // Receive the server's response:
    if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
        printf("Error while receiving server's msg\n");
        return -1;
    }

    // Close the socket:
    close(socket_desc);

    // check for success
    printf("\nChecking successful response\n");
    char check_success[] = "HTTP/1.1 200 OK";
    assert(strstr(server_message, check_success)!= NULL);
    printf("Successful 200 response\n\n");

    // save key
    if(strstr(server_message, "temp") !=NULL){
      char *p = strstr(server_message, "temp");
      memcpy(key,p, 12);
    }

    return 0;
}
int get_request(char *key, char *name, char *message, int pass){

    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000];
    char address[100];

    struct addrinfo *result;

    // Clean buffers:
    memset(server_message,'\0',sizeof(server_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }

    printf("Socket created successfully\n");

    struct addrinfo hints;
    memset(&hints, 0 , sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_CANONNAME;

    //get the ip of the page we want to scrape
    int out = getaddrinfo ("www-test.cs.umanitoba.ca",NULL, &hints, &result);
    // fail gracefully

    if(out != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(out));
        exit(EXIT_FAILURE);
    }

    // ai_addr is a struct sockaddr
    // so, we can just use that sin_addr
    struct sockaddr_in *serverDetails = (struct sockaddr_in *)result->ai_addr;

    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    server_addr.sin_addr = serverDetails->sin_addr;

    //convert to octets
    printf("Convert...\n");
    inet_ntop(server_addr.sin_family, &server_addr.sin_addr, address, 100);
    printf("Connecting to %s\n", address);

    //Send connection request to server:
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        printf("Unable to connect\n");
        exit(EXIT_FAILURE);
    }
    printf("Connected with server successfully\n");

    // parse GET request
    char part1[] = "GET /~hamptone/cgi-bin/a1/getnote.cgi?key=";
    char part2[] = " HTTP/1.1\r\nHost: www-test.cs.umanitoba.ca\r\n\r\n";
    char request[20000];
    strcat(request,part1);
    strcat(request,key);
    strcat(request,part2);

    // Send the message to server:
    if(send(socket_desc, request, strlen(request), 0) < 0){
        printf("Unable to send message\n");
        return -1;
    }

    // Receive the server's response:
    if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
        printf("Error while receiving server's msg\n");
        return -1;
    }

    // Close the socket:
    close(socket_desc);

    //check for success
    char check_success[] = "HTTP/1.1 200 OK";

    // pass one check for message inside server_message
    // pass 2 check that message is NOT inside server_message
    if(pass==1){
        printf("\nChecking successful response and if name and message is in dataset\n");
        assert(strstr(server_message, check_success)!= NULL);
        assert(strstr(server_message, message) != NULL);
        assert(strstr(server_message, name) != NULL);
        printf("Successful 200 and message and name found!\n\n");
    }
    else if(pass == 2){
        printf("\nChecking successful response and if message is NOT in dataset\n");
        assert(strstr(server_message, check_success)!= NULL);
        assert(strstr(server_message,message) == NULL);
        assert(strstr(server_message,name) == NULL);
        printf("Successful 200 and message and name NOT found!\n\n");
    }

    return 0;
}