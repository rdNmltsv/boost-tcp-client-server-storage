#pragma once

#include "tcp_client.h"
#include <string>

enum class req_t : std::uint8_t;

class Handler{
    public:
        static void handleRead(TCPClient& client);
        static void handleWrite(TCPClient& client);
        static void handleResponce(const std::string& responce);
        static req_t request;
};