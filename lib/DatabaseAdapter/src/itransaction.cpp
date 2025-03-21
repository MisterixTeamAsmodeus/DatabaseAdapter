#include "DatabaseAdapter/itransaction.h"

namespace DatabaseAdapter {

bool ITransaction::rollback()
{
    return rollback("");
}

} // namespace DatabaseAdapter
