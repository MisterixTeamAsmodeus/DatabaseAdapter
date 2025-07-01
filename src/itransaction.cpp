#include "DatabaseAdapter/itransaction.h"

namespace database_adapter {

ITransaction::ITransaction(std::shared_ptr<connection> connection)
    : _connection(std::move(connection))
{
}

models::query_result ITransaction::exec(const std::string& query)
{
    return _connection->exec(query);
}

bool ITransaction::rollback()
{
    return rollback_to_save_point("");
}

} // namespace database_adapter
