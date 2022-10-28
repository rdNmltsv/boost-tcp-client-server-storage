#include <iostream>
#include "tcp_server.h"

int main(int argc, char* argv[]) {
    TCPServer server(1337);

    server.OnJoin = [](TCPConnection::pointer connection) {
        std::cout << "User has joined the server: " << connection->GetUsername() << std::endl;
    };

    server.OnLeave = [](TCPConnection::pointer connection) {
        std::cout << "User has left the server: " << connection->GetUsername() << std::endl;
    };

    server.OnClientMessage = [&server](const std::string& message) {
        // Parse the message
		std::cout << message;

        // Send message to all clients
        // server.Broadcast(message);
    };
	
	int res = server.Run();
	return res;
}