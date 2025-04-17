#pragma once

#include <exception>
#include <string>

namespace DatabaseAdapter {
class sql_exception final : public std::exception
{
public:
    explicit sql_exception(char* Message);
    sql_exception(char* Message, char* last_query);

    ~sql_exception() noexcept override = default;
    const char* what() const override;

    std::string last_query() const
    {
        return _last_query;
    }

private:
    char* _message = nullptr;
    /// @brief Текст последнего выполненного SQL-запроса.
    std::string _last_query {};
};
} // namespace DatabaseAdapter