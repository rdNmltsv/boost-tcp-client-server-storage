#include "tcp_client.h"
#include "handler.h"
#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
	std::string address;
	int port;
	std::cout << "Enter IP address: \n";
	std::cin >> address;
	std::cout << "Enter port: \n";
	std::cin >> port;
	
    TCPClient client {address, port};

    client.OnMessage = [](const std::string& message) {
		Handler::handleResponce(message);
    };

    std::thread t{[&client] () { client.Run(); }};

    for(;;) {		
        std::string cmd;
        std::cin >> cmd;

		if (cmd == "q" || cmd == "quit") {
            break;
        }
        else if (cmd == "read") {
            Handler::handleRead(client);
        }
        else if (cmd == "write") {
            Handler::handleWrite(client);
        }
        else {
            std::cerr << "Wrong command '" << cmd << "'\n";
			std::ios_base::sync_with_stdio(0);
			std::cin.ignore(std::cin.rdbuf()->in_avail());
        }
    }

    client.Stop();
    t.join();
    return 0;
}
