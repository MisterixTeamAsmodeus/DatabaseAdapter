#include <DatabaseAdapter/sqlexception.h>

namespace DatabaseAdapter {
sql_exception::sql_exception(char* Message)
    : _message(Message)
{
}

sql_exception::sql_exception(char* Message, char* last_query)
    : _message(Message)
    , _last_query(last_query)
{
}

const char* sql_exception::what() const
{
    return _message;
}
} // namespace DatabaseAdapter