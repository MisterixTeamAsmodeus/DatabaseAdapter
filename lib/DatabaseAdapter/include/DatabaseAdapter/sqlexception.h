#pragma once

#include "databaseadapter_global.h"

#include <exception>
#include <string>

namespace DatabaseAdapter {
class DATABASEADAPTER_EXPORT sql_exception final : public std::exception
{
public:
    sql_exception() = default;

    explicit sql_exception(char const* Message);
    sql_exception(char const* Message, char const* last_query);

    std::string last_query() const
    {
        return _last_query;
    }

private:
    /// @brief Текст последнего выполненного SQL-запроса.
    std::string _last_query {};
};
} // namespace DatabaseAdapter