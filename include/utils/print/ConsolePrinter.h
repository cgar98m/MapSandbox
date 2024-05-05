#ifndef _UTILS_PRINT_CONSOLEPRINTER_H_
#define _UTILS_PRINT_CONSOLEPRINTER_H_

#include <string>

namespace Utils
{

/****************************
 * CONSOLE PRINTING
 ****************************/
template < class Data >
class ConsolePrinter
{
public:
    ConsolePrinter(const Data& data)
        : data_(data)
    {
    }

    void print(std::string padding = "");

private:
    const Data& data_;
};

};

#endif
