#include <DatabaseAdapter/idatabasedriver.h>

namespace database_adapter {

IDataBaseDriver::IDataBaseDriver(models::database_settings /*settings*/)
{
}

IDataBaseDriver::IDataBaseDriver(const std::shared_ptr<connection>& connection)
    : _connection(connection)
{
}

bool IDataBaseDriver::is_open() const
{
    return _connection->is_valid();
}

models::query_result IDataBaseDriver::exec(const std::string& query)
{
    return _connection->exec(query);
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

} // namespace database_adapter
