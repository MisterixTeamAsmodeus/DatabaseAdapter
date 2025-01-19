#include "SqliteAdapter/sqlitedatabaseadapter.h"

#include "SqliteAdapter/sqlitetransaction.h"

// https://www.sqlite.org/cintro.html
// https://www.book2s.com/tutorials/sqlite-cpp.html

namespace EntityCraft {
namespace DatabaseAdapter {
namespace Sqlite {

SqliteDatabaseAdapter::SqliteDatabaseAdapter(const Models::DatabaseSettings& settings)
    : IDataBaseDriver(settings)
{
}

SqliteDatabaseAdapter::~SqliteDatabaseAdapter()
{
    sqlite3_close(_database);
}

bool SqliteDatabaseAdapter::connect()
{
    if(sqlite3_open(_settings.url.c_str(), &_database) != SQLITE_OK) {
        _last_error.append("Can't open database: ").append(sqlite3_errmsg(_database));
        return false;
    }

    return true;
}

bool SqliteDatabaseAdapter::is_open()
{
    return _database != nullptr;
}

bool SqliteDatabaseAdapter::disconnect() const
{
    return sqlite3_close(_database) == SQLITE_OK;
}

Models::QueryResult SqliteDatabaseAdapter::exec(const std::string& query)
{
    IDataBaseDriver::exec(query);
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _last_error.append("Failed to prepare statement: ").append(sqlite3_errmsg(_database));
        return {};
    }

    int rc = sqlite3_step(stmt);

    Models::QueryResult result;
    while(rc == SQLITE_ROW) {
        Models::QueryResult::ResultRow row;
        for(int i = 0; i < sqlite3_column_count(stmt); i++) {
            const auto column_name = sqlite3_column_name(stmt, i);
            const auto column_value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));

            row.insert({ column_name, column_value == nullptr ? null_value() : column_value });
        }
        result.add_row(row);

        rc = sqlite3_step(stmt);
    }

    if(rc != SQLITE_DONE) {
        _last_error.append("Failed to execute statement: ").append(sqlite3_errmsg(_database));
        return {};
    }

    sqlite3_finalize(stmt);

    return result;
}

std::shared_ptr<ITransaction> SqliteDatabaseAdapter::open_transaction(int type) const
{
    const auto sql = [&type]() {
       switch(type) {
           case DEFERRED:
               return "BEGIN DEFERRED;";
           case IMMEDIATE:
               return "BEGIN IMMEDIATE;";
           case EXCLUSIVE:
               return "BEGIN EXCLUSIVE;";
           default:
               return "BEGIN;";
       }
    }();

    if(sqlite3_exec(_database, sql, nullptr, nullptr, nullptr) != SQLITE_OK)
        return nullptr;

    return std::make_shared<SqliteTransaction>(_database);
}

} // namespace Sqlite
} // namespace DatabaseAdapter
} // namespace EntityCraft