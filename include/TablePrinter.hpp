#ifndef TABLEPRINTER_H
#define TABLEPRINTER_H
#include <vector>
#include <string>
#include <fmt/core.h>

// namespace DavidM-Fox
namespace dmf {

// namespace tableprinter
namespace tableprinter {

enum class Align { LEFT, RIGHT, CENTER };
enum class Separator { LEFT, RIGHT, BOTH, NONE };
enum class HPolicy { MIN, MAX, SET };

class Component {
public:
    Component(const Align &alignment, const size_t &width,
              const HPolicy &h_policy)
        : alignment(alignment), h_policy(h_policy), width(width),
          separator(Separator::NONE), new_line("")
    {
    }

    virtual void format() = 0;
    virtual void display() = 0;

    void setNewLine(const bool &new_line)
    {
        if (new_line)
            this->new_line = "\n";
        else
            this->new_line = "";
    }

    Align alignment;
    HPolicy h_policy;
    size_t width;
    Separator separator;

protected:
    std::string new_line;

    std::string autoFormat()
    {
        std::string w_str;
        if (separator == Separator::BOTH)
            w_str = std::to_string(width - 2);
        else if (separator == Separator::NONE)
            w_str = std::to_string(width);
        else
            w_str = std::to_string(width - 1);

        return format_begin(separator) + format_alignment(alignment) + w_str +
               format_end(separator) + new_line;
    }

    static const bool stringReplace(std::string &str, const std::string &from,
                                    const std::string &to)
    {
        size_t start = str.find(from);
        if (start == std::string::npos) {
            return false;
        }
        str.replace(start, from.length(), to);
        return true;
    }

private:
    static const std::string format_alignment(const Align &index)
    {
        static const std::string a[] = {"<", ">", "^"};
        return a[static_cast<int>(index)];
    }

    static const std::string format_begin(const Separator &index)
    {
        if (index == Separator::LEFT || index == Separator::BOTH)
            return "|{:";
        else
            return "{:";
    }

    static const std::string format_end(const Separator &index)
    {
        if (index == Separator::RIGHT || index == Separator::BOTH)
            return "}|";
        else
            return "}";
    }
};

class TextBox : public Component {
public:
    TextBox(const std::string &text, const Align &alignment,
            const HPolicy &h_policy, const size_t &width)
        : Component(alignment, width, h_policy), text(text), fmt_string("")
    {
    }

    void format() override { fmt_string = autoFormat(); }

    void display() override { fmt::print(fmt_string, text); }

    std::string text;
    std::string fmt_string;
};

class Title : public TextBox {
public:
    Title(const std::string &text, const Align &alignment,
          const HPolicy &h_policy, const size_t &width)
        : TextBox(text, alignment, h_policy, width)
    {
        this->separator = Separator::BOTH;
        this->setNewLine(true);
        this->format();
    }
};

class Headers : public Component {
public:
    Headers(const std::vector<std::string> &headers, const Align &alignment,
            const size_t &cell_width)
        : Component(alignment, cell_width * headers.size() + 1, HPolicy::MIN)
    {
        for (auto &text : headers) {
            TextBox header{text, alignment, HPolicy::SET, cell_width};
            header.separator = Separator::LEFT;
            header.setNewLine(false);
            this->headers.push_back(header);
        }
        this->format();
    }

    void format() override
    {
        for (auto &header : headers) {
            header.format();
        }
    }

    void display() override
    {
        for (auto &header : headers) {
            header.display();
        }
        std::cout << "|\n";
    }

    std::vector<TextBox> headers;
};

class Printer {
public:
    Printer() : table_title(nullptr), table_headers(nullptr), max_table_width(0)
    {
    }

    ~Printer() {}

    void setTitle(const std::string &title, const Align &alignment,
                  const HPolicy &h_policy = HPolicy::MAX,
                  const size_t width = 0)
    {
        table_title.reset(new Title(title, alignment, h_policy, width));
    }

    void setHeaders(const std::vector<std::string> &headers,
                    const Align &alignment, const size_t width = 0)
    {
        table_headers.reset(new Headers(headers, alignment, width));
    }

    void display() { formatTitleHeadersBox(); }

    std::unique_ptr<Title> table_title;
    std::unique_ptr<Headers> table_headers;

private:
    void formatTitleHeadersBox()
    {
        if (table_title != nullptr) {
            std::cout << std::string(table_title->width, '-') << '\n';
            this->table_title->display();
            if (table_headers != nullptr) {
                size_t width =
                    std::max(table_title->width, table_headers->width);
                std::cout << std::string(width, '-') << '\n';
                this->table_headers->display();
            }
        }
        else if (table_headers != nullptr) {
            std::cout << std::string(table_headers->width, '-') << '\n';
            this->table_headers->display();
        }
    }

    size_t max_table_width;
};

} // namespace tableprinter
} // namespace dmf
#endif // !TABLEPRINTER_H
