#include "processor.hpp"
#include <algorithm>

Processor::Processor(std::vector<std::string> data) : data_(data) {}
auto Processor::transform() -> std::vector<std::string>
{
    auto result = data_;
    for (auto &s : result)
    {
        if (s.empty())
            s = "empty";
        else
            s = s + "_processed"; // string class + "..."
    }
    return result;
}