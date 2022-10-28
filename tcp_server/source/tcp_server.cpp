#include "tcp_server.h"
#include <iostream>

using boost::asio::ip::tcp;

TCPServer::TCPServer(int port) :  
	_port(port),
    _acceptor(_ioContext, tcp::endpoint(tcp::v4(), _port)) 
{}

int TCPServer::Run() {
    try {
        startAccept();
		
		std::cout << "Server is running on port " << _port << ".\n";
		
        _ioContext.run();
    } 
	catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}

void TCPServer::Send(TCPConnection::pointer connection, const std::string& message) {
    connection->Post(message);
}

void TCPServer::startAccept() {
    _socket.emplace(_ioContext);

    _acceptor.async_accept(*_socket, 
		[this](const boost::system::error_code& error) {
			auto connection = TCPConnection::Create(std::move(*_socket));

			if (OnJoin) {
				OnJoin(connection);
			}

			_connections.insert(connection);
			
			if (!error) {
				connection->Start(
					[this, weak = std::weak_ptr(connection)](const std::string& message) { 
						if (auto shared = weak.lock(); shared && OnClientMessage){
							OnClientMessage(shared, message); 
						}
					},
					[&, weak = std::weak_ptr(connection)] () {
						if (auto shared = weak.lock(); shared && _connections.erase(shared)) {
							if (OnLeave) {
								OnLeave(shared);
							}
						}
					}
				);
			}

			startAccept();
		}
	);
}
