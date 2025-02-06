#include "SqliteAdapter/sqlitetransaction.h"

namespace EntityCraft {
namespace DatabaseAdapter {
namespace Sqlite {

SqliteTransaction::SqliteTransaction(sqlite3* database)
    : _database(database)
{
}

bool SqliteTransaction::exec(const std::string& query)
{
    ITransaction::exec(query);
    return sqlite3_exec(_database, query.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK;
}

bool SqliteTransaction::commit()
{
    return sqlite3_exec(_database, "COMMIT;", nullptr, nullptr, nullptr) != SQLITE_OK;
}

bool SqliteTransaction::rollback(const std::string& save_point)
{
    const auto sql = save_point.empty() ? "ROLLBACK;" : "ROLLBACK TO " + save_point;
    return sqlite3_exec(_database, sql.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK;
}

bool SqliteTransaction::add_save_point(const std::string& save_point)
{
    if(save_point.empty())
        return false;

    const auto sql = "SAVEPOINT " + save_point;
    return sqlite3_exec(_database, sql.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK;
}

} // namespace Sqlite
} // namespace DatabaseAdapter
} // namespace EntityCraft