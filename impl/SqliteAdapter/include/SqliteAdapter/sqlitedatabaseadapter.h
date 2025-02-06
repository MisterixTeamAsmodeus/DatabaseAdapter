#pragma once

#include "sqlliteadapter_global.h"

#include <DatabaseAdapter/idatabasedriver.h>
#include <../lib/sqlite-amalgamation/sqlite3.h>

namespace EntityCraft {
namespace DatabaseAdapter {
namespace Sqlite {

class SQLITEADAPTER_EXPORT SqliteDatabaseAdapter final : public IDataBaseDriver
{
public:
    enum TransactionType
    {
        DEFERRED = 0,
        IMMEDIATE,
        EXCLUSIVE
    };

    explicit SqliteDatabaseAdapter(const Models::DatabaseSettings& settings);

    ~SqliteDatabaseAdapter() override;

    bool connect() override;
    bool is_open() override;

    bool disconnect() const override;

    Models::QueryResult exec(const std::string& query) override;
    std::shared_ptr<ITransaction> open_transaction(int type) const override;

private:
    sqlite3* _database = nullptr;
};

} // namespace Sqlite
} // namespace DatabaseAdapter
}; // namespace EntityCraft