#include <iostream>
#include "TablePrinter.hpp"
#include "Component/Title.hpp"

int main()
{
    using namespace dmf::table;

    dmf::TablePrinter printer;
    printer.setTitle("Test Table Title", Align::CENTER, 30);
    printer.title()->title = "WHOOOOOOOOAHHH";
    printer.display();

    return 0;
}