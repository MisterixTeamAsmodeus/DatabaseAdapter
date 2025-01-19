#pragma once

#include "databaseadapter_global.h"

#include <string>

namespace EntityCraft {
namespace DatabaseAdapter {
/**
 * @brief Интерфейс для работы с транзакциями в базе данных.
 * Класс ITransaction предоставляет основные операции с транзакциями,
 * которые должны быть реализованы в конкретных драйверах базы данных.
 * @note Класс должен быть специализирован для конкретной реализации базы данных и генерировать sql команды для выполнения внесенных изменений.
 */
class DATABASEADAPTER_EXPORT ITransaction
{
public:
    /**
     * @brief Деструктор по умолчанию.
     */
    virtual ~ITransaction() = default;

    /**
     * @brief Выполняет SQL-запрос в рамках текущей транзакции.
     *
     * Эта функция выполняет предоставленный SQL-запрос как часть текущей транзакции базы данных.
     * Она позволяет выполнять операции с базой данных, такие как SELECT, INSERT, UPDATE или DELETE,
     * в рамках транзакции.
     *
     * @param query Строка, содержащая SQL-запрос для выполнения.
     *
     * @return Возвращает true, если запрос был успешно выполнен, в противном случае - false.
     */
    virtual bool exec(const std::string& query);

    /**
     * @brief Фиксирует изменения в базе данных.
     * Эта функция должна фиксировать все изменения, внесенные в базу данных
     * с момента начала текущей транзакции.
     */
    virtual bool commit() = 0;

    bool rollback();

    /**
     * @brief Откатывает изменения в базе данных до указанной точки сохранения.
     * Эта функция должна откатить все изменения, внесенные в базу данных
     * с момента создания указанной точки сохранения.
     * @param save_point Точка сохранения, до которой необходимо откатить изменения.
     */
    virtual bool rollback(const std::string& save_point) = 0;

    /**
     * @brief Добавляет точку сохранения в текущую транзакцию.
     * Эта функция должна создать точку сохранения, которую можно использовать
     * для отката изменений до этой точки в текущей транзакции.
     * @param save_point Имя точки сохранения.
     */
    virtual bool add_save_point(const std::string& save_point) = 0;

    /**
     * @brief Возвращает текст сгенерированного SQL-запроса.
     * @return Текст сгенерированного SQL-запроса.
     */
    std::string query() const;

private:
    /// @brief Сгенерированный SQL-запрос.
    std::string _query;
};
} // namespace DatabaseAdapter
} // namespace EntityCraft
