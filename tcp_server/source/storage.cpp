#include "storage.h"
#include <mutex>
#include <optional>

Storage* Storage::_pInstance {nullptr};
std::mutex Storage::_mutex;

Storage::Storage() {}

Storage* Storage::getInstance() {
    std::lock_guard lock(_mutex);

    if (_pInstance == nullptr) {
        _pInstance = new Storage();
    }
    return _pInstance;
}

std::optional<std::string> Storage::Read(const std::string& key) {
    std::lock_guard lock(_mutex);
    if (_storage.find(key) != _storage.end()) {
        return _storage.at(key);
    }
    return std::nullopt;
}
        
int Storage::Write(std::string key, std::string value) {
    std::lock_guard lock(_mutex);
    auto result = _storage.try_emplace(key, value);
    if (result.second)
        return 0; // insertion happened
    
    return -1;  // insertion didn't happened
}