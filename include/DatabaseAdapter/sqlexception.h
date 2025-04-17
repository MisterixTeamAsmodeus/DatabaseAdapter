#pragma once

#include <exception>
#include <string>

namespace DatabaseAdapter {
class sql_exception final : public std::exception
{
public:
    explicit sql_exception(std::string  Message);
    sql_exception(std::string Message, std::string last_query);

    sql_exception(const sql_exception& other) = default;
    sql_exception(sql_exception&& other) noexcept = default;
    sql_exception& operator=(const sql_exception& other) = default;
    sql_exception& operator=(sql_exception&& other) noexcept = default;

    ~sql_exception() noexcept override = default;
    const char* what() const override;

    std::string last_query() const;

private:
    std::string _message;
    /// @brief Текст последнего выполненного SQL-запроса.
    std::string _last_query {};
};
} // namespace DatabaseAdapter