#include <DatabaseAdapter/sqlexception.h>

#include <utility>

namespace DatabaseAdapter {
sql_exception::sql_exception(std::string Message)
    : _message(std::move(Message))
{
}

sql_exception::sql_exception(std::string Message, std::string last_query)
    : _message(std::move(Message))
    , _last_query(std::move(last_query))
{
}

const char* sql_exception::what() const
{
    return _message.c_str();
}

std::string sql_exception::last_query() const
{
    return _last_query;
}
} // namespace DatabaseAdapter