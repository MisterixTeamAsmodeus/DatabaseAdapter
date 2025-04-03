#include "DatabaseAdapter/model/queryresult.h"


namespace DatabaseAdapter {
namespace Models {

QueryResult::QueryResult(const std::list<ResultRow>& result)
    : _result(result)
{
}

void QueryResult::add_row(const ResultRow& value)
{
    _result.emplace_back(value);
}

std::list<QueryResult::ResultRow> QueryResult::data() const
{
    return _result;
}

std::list<QueryResult::ResultRow>& QueryResult::operator()()
{
    return _result;
}

bool QueryResult::empty() const
{
    return _result.empty();
}
} // namespace Models
} // namespace DatabaseAdapter
