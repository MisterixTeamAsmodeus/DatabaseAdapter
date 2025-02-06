#pragma once

#include "databaseadapter_global.h"
#include "itransaction.h"
#include "model/databasesettings.h"
#include "model/queryresult.h"

#include <memory>

namespace EntityCraft {
namespace DatabaseAdapter {
/**
 * @brief Интерфейс для работы с базами данных.
 * Класс IDataBaseDriver предоставляет основные операции с базами данных,
 * которые должны быть реализованы в конкретных драйверах базы данных.
 */
class DATABASEADAPTER_EXPORT IDataBaseDriver
{
public:
    /**
     * @brief Конструктор IDataBaseDriver с указанными настройками подключения.
     * @param settings Настройки подключения к базе данных.
     */
    explicit IDataBaseDriver(Models::DatabaseSettings settings);

    /**
     * @brief Деструктор по умолчанию.
     */
    virtual ~IDataBaseDriver() = default;

    /**
     * @brief Устанавливает соединение с базой данных.
     * Эта функция должна устанавливать соединение с базой данных
     * с использованием настроек, указанных при создании экземпляра драйвера.
     * @return true, если соединение установлено успешно, иначе false.
     */
    virtual bool connect() = 0;

    /**
     * @brief Проверяет, открыто ли соединение с базой данных.
     * @return true, если соединение открыто, иначе false.
     */
    virtual bool is_open() = 0;

    /**
     * @brief Отключается от базы данных.
     * Эта функция должна закрыть текущее соединение с базой данных.
     * @return true, если соединение закрыто успешно, иначе false.
     */
    virtual bool disconnect() const = 0;

    /**
     * @brief Выполняет SQL-запрос к базе данных.
     * Эта функция должна выполнить указанный SQL-запрос к базе данных
     * и вернуть результат в виде объекта QueryResult.
     * @param query SQL-запрос.
     * @return Результат выполнения SQL-запроса.
     */
    virtual Models::QueryResult exec(const std::string& query);

    /**
     * @brief Открывает новую транзакцию с типом -1.
     * Эта функция должна открыть новую транзакцию и вернуть указатель на нее.
     * @return Указатель на открытую транзакцию. Если транзакция не была открыта возвращается nullptr.
     */
    virtual std::shared_ptr<ITransaction> open_transaction() const;

    /**
     * @brief Открывает новую транзакцию.
     * Эта функция должна открыть новую транзакцию и вернуть указатель на нее.
     * @param type Тип транзакции (Зависит от реализации базы данных).
     * @return Указатель на открытую транзакцию. Если транзакция не была открыта возвращается nullptr.
     */
    virtual std::shared_ptr<ITransaction> open_transaction(int type) const = 0;

    /**
     * @brief Возвращает текст последнего выполненного SQL-запроса.
     * @return Текст последнего выполненного SQL-запроса.
     */
    std::string last_query() const;

    /**
     * @brief Возвращает текст последней ошибки, произошедшей при выполнении SQL-запроса.
     * @return Текст последней ошибки, произошедшей при выполнении SQL-запроса.
     * @note Очищает текст ошибки после вызова функции.
     *       Если ошибка не была зарегистрирована, то возвращает пустую строку.
     */
    std::string last_error();

    /**
     * @brief Проверяет, произошла ли ошибка при выполнении предыдущего SQL-запроса.
     * @return true, если ошибка произошла, иначе false.
     */
    bool has_error() const;

protected:
    /**
     * @brief Возвращает текст, представляющий NULL-значение в базе данных.
     * @return NULL-значение в виде строки.
     */
    static std::string null_value();

protected:
    /// @brief Настройки подключения к базе данных.
    Models::DatabaseSettings _settings;
    /// @brief Текст последнего выполненного SQL-запроса.
    std::string _last_query;
    /// @brief Текст последней ошибки, произошедшей при выполнении SQL-запроса.
    std::string _last_error;
};

} // namespace DatabaseAdapter
} // namespace EntityCraft
