#include "DatabaseAdapter/connection.h"

namespace database_adapter {
connection::connection(models::database_settings settings)
    : settings(std::move(settings))
{
}
} // namespace database_adapter