#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include <stdlib.h>

#define RCVBUFSIZE 2048   /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket, char* rootDirName)
{
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */

    // initialize arrays and pointers
    char* first_word_in_header;
    char* file_to_look_for;
    char* directory;
    char header[256];
    char content_type[1024];
    char* content_type1;    
    
    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");

    // find the file requested from the echo buffer
    first_word_in_header = strtok(echoBuffer, " ");
    file_to_look_for = strtok(NULL, " ");

    // set file to look for to a content type var
    char* before_content_type = file_to_look_for;

    if (strcmp(file_to_look_for, "/") == 0)
    {
	strcat(rootDirName, "/index.html");
    }
    else
    {
	// combine the root directory name with the file requested
        strcat(rootDirName, file_to_look_for);
    }

    // find what the content type that was requested
    strcpy(content_type, rootDirName);
    strtok(content_type, ".");
    content_type1 = strtok(NULL, " ");

    // clear the header buffer
    memset(header, 0, 256);

    // create a file pointer
    FILE* open_dir = fopen(rootDirName, "rb");

    // seek to end of file to find size then return to begging of file
    fseek(open_dir, 0, SEEK_END);
    long int file_size = ftell(open_dir);
    fseek(open_dir, 0, SEEK_SET);

    // open the file to read 
    // depending on the content type set the header to the proper value
    if (open_dir)
    {
        if (strcmp(content_type1, "html") == 0)
        {
            sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %li\r\n\r\n", file_size);
        }

        else if (strcmp(content_type1, "htm") == 0)
        {
            sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %li\r\n\r\n", file_size);
        }

        else if (strcmp(content_type1, "jpg") == 0)
        {
            sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %li\r\n\r\n", file_size);
        }

        else if (strcmp(content_type1, "jpeg") == 0)
        {
            sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %li\r\n\r\n", file_size);
        }

        else if (strcmp(content_type1, "txt") == 0)
        {
            sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %li\r\n\r\n", file_size);
        }

        else if (strcmp(content_type1, "gif") == 0)
        {
            sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: image/gif\r\nContent-Length: %li\r\n\r\n", file_size);
        }

        else
        {
            sprintf(header, "HTTP/1.1 404 Not Found\r\nContent-Type: application/octet-stream\r\n\r\n");
        }
    }

    else if (open_dir == NULL)
    {
        sprintf(header, "HTTP/1.1 404 Not Found\r\nContent-Type: application/octet-stream\r\n\r\n");
    }

    // set the send buffer size to the size of the file
    // clear the send buffer if anything was in it
    char send_buffer[file_size];
    memset(send_buffer, 0, file_size);

    // send the header to the client or say the send failed
    if (send(clntSocket, header, strlen(header), 0) != strlen(header))
        DieWithError("send() failed");

    // read the file into the send buffer
    fread(send_buffer, file_size, 1, open_dir);

    // send the send buffer to the client
    if (send(clntSocket, send_buffer, file_size, 0) != file_size)
	DieWithError("send() failed");

    // close the file
    fclose(open_dir);
    close(clntSocket);    /* Close client socket */
}
