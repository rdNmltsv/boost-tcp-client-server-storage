#pragma once

#include <string>
#include <unordered_map>
#include <mutex>
#include <optional>

using UMapSS = std::unordered_map<std::string, std::string>;

class Storage {
    public:
        Storage(const Storage&) = delete;
        Storage(Storage&&) = delete;
        Storage& operator=(const Storage&) = delete;
        Storage&& operator=(Storage&&) = delete;

        static Storage* getInstance();
        
        std::optional<std::string> Read(const std::string& key);
        
        // TODO: should return some error_type
        int Write(std::string key, std::string value);

    private:
        Storage();

    private:
        static Storage* _pInstance;
        static std::mutex _mutex;
        UMapSS _storage;
};
