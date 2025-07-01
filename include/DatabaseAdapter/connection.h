#pragma once

#include "model/databasesettings.h"
#include "model/queryresult.h"

namespace database_adapter {

class connection
{
public:
    explicit connection(models::database_settings settings);

    virtual ~connection() = default;

    virtual bool is_valid() = 0;

    /**
     * @brief Выполняет SQL-запрос к базе данных.
     * Эта функция должна выполнить указанный SQL-запрос к базе данных
     * и вернуть результат в виде объекта QueryResult.
     * @param query SQL-запрос.
     * @return Результат выполнения SQL-запроса.
     * @throws Выбрасывает исключение sql_exception в случае ошибки выполнения запроса
     */
    virtual models::query_result exec(const std::string& query) = 0;
};

} // namespace database_adapter