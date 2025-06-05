#pragma once

#include "itransaction.h"
#include "model/databasesettings.h"
#include "model/queryresult.h"

#include <memory>

namespace database_adapter {
/**
 * @brief Интерфейс для работы с базами данных.
 * Класс IDataBaseDriver предоставляет основные операции с базами данных,
 * которые должны быть реализованы в конкретных драйверах базы данных.
 */
class IDataBaseDriver
{
public:
    /**
     * @brief Возвращает текст, представляющий NULL-значение в базе данных.
     * @return NULL-значение в виде строки.
     */
    static std::string null_value();

public:
    /**
     * @brief Конструктор IDataBaseDriver с указанными настройками подключения.
     * @param settings Настройки подключения к базе данных.
     */
    explicit IDataBaseDriver(models::database_settings settings);

    /**
     * @brief Деструктор по умолчанию.
     */
    virtual ~IDataBaseDriver() = default;

    /**
     * @brief Устанавливает соединение с базой данных.
     * Эта функция должна устанавливать соединение с базой данных
     * с использованием настроек, указанных при создании экземпляра драйвера.
     * @return true, если соединение установлено успешно, иначе false.
     * @throws Выбрасывает исключение open_database_exception в случае ошибки подключения к базе данных
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
     * @throws Выбрасывает исключение sql_exception в случае ошибки выполнения запроса
     */
    virtual models::query_result exec(const std::string& query) = 0;
    /**
     * @brief Открывает новую транзакцию с типом -1.
     * Эта функция должна открыть новую транзакцию и вернуть указатель на нее.
     * @return Указатель на открытую транзакцию. Если транзакция не была открыта возвращается nullptr.
     */
    std::shared_ptr<ITransaction> open_base_transaction() const;

    /**
     * @brief Открывает новую транзакцию.
     * Эта функция должна открыть новую транзакцию и вернуть указатель на нее.
     * @param type Тип транзакции (Зависит от реализации базы данных).
     * @return Указатель на открытую транзакцию. Если транзакция не была открыта возвращается nullptr.
     */
    virtual std::shared_ptr<ITransaction> open_transaction(int type) const = 0;

    /**
     * Возвращает флаг который сообщает о том что данная база данных поддреживает returning после insert
     */
    virtual bool has_returning_statment();

    /**
     * Функция которая модифицирует запрос на всавку чтобы она возвращала требуемые поля после вставки
     * @param sql Запрос который необходимо модифицировать
     * @param returning_columns Список колонок которые необходимо вернуть
     * @note Для баз данных в которых нет поддержки returning
     */
    virtual void append_returning(std::string& sql, const std::vector<std::string>& returning_columns);

protected:
    /// @brief Настройки подключения к базе данных.
    models::database_settings _settings;
};

} // namespace database_adapter
