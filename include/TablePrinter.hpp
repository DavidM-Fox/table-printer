#ifndef TABLEPRINTER_H
#define TABLEPRINTER_H
#include <vector>
#include <string>
#include "Component.hpp"
#include "Component/Title.hpp"
#include "Component/Headers.hpp"

namespace dmf {

class TablePrinter {
public:
    TablePrinter() : table_title(nullptr), max_table_width(0) {}

    ~TablePrinter() {}

    void setTitle(const std::string &title, const table::Align &alignment,
                  const uint32_t width = 0)
    {
        table_title.reset(new table::Title(title, alignment, width));
    }

    void setHeaders(const std::vector<std::string> &headers) {}

    std::unique_ptr<table::Title> &title() { return table_title; }
    std::unique_ptr<table::Headers> &headers() { return table_headers; }

    void display() { this->table_title->display(); }

private:
    std::unique_ptr<table::Title> table_title;
    std::unique_ptr<table::Headers> table_headers;

    size_t max_table_width;
};

} // namespace dmf
#endif // !TABLEPRINTER_H
