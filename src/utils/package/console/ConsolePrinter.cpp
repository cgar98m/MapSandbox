#include "utils/package/console/ConsolePrinter.h"

#include <iomanip>
#include <iostream>
#include <sstream>

namespace NSPackage
{

void displayComponents(const ComponentContainer& components, std::string pad)
{
    std::cout << pad << "Components:" << std::endl;

    std::string c_pad = pad + " ";
    for (CompContConstIter it_comp = components.begin(); it_comp != components.end(); ++it_comp)
    {
        displayComponent(*it_comp, c_pad);
    }
}

void displayComponent(const Component& component, std::string pad)
{
    std::string c_key_pad  = pad + " ";
    std::string c_data_pad = c_key_pad + " ";

    const ComponentKey&  c_key  = component.first;
    const ComponentData& c_data = component.second;

    std::cout << c_key_pad << "Component: " << c_key.id << "-" << c_key.version << std::endl;

    std::cout << c_data_pad << "description: " << c_data.description << std::endl;
    std::cout << c_data_pad << "path:        " << c_data.path        << std::endl;
}

void displayPackages(const PackageContainer& packages, std::string pad)
{
    std::cout << pad << "Packages:" << std::endl;

    std::string p_pad = pad + " ";
    for (PackContConstIter it_pack = packages.begin(); it_pack != packages.end(); ++it_pack)
    {
        displayPackage(*it_pack, p_pad);
    }
}

void displayPackage(const Package& package, std::string pad)
{
    std::string p_key_pad  = pad + " ";
    std::string p_data_pad = p_key_pad + " ";

    const PackageKey&  p_key  = package.first;
    const PackageData& p_data = package.second;

    std::cout << p_key_pad << "Package: " << p_key.id << "-" << p_key.version << std::endl;

    std::cout << p_data_pad << "current:         " << p_data.current     << std::endl;
    std::cout << p_data_pad << "installing:      " << p_data.installing  << std::endl;
    std::cout << p_data_pad << "owner:           " << p_data.owner       << std::endl;
    std::cout << p_data_pad << "description:     " << p_data.description << std::endl;

    std::cout << p_data_pad << "activation_date: "
                << std::setfill('0') << std::setw(2) << p_data.activation_date.wDay          << "/"
                << std::setfill('0') << std::setw(2) << p_data.activation_date.wMonth        << "/"
                << std::setfill('0') << std::setw(4) << p_data.activation_date.wYear         << " "
                << std::setfill('0') << std::setw(2) << p_data.activation_date.wHour         << ":"
                << std::setfill('0') << std::setw(2) << p_data.activation_date.wMinute       << ":"
                << std::setfill('0') << std::setw(2) << p_data.activation_date.wSecond       << "."
                << std::setfill('0') << std::setw(3) << p_data.activation_date.wMilliseconds << std::endl;
    
    std::cout << p_data_pad << "install_date:    "
                << std::setfill('0') << std::setw(2) << p_data.install_date.wDay          << "/"
                << std::setfill('0') << std::setw(2) << p_data.install_date.wMonth        << "/"
                << std::setfill('0') << std::setw(4) << p_data.install_date.wYear         << " "
                << std::setfill('0') << std::setw(2) << p_data.install_date.wHour         << ":"
                << std::setfill('0') << std::setw(2) << p_data.install_date.wMinute       << ":"
                << std::setfill('0') << std::setw(2) << p_data.install_date.wSecond       << "."
                << std::setfill('0') << std::setw(3) << p_data.install_date.wMilliseconds << std::endl;

    displayComponents(p_data.components, p_data_pad);
}

};
