#include "utils/print/ConsolePrinter.h"

#include <iomanip>
#include <iostream>

#include "data/package/Container.h"

namespace Utils
{

/****************************
 * CONSOLE PRINTING
 ****************************/

/*
 * ConsolePrinter< Data::ComponentsMap >
 */
template class ConsolePrinter< Data::ComponentsMap >;

template <>
void ConsolePrinter< Data::ComponentsMap >::print(std::string padding)
{
    std::cout << padding << "Components:" << std::endl;

    std::string padding_child = padding + " ";
    for (Data::ComponentsMapConstIter it = data_.begin(); it != data_.end(); ++it)
    {
        Data::Component data_child(it->first, it->second);
        ConsolePrinter< Data::Component > printer_child(data_child);
        printer_child.print(padding_child);
    }
}

/*
 * ConsolePrinter< Data::ComponentsVector >
 */
template class ConsolePrinter< Data::ComponentsVector >;

template <>
void ConsolePrinter< Data::ComponentsVector >::print(std::string padding)
{
    std::cout << padding << "Components:" << std::endl;

    std::string padding_child = padding + " ";
    for (Data::ComponentsVectorConstIter it = data_.begin(); it != data_.end(); ++it)
    {
        ConsolePrinter< Data::Component > printer_child(*it);
        printer_child.print(padding_child);
    }
}

/*
 * ConsolePrinter< Data::Component >
 */
template class ConsolePrinter< Data::Component >;

template <>
void ConsolePrinter< Data::Component >::print(std::string padding)
{
    std::string key_padding  = padding + " ";
    std::string data_padding = key_padding + " ";

    std::cout << key_padding << "Component: " << data_.key.id << "-" << data_.key.version << std::endl;

    std::cout << data_padding << "description: " << data_.data.description << std::endl;
    std::cout << data_padding << "path:        " << data_.data.path        << std::endl;
}

/*
 * ConsolePrinter< Data::PackagesMap >
 */
template class ConsolePrinter< Data::PackagesMap >;

template <>
void ConsolePrinter< Data::PackagesMap >::print(std::string padding)
{
    std::cout << padding << "Packages:" << std::endl;

    std::string padding_child = padding + " ";
    for (Data::PackagesMapConstIter it = data_.begin(); it != data_.end(); ++it)
    {
        Data::Package< Data::ComponentsMap > data_child(it->first, it->second);
        ConsolePrinter< Data::Package< Data::ComponentsMap > > printer_child(data_child);
        printer_child.print(padding_child);
    }
}

/*
 * ConsolePrinter< Data::Package < Data::ComponentsMap > >
 */
template class ConsolePrinter< Data::Package< Data::ComponentsMap > >;

template <>
void ConsolePrinter< Data::Package< Data::ComponentsMap > >::print(std::string padding)
{
    std::string key_padding  = padding + " ";
    std::string data_padding = key_padding + " ";

    std::cout << key_padding  << "Package: " << data_.key.id << "-" << data_.key.version << std::endl;

    std::cout << data_padding << "installing:      " << data_.data.installing  << std::endl;
    std::cout << data_padding << "current:         " << data_.data.current     << std::endl;
    std::cout << data_padding << "owner:           " << data_.data.owner       << std::endl;
    std::cout << data_padding << "description:     " << data_.data.description << std::endl;

    std::cout << data_padding << "activation_date: "
                << std::setfill('0') << std::setw(2) << data_.data.activation_date.wDay          << "/"
                << std::setfill('0') << std::setw(2) << data_.data.activation_date.wMonth        << "/"
                << std::setfill('0') << std::setw(4) << data_.data.activation_date.wYear         << " "
                << std::setfill('0') << std::setw(2) << data_.data.activation_date.wHour         << ":"
                << std::setfill('0') << std::setw(2) << data_.data.activation_date.wMinute       << ":"
                << std::setfill('0') << std::setw(2) << data_.data.activation_date.wSecond       << "."
                << std::setfill('0') << std::setw(3) << data_.data.activation_date.wMilliseconds << std::endl;
    
    std::cout << data_padding << "install_date:    "
                << std::setfill('0') << std::setw(2) << data_.data.install_date.wDay          << "/"
                << std::setfill('0') << std::setw(2) << data_.data.install_date.wMonth        << "/"
                << std::setfill('0') << std::setw(4) << data_.data.install_date.wYear         << " "
                << std::setfill('0') << std::setw(2) << data_.data.install_date.wHour         << ":"
                << std::setfill('0') << std::setw(2) << data_.data.install_date.wMinute       << ":"
                << std::setfill('0') << std::setw(2) << data_.data.install_date.wSecond       << "."
                << std::setfill('0') << std::setw(3) << data_.data.install_date.wMilliseconds << std::endl;

    ConsolePrinter < Data::ComponentsMap >(data_.data.components).print(data_padding);
}

/*
 * ConsolePrinter< Data::PackagesVector >
 */
template class ConsolePrinter< Data::PackagesVector >;

template <>
void ConsolePrinter< Data::PackagesVector >::print(std::string padding)
{
    std::cout << padding << "Packages:" << std::endl;

    std::string padding_child = padding + " ";
    for (Data::PackagesVectorConstIter it = data_.begin(); it != data_.end(); ++it)
    {
        ConsolePrinter< Data::Package< Data::ComponentsVector > > printer_child(*it);
        printer_child.print(padding_child);
    }
}

/*
 * ConsolePrinter< Data::Package< Data::ComponentsVector > >
 */
template class ConsolePrinter< Data::Package< Data::ComponentsVector > >;

template <>
void ConsolePrinter< Data::Package< Data::ComponentsVector > >::print(std::string padding)
{
    std::string key_padding  = padding + " ";
    std::string data_padding = key_padding + " ";

    std::cout << key_padding  << "Package: " << data_.key.id << "-" << data_.key.version << std::endl;

    std::cout << data_padding << "installing:      " << data_.data.installing  << std::endl;
    std::cout << data_padding << "current:         " << data_.data.current     << std::endl;
    std::cout << data_padding << "owner:           " << data_.data.owner       << std::endl;
    std::cout << data_padding << "description:     " << data_.data.description << std::endl;

    std::cout << data_padding << "activation_date: "
                << std::setfill('0') << std::setw(2) << data_.data.activation_date.wDay          << "/"
                << std::setfill('0') << std::setw(2) << data_.data.activation_date.wMonth        << "/"
                << std::setfill('0') << std::setw(4) << data_.data.activation_date.wYear         << " "
                << std::setfill('0') << std::setw(2) << data_.data.activation_date.wHour         << ":"
                << std::setfill('0') << std::setw(2) << data_.data.activation_date.wMinute       << ":"
                << std::setfill('0') << std::setw(2) << data_.data.activation_date.wSecond       << "."
                << std::setfill('0') << std::setw(3) << data_.data.activation_date.wMilliseconds << std::endl;
    
    std::cout << data_padding << "install_date:    "
                << std::setfill('0') << std::setw(2) << data_.data.install_date.wDay          << "/"
                << std::setfill('0') << std::setw(2) << data_.data.install_date.wMonth        << "/"
                << std::setfill('0') << std::setw(4) << data_.data.install_date.wYear         << " "
                << std::setfill('0') << std::setw(2) << data_.data.install_date.wHour         << ":"
                << std::setfill('0') << std::setw(2) << data_.data.install_date.wMinute       << ":"
                << std::setfill('0') << std::setw(2) << data_.data.install_date.wSecond       << "."
                << std::setfill('0') << std::setw(3) << data_.data.install_date.wMilliseconds << std::endl;

    ConsolePrinter < Data::ComponentsVector >(data_.data.components).print(data_padding);
}

};
