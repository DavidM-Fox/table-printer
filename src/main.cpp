#include <iostream>
#include <vector>
#include <string>
#include <fmt/core.h>
#include "TablePrinter.hpp"

int main()
{
    using namespace dmf::tableprinter;

    std::vector<std::pair<std::string, double>> form = {
        {"Timestamp:", 1615442400},
        {"Open:", 9543},
        {"High:", 9321},
        {"Low:", 9532}};

    FormPrinter printer("DATA", form);
    printer.autoFormat();
    printer.print();

    return 0;
}