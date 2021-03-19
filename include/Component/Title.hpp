#ifndef TABLETITLE_H
#define TABLETITLE_H
#include <vector>
#include <string>
#include <fmt/core.h>
#include "Component.hpp"

namespace dmf {
namespace table {

class Title : public Component {
public:
    Title(const std::string &title, const Align &alignment, const size_t &width)
        : Component(alignment, width), title(title)
    {
    }

    std::string title;

    void display() override
    {
        std::string format = "|{:";
        format.push_back(alignment_char(alignment));
        format += std::to_string(width - 2) + "}|\n";
        std::cout << std::string(separator, '-') + "\n";
        fmt::print(format, title);
    }
};

} // namespace table
} // namespace dmf
#endif // !TABLETITLE_H
