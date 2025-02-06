// Server side C/C++ program to demonstrate Socket programming 
// Here's some include statements that might be helpful for you
#include <string> 
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) 
{ 
	// check to see if user input is valid
	char socket_read_buffer[1024];
	
	// TODO: Fill out the server ip and port
	std::string server_ip = "";
	std::string server_port = "";

	int opt = 1;
	int client_fd = -1;

	// TODO: Create a TCP socket()

	// Enable reusing address and port
	if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
		return -1;
	}

	// Check if the client socket was set up properly
	if(client_fd == -1){
		printf("Error- Socket setup failed");
		return -1;
	}
	
	// Helping you out by pepping the struct for connecting to the server
	struct addrinfo hints;
	struct addrinfo *server_addr;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(server_ip.c_str(), server_port.c_str(), &hints, &server_addr);

	// TODO: Connect() to the server
	if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		std::cout << "No connection.\n";
		close(client_fd);
		return -1;
	}
	// TODO: Retreive user input
	std::string user_input;
	std:: cout << "Enter input: ";
	std::getline(std::cin, user_input); 
	// TODO: Send() the user input to the server
	 // 5️⃣ Send user input to the server
    	send(client_fd, user_input.c_str(), user_input.length(), 0);
	// TODO: Recieve any messages from the server and print it here. Don't forget to make sure the string is null terminated!
	char buff[1024]; 
	int messageRecieved = recv(client_fd, buff, 1023, 0);
	
	if (messageRecieved > 0) {
		buff[messageRecieved] = '\0'; 
		std::cout << "Message: " << buff << std::endl;
	} else {
		std::cout << "No connection. Failed.\n";
	}	
	// TODO: Close() the socket
	close(client_fd); 

	return 0; 
} 
