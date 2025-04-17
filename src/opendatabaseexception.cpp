#include <DatabaseAdapter/opendatabaseexception.h>

namespace DatabaseAdapter {
open_database_exception::open_database_exception(const std::string& Message)
    : _message(Message)
{
}

const char* open_database_exception::what() const
{
    return _message.c_str();
}
} // namespace DatabaseAdapter