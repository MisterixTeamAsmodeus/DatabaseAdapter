#pragma once

#include <exception>
#include <string>

namespace DatabaseAdapter {
class open_database_exception final : std::exception
{
public:
    explicit open_database_exception(const std::string& Message);

    ~open_database_exception() noexcept override = default;

    const char* what() const override;

private:
    std::string _message;
};
} // namespace DatabaseAdapter