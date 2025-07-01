#pragma once

#include "model/databasesettings.h"

#include <chrono>
#include <memory>
#include <mutex>
#include <vector>

namespace database_adapter {

template<typename ConnectionType>
class connection_pool
{
public:
    explicit connection_pool(models::database_settings settings,
        size_t start_pool_size,
        size_t max_pool_size,
        std::chrono::seconds wait_time = std::chrono::seconds(5))
        : _settings(std::move(settings))
        , _start_pool_size(start_pool_size)
        , _max_pool_size(max_pool_size)
        , _wait_time(wait_time)
    {
        static_assert(_start_pool_size <= _max_pool_size);

        std::lock_guard<std::mutex> lock_guard(_lock);

        for(auto i = 0; i < _start_pool_size; i++) {
            _connections.emplace_back(std::make_shared<ConnectionType>(_settings));
        }
    }

    explicit connection_pool(models::database_settings settings,
        size_t start_pool_size = 10,
        std::chrono::seconds wait_time = std::chrono::seconds(5))
        : connection_pool(std::move(settings), start_pool_size, start_pool_size, wait_time)
    {
    }

    void set_max_pool_size(const size_t max_pool_size)
    {
        _max_pool_size = max_pool_size;
    }

    void set_wait_time(const std::chrono::seconds& wait_time)
    {
        _wait_time = wait_time;
    }

    std::shared_ptr<ConnectionType> open_connection()
    {
        std::lock_guard<std::mutex> lock_guard(_lock);
        for(const auto& connection : _connections) {
            if(connection.use_count() == 1) {
                return connection;
            }
        }

        if(_connections.size() < _max_pool_size) {
            auto conn = std::make_shared<ConnectionType>(_settings);
            _connections.emplace_back(conn);
            return conn;
        }

        const auto start = std::chrono::system_clock::now();

        while(std::chrono::system_clock::now() - start <= _wait_time) {
            for(const auto& connection : _connections) {
                if(connection.use_count() == 1) {
                    return connection;
                }
            }
        }

        return nullptr;
    }

private:
    std::mutex _lock;

    models::database_settings _settings;

    size_t _start_pool_size;
    size_t _max_pool_size;
    std::chrono::seconds _wait_time = std::chrono::seconds(5);

    std::vector<std::shared_ptr<ConnectionType>> _connections;
};
} // namespace database_adapter