#ifndef TABLEPRINTER_H
#define TABLEPRINTER_H
#include <iostream>
#include <vector>
#include <string>
#include <fmt/core.h>

// namespace DavidM-Fox
namespace dmf {

// namespace tableprinter
namespace tableprinter {

enum class Align { LEFT, RIGHT, CENTER };
enum class Separator { LEFT, RIGHT, BOTH, NONE };

class Component {
public:
    Component() {}

    virtual void format() = 0;

    class Format {
    public:
        Format(const Separator &sep = Separator::NONE,
               const Align &alignment = Align::CENTER, const size_t &width = 0,
               const std::string &additional = "")
            : separator(sep), alignment(alignment), width(width),
              additional(additional)
        {
        }

        const std::string &operator()() { return fmt_string; }

        void format()
        {
            std::string fmt = "{:" +
                              fmt::format("{}{}{}", align_char(alignment),
                                          width, additional) +
                              "}";
            fmt_string = fmt::format(sep_string(separator), fmt);
        }

        Separator separator;
        Align alignment;
        std::string additional;
        std::string fmt_string;
        size_t width;
    };

protected:
    static const std::string align_char(const Align &index)
    {
        static const std::string a[] = {"<", ">", "^"};
        return a[static_cast<int>(index)];
    }

    static const std::string sep_string(const Separator &index)
    {
        static const std::string a[] = {"|{}", "{}|", "|{}|", "{}"};
        return a[static_cast<int>(index)];
    }
};

class Column : Component {
public:
    Column()
        : header_text("HEADER TEXT"), header_fmt({}), data_fmt({}),
          column_width(header_text.size() + 2)
    {
    }
    Column(const std::string &header_text,
           const Component::Format &header_fmt = {},
           const Component::Format &data_fmt = {})
        : header_text(header_text), header_fmt(header_fmt), data_fmt(data_fmt),
          column_width(header_text.size() + 2)
    {
    }

    void format() override
    {
        formatHeader();
        formatData();
    }
    void formatHeader() { header_fmt.format(); }
    void formatData() { data_fmt.format(); }

    void setWidth(const size_t &width = 0)
    {
        if (width == 0 || width < header_text.size() + 2)
            column_width = header_text.size() + 2;
        else
            column_width = width;
        header_fmt.width = column_width;
        data_fmt.width = column_width;
    }
    const size_t &getWidth() { return column_width; }

    std::string header_text;
    Component::Format header_fmt;
    Component::Format data_fmt;

private:
    size_t column_width;
};

class Title : public Component {
public:
    Title(const std::string &text, const Component::Format &title_fmt = {})
        : text(text), fmt(title_fmt), width(text.size() + 2)
    {
    }

    void format() override
    {
        fmt.width = width;
        fmt.format();
    }

    void setWidth(const size_t &width = 0)
    {
        if (width == 0 || width < text.size() + 2)
            this->width = text.size() + 2;
        else
            this->width = width;
    }

    const size_t &getWidth() { return width; }

    std::string text;
    Component::Format fmt;

private:
    size_t width;
};

class Printer {
public:
    Printer(const std::string &title, const std::vector<std::string> &headers)
        : title(title, {Separator::BOTH, Align::CENTER, title.size() + 2, ""})
    {
        for (auto &text : headers) {
            size_t width = text.size() + 2;
            columns.push_back({text,
                               {Separator::LEFT, Align::CENTER, width, ""},
                               {Separator::LEFT, Align::CENTER, width, ""}});
        }
    }

    void format()
    {
        headers_str = "";

        for (auto &col : columns) {
            col.format();
            headers_str += fmt::format(col.header_fmt(), col.header_text);
        }
        headers_str += "|";

        title.setWidth(std::max(title.getWidth(), headers_str.size() - 2));
        title.format();
        title_str = fmt::format(title.fmt(), title.text);
    }

    void printHeading()
    {
        format();
        std::cout << std::string(title_str.size(), '-') << "\n";
        std::cout << title_str << "\n";
        std::cout << std::string(std::max(title_str.size(), headers_str.size()),
                                 '-')
                  << "\n";
        std::cout << headers_str << "\n";
        std::cout << std::string(headers_str.size(), '-') << "\n";
    }

    void printDataRow(const std::vector<double> &data)
    {
        if (data.size() != columns.size()) {
            std::cerr << "error here......\n";
            return;
        }

        for (size_t i = 0; i < data.size(); ++i) {
            fmt::print(columns[i].data_fmt(), data[i]);
        }
        std::cout << "|\n";
    }

    Title title;
    std::vector<Column> columns;

private:
    std::string title_str;
    std::string headers_str;
};

} // namespace tableprinter
} // namespace dmf
#endif // !TABLEPRINTER_H
