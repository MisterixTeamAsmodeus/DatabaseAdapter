#pragma once

#include <exception>

namespace DatabaseAdapter {
class open_database_exception final : std::exception
{
public:
    open_database_exception() = default;

    explicit open_database_exception(char const* Message);
};
} // namespace DatabaseAdapter