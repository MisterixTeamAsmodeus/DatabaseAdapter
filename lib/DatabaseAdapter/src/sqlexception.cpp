#include <DatabaseAdapter/sqlexception.h>

namespace DatabaseAdapter {
sql_exception::sql_exception(char const* Message)
    : std::exception(Message)
{
}

sql_exception::sql_exception(char const* const Message, char const* const last_query)
    : std::exception(Message)
    , _last_query(last_query)
{
}
} // namespace DatabaseAdapter