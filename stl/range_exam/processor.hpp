#pragma once
#include <string>
#include <vector>

class Processor
{
public:
    Processor(std::vector<std::string> data);
    auto transform() -> std::vector<std::string>;
    template <typename T>
    auto compute(T value) const -> T
    {
        if constexpr (std::is_integral_v<T>)
            return value * 2;
        else if constexpr (std::is_floating_point_v<T>)
            return value / 2;
        else
            return value;
    }

private:
    std::vector<std::string> data_;
};