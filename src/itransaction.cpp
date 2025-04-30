#include "DatabaseAdapter/itransaction.h"

namespace database_adapter {

bool ITransaction::rollback()
{
    return rollback("");
}

} // namespace database_adapter
