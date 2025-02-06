#include <DatabaseAdapter/idatabasedriver.h>

#include <utility>

namespace {
constexpr auto Null_Value = "NULL";
}

namespace EntityCraft {
namespace DatabaseAdapter {

IDataBaseDriver::IDataBaseDriver(Models::DatabaseSettings settings)
    : _settings(std::move(settings))
{
}

Models::QueryResult IDataBaseDriver::exec(const std::string& query)
{
    _last_query = query;
    return {};
}

std::shared_ptr<ITransaction> IDataBaseDriver::open_transaction() const
{
    return open_transaction(-1);
}

std::string IDataBaseDriver::last_query() const
{
    return _last_query;
}

std::string IDataBaseDriver::last_error()
{
    const auto temp = _last_error;
    _last_error.clear();
    return temp;
}

bool IDataBaseDriver::has_error() const
{
    return !_last_error.empty();
}

std::string IDataBaseDriver::null_value()
{
    return Null_Value;
}

} // namespace DatabaseAdapter
} // namespace EntityCraft
