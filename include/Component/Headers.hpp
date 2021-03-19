#ifndef TABLEHEADERS_H
#define TABLEHEADERS_H
#include <vector>
#include <string>
#include <fmt/core.h>
#include "Component.hpp"

namespace dmf {
namespace table {

class Headers : public Component {
public:
    Headers(const std::vector<std::string> &headers, const Align &alignment,
            const size_t &width)
        : Component(alignment, width), headers(headers)
    {
    }

    std::vector<std::string> headers;

    void display() override
    {
        std::string format = "|{:";
        format.push_back(alignment_char(alignment));
        format += std::to_string(width - 2) + "}";

        for (auto &header : headers) {
            fmt::print(format, header);
        }
        std::count << "|\n";
    }
};

} // namespace table
} // namespace dmf
#endif // !TABLEHEADERS_H
