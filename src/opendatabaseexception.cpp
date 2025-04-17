#include <DatabaseAdapter/opendatabaseexception.h>

namespace DatabaseAdapter {
open_database_exception::open_database_exception(std::string Message)
    : _message(std::move(Message))
{
}

const char* open_database_exception::what() const
{
    return _message.c_str();
}
} // namespace DatabaseAdapter