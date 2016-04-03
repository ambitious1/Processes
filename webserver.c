#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

char webpage[] = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html><head><title>Test Page</title>\r\n"
"<style>body { background-color: #BDF000 }</style></head>\r\n"
"<body><center><h1>Hello World</h1><br>\r\n"
"<img src=\"http://static7.comicvine.com/uploads/original/11112/111122896/4818284-2933451-broly__the_legend_as_ssj3_by_saiyakupo.png\"></center></body></html>\r\n";

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_len = sizeof(client_addr);
    int fd_server, fd_client; //Return value of socket, and accept
    char buf[2048];//size of data buffer
    int fdimg;
    int on = 1;

    fd_server = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_server < 0)
    {
        perror("socket");
        exit(1);
    }

    //Setting up Socket properties
    setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

    server_addr.sin_family = AF_INET; //server is a TCP socket
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(8080); //listens on port 8080

    //Error Handling on the binding of the server to the client, and the listening of server for the client
    if (bind(fd_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(fd_server);
        exit(1);
    }

    if (listen(fd_server, 10)==-1)
    {
        perror("listen");
        close(fd_server);
        exit(1);
    }

    while(1)
    {
        fd_client = accept(fd_server, (struct sockaddr *) &client_addr, &sin_len);
        
        if (fd_client == -1)
        {
            perror("Connection failed....\n");
            continue;
        }

        printf("Got client connection..........\n");

        if (!fork())
        {
            //child process
            close(fd_server);
            memset(buf, 0, 2048);
            read(fd_client, buf, 2047);

            printf("%s\n", buf);

            if (!strncmp(buf, "GET http://img12.deviantart.net/8120/i/2014/053/8/a/okay_sticker_by_quartertofour-d77iu0e.jpg", 2500))
            {
                fdimg = open("http://img12.deviantart.net/8120/i/2014/053/8/a/okay_sticker_by_quartertofour-d77iu0e.jpg", O_RDONLY);
                sendfile(fd_client, fdimg, NULL, 4000);
                close(fdimg);
            }


            else if (!strncmp(buf, "GET http://s-media-cache-ak0.pinimg.com/236x/b6/f0/35/b6f03509aaa5c6f7d2c12de014d07a61.jpg", 2500))
            {
                fdimg = open("http://s-media-cache-ak0.pinimg.com/236x/b6/f0/35/b6f03509aaa5c6f7d2c12de014d07a61.jpg", O_RDONLY);
                sendfile(fd_client, fdimg, NULL, 4000);
                close(fdimg);
            }
                        
            else
                write(fd_client, webpage, sizeof(webpage) -1);

            close(fd_client);
            printf("closing...\n");
            exit(0);
        }

        //parent process
        close(fd_client);
    }

    return 0;
}
