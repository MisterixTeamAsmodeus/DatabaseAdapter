#pragma once

#include <exception>

namespace DatabaseAdapter {
class open_database_exception final : std::exception
{
public:
    explicit open_database_exception(char* Message);

    ~open_database_exception() noexcept override = default;

    const char* what() const override;

private:
    char* _message = nullptr;
};
} // namespace DatabaseAdapter