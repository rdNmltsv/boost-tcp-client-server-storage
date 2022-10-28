#include "handler.h"
#include "nlohmann/json.hpp"
#include <iostream>

using json = nlohmann::json;

enum class req_t : std::uint8_t  {
    None,
    Read,
    Write
};

req_t Handler::request = req_t::None;

void Handler::handleRead(TCPClient& tcp_client) {
    Handler::request = req_t::Read;
    json jmessage;
    jmessage["request"] = "read";
    std::string key;
    std::cin >> key;
    jmessage["key"] = key;
    tcp_client.Post(jmessage.dump());
}

void Handler::handleWrite(TCPClient& tcp_client) {
    Handler::request = req_t::Write;
    json jmessage;
    jmessage["request"] = "write";
    std::string key;
    std::cin >> key;
    jmessage["key"] = key;
    std::string value;
    std::cin >> value;
    jmessage["value"] = value;
    tcp_client.Post(jmessage.dump());
}

void Handler::handleResponce(const std::string& responce) {
    if (Handler::request == req_t::None) {
        std::cout << responce << '\n';
        return;
    }

    json jresponce = json::parse(responce);

    if (jresponce.contains("status")) {
        if (jresponce["status"] == "ok") {       
            switch (Handler::request)
            {
            case req_t::Read: {
                if(jresponce.contains("value") && jresponce["value"].is_string()) {
                    std::cout << "value: " << jresponce["value"].get<std::string>() << '\n';
                }
                else {
                    std::cerr << "Succesfull responce on read must contain value.";
                }
                break;
            }
            case req_t::Write: {
                if(jresponce.size() == 1)
                    std::cout << "Succesfully writed.\n";
                else {
                    std::cerr << "Wrong responce on write request.\n";
                }
                break;
            }
            default: {
                break;
            }
            }
        }
        else {
            if (jresponce.contains("description")) {
                std::cerr << "Error: " << jresponce["description"].get<std::string>() << '\n';
            }
            else {
                std::cerr << "Error occurred, but no description provided.\n";
            }
        }
    }
    else {
        std::cerr << "Responce must contain operation status.";
    }

    Handler::request = req_t::None; // reset request type
}
