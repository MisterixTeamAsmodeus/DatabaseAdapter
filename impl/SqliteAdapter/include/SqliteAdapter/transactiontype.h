#pragma once

#include <cstdint>

namespace DatabaseAdapter {
namespace Sqlite {
/// Типы транзакции поддерживаемые в sqlite3
enum class TransactionType : uint8_t
{
    DEFERRED = 0,
    IMMEDIATE,
    EXCLUSIVE
};
} // namespace Sqlite
} // namespace DatabaseAdapter