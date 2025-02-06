#pragma once

#include "DatabaseAdapter/databaseadapter_global.h"

#include <string>

namespace EntityCraft {
namespace DatabaseAdapter {
namespace Models {
/**
 * @brief Класс описывающий настройки для подключения к базе данных
 */
struct DATABASEADAPTER_EXPORT DatabaseSettings
{
    /// @brief Адрес для подключения к базе данных
    std::string url;
    /// @brief Порт для подключения к базе данных
    std::string port;
    /// @brief Имя пользователя для авторизации
    std::string login;
    /// @brief Пароль пользователя для авторизации
    std::string password;
};
} // namespace Models
} // namespace DatabaseAdapter
} // namespace EntityCraft
