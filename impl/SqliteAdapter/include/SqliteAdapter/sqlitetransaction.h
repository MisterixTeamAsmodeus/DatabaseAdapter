#pragma once

#include "sqlliteadapter_global.h"

#include <DatabaseAdapter/itransaction.h>
#include <sqlite-amalgamation/sqlite3.h>

#include <memory>

namespace DatabaseAdapter {
namespace Sqlite {

class SQLITEADAPTER_EXPORT SqliteTransaction final : public ITransaction
{
public:
    explicit SqliteTransaction(sqlite3* database);

    bool exec(const std::string& query) override;
    bool commit() override;
    bool rollback(const std::string& save_point) override;
    bool add_save_point(const std::string& save_point) override;

private:
    sqlite3* _database;
};

} // namespace Sqlite
} // namespace DatabaseAdapter