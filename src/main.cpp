#include <iostream>
#include <vector>
#include <string>
#include <fmt/core.h>
#include "TablePrinter.hpp"

int main()
{
    using namespace dmf::tableprinter;

    Printer printer("BTC: INTRADAY TIME SERIES EXAMPLE TITLE",
                    {"Timestamp", "Open", "High", "Low", "Close", "Volume"});
    for (auto &col : printer.columns)
        col.setWidth(15);
    printer.format();
    printer.printHeading();

    std::vector<double> dat = {1615512600, 698.00, 699.00,
                               698.71,     699.00, 11276};

    printer.printDataRow(dat);

    return 0;
}