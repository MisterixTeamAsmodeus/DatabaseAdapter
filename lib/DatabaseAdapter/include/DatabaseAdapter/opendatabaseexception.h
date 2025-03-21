#pragma once

#include "databaseadapter_global.h"

#include <exception>

namespace DatabaseAdapter {
class DATABASEADAPTER_EXPORT open_database_exception final : std::exception
{
public:
    open_database_exception() = default;

    explicit open_database_exception(char const* Message);
};
} // namespace DatabaseAdapter