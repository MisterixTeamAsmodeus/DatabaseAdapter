#include "DatabaseAdapter/itransaction.h"


namespace DatabaseAdapter {

bool ITransaction::exec(const std::string& query)
{
    _query.append(query).append("\n");
    return true;
}

bool ITransaction::rollback()
{
    return rollback("");
}

std::string ITransaction::query() const
{
    return _query;
}

} // namespace DatabaseAdapter

