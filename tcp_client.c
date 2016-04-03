#include <stdio.h>
#include <stdlib.h>

//Socket Headers
#include <sys/types.h>
#include <sys/socket.h>

//Structures to Store Address Information
#include <netinet/in.h> 

int main() {
    
    //create a socket
    int network_socket;
    
    /* TCP socket - parameters to use from the header file, 
     * SOCK_STREAM is to indicate it is a TCP socket instead 
     * of UDP, 0 is we're using the default protocol, 
     * which is TCP */

    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    //specify an address for the socket (find the address and port of the remote socket we want to connect to)
    
    //Port Declaration
    struct sockaddr_in server_address; //declare structure for the address AF_INET
    server_address.sin_family = AF_INET; //lets it know what type of address
    server_address.sin_port = htons(9002); //specifies the port

    //Address Declaration
    server_address.sin_addr.s_addr = INADDR_ANY; //connect to our localmachine, same as connecting to 0000


    int connect_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    
    if (connect_status == -1) {
        printf("There was an error making a connection to the remote socket \n\n");
    }

    //receive data from the server
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    //print out the server's response
    printf("The server sent the data: %s\n", server_response);

    //close socket
    close(network_socket);
    close(network_socket);

    return 0;
}

