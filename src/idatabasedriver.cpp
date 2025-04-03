#include <DatabaseAdapter/idatabasedriver.h>

#include <utility>

namespace {
constexpr auto Null_Value = "NULL";
} // namespace

namespace DatabaseAdapter {

IDataBaseDriver::IDataBaseDriver(Models::DatabaseSettings settings)
    : _settings(std::move(settings))
{
}

std::shared_ptr<ITransaction> IDataBaseDriver::open_base_transaction() const
{
    return open_transaction(-1);
}

std::string IDataBaseDriver::null_value()
{
    return Null_Value;
}

} // namespace DatabaseAdapter
