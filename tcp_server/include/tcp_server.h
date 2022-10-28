#pragma once

#include <boost/asio.hpp>
#include <tcp_connection.h>
#include <functional>
#include <optional>
#include <unordered_set>

namespace io = boost::asio;
using io::ip::tcp;


class TCPServer {
    using OnJoinHandler = std::function<void(TCPConnection::pointer)>;
    using OnLeaveHandler = std::function<void(TCPConnection::pointer)>;
    using OnClientMessageHandler = std::function<void(std::string)>;

public:
    TCPServer(int port);

    int Run();
	
    void Broadcast(const std::string& message);
	
private:
    void startAccept();

public:
    OnJoinHandler OnJoin;
    OnLeaveHandler OnLeave;
    OnClientMessageHandler OnClientMessage;

private:
    int _port;
    io::io_context _ioContext;
    tcp::acceptor  _acceptor;
    std::optional<tcp::socket> _socket;
    std::unordered_set<TCPConnection::pointer> _connections {};
};


