#include <DatabaseAdapter/opendatabaseexception.h>

namespace DatabaseAdapter {
open_database_exception::open_database_exception(char const* const Message)
    : exception(Message)
{
}
} // namespace DatabaseAdapter