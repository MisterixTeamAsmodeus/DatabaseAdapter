#include <DatabaseAdapter/idatabasedriver.h>

#include <utility>

namespace database_adapter {

IDataBaseDriver::IDataBaseDriver(models::database_settings settings)
    : _settings(std::move(settings))
{
}

std::shared_ptr<ITransaction> IDataBaseDriver::open_base_transaction() const
{
    return open_transaction(-1);
}

bool IDataBaseDriver::has_returning_statment()
{
    return true;
}

void IDataBaseDriver::append_returning(std::string& sql, const std::vector<std::string>& returning_columns)
{
}

std::string IDataBaseDriver::null_value()
{
    return "NULL";
}

} // namespace database_adapter
