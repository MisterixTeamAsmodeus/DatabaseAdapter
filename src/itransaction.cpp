#include "DatabaseAdapter/itransaction.h"

#include "DatabaseAdapter/exception/sqlexception.h"
#include "DatabaseAdapter/iconnection.h"

namespace database_adapter {

ITransaction::ITransaction(std::shared_ptr<IConnection> connection)
    : _connection(std::move(connection))
{
}

void ITransaction::open_base_transaction()
{
    open_transaction(-1);
}

models::query_result ITransaction::exec(const std::string& query)
{
    try {
        return _connection->exec(query);
    } catch(const sql_exception&) {
        _has_error = true;
        throw;
    }
}

void ITransaction::rollback()
{
    rollback_to_save_point("");
}

} // namespace database_adapter
