#include <iostream>
#include <vector>
#include <string>
#include "TablePrinter.hpp"

int main()
{
    using namespace dmf::tableprinter;

    Printer printer;

    printer.setTitle("Test Table Title", Align::CENTER, HPolicy::MAX, 30);
    std::vector<std::string> headers{"header1", "header2", "header3"};
    printer.setHeaders(headers, Align::CENTER, 20);

    printer.display();

    return 0;
}