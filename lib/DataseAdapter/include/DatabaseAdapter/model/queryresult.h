#pragma once

#include "DatabaseAdapter/databaseadapter_global.h"

#include <list>
#include <string>
#include <unordered_map>

namespace EntityCraft {
namespace DatabaseAdapter {
namespace Models {

/**
 * @brief Класс для хранения и предоставления результатов SQL-запросов
 */
class DATABASEADAPTER_EXPORT QueryResult
{
public:
    /// @brief Псевдоним для имени столбца результата
    typedef std::string ColumnName;

    /// @brief Псевдоним для значения столбца результата
    typedef std::string Value;

    /// @brief Псевдоним для строки результата запроса
    typedef std::unordered_map<ColumnName, Value> ResultRow;

    QueryResult() = default;

    /**
     * @brief Конструктор, который принимает список ResultRow и инициализирует результат запроса
     * @param result Список ResultRow для инициализации результата
     */
    explicit QueryResult(const std::list<ResultRow>& result);

    /**
     * @brief Добавляет новую строку результата в конец списка
     * @param value Строка результата для добавления
     */
    void add_row(const ResultRow& value);

    /**
     * @brief Возвращает список всех строк результата
     * @return Список всех строк результата
     */
    std::list<ResultRow> data() const;

    /**
     * Перегрузка оператора для удобства использования внутри цикла
     * @return Список всех строк результата
     */
    std::list<ResultRow>& operator()();

    bool empty() const;

private:
    /// @brief Поле, которое хранит список всех строк результатов запроса
    std::list<ResultRow> _result = {};
};
} // namespace Models
} // namespace DatabaseAdapter
} // namespace EntityCraft
