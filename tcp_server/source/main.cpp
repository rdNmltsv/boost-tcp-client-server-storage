#include <iostream>
#include "tcp_server.h"
#include "nlohmann/json.hpp"
#include "storage.h"

using json = nlohmann::json;

int main(int argc, char* argv[]) {
	int port;
	std::cout << "Enter port: \n";
	std::cin >> port;
    
	TCPServer server(port);
	
	Storage* pStorage = Storage::getInstance();

    server.OnJoin = [](TCPConnection::pointer connection) {
        std::cout << "User "  << connection->GetUsername() << " connected." << std::endl;
	connection->Post("Succesfully connected to server.}");
    };

    server.OnLeave = [](TCPConnection::pointer connection) {
        std::cout << "User " << connection->GetUsername() << " disconnected." << std::endl;
    };

    server.OnClientMessage = [&server, pStorage](TCPConnection::pointer connection, const std::string& message) {
		// std::cout << connection->GetUsername() << ':' << message << '\n';
		
		json jmessage = json::parse(message);
        json jresponce;
        bool error = false;
        std::string error_description;

        if (jmessage.contains("request")) {
            if(jmessage.at("request") == "read") {
                if(jmessage.contains("key")) {
                    auto responce = pStorage->Read(jmessage["key"]);
                    if (responce) {
                        jresponce["value"] = responce.value();
                    }
                    else {
                        error = true;
                        error_description = "There is no key " + jmessage["key"].get<std::string>() + " in storage.";
                    } 
                }
                else {
                    error = true;
                    error_description = "Provide key for read request.";
                }
            }
            else if (jmessage.at("request") == "write") {
                if(jmessage.contains("key")) {
                    if(jmessage.contains("value")) {
                        auto responce = pStorage->Write(jmessage["key"], jmessage["value"]);
                        if (responce == 0) {
							std::cout << "Succesfully writed key " << jmessage["key"] << " with value " << jmessage["value"] << ".\n"; 
                        }
                        else {
                            error = true;
                            error_description = "Unsuccessfull write. Key " + jmessage["key"].get<std::string>() + " already exists in storage.";
                        }
                    }
                    else {
                        error = true;
                        error_description = "Provide value for write request.";
                    }
                }
                else {
                    error = true;
                    error_description = "Provide key for write request.";
                }
            }
            else {
                error_description = "Wrong request. Must be read or write.";            
            }
        }
        else {
                error_description = "Wrong JSON. Must contain request.";  
        }

        if (!error) {
            jresponce["status"] = "ok";
        }
        else {
            jresponce["status"] = "error";
            jresponce["description"] = error_description;
        }
         
        // std::cout << "Sending responce " << jresponce << " to user " << connection->GetUsername() << ".\n"; 
        server.Send(connection, jresponce.dump());
    };
	
	int res = server.Run();
	return res;
}