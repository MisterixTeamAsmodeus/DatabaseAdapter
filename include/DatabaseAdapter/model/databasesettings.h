#pragma once

#include <string>

namespace DatabaseAdapter {
namespace Models {
/**
 * @brief Класс описывающий настройки для подключения к базе данных
 */
struct DatabaseSettings
{
    /// @brief Адрес/путь для подключения к базе данных
    std::string url {};
    /// @brief Порт для подключения к базе данных
    std::string port {};
    /// @brief Имя пользователя для авторизации
    std::string login {};
    /// @brief Пароль пользователя для авторизации
    std::string password {};
};
} // namespace Models
} // namespace DatabaseAdapter
