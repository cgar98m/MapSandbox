#ifndef _UTILS_PACKAGE_CONSOLE_CONSOLEPRINTER_H_
#define _UTILS_PACKAGE_CONSOLE_CONSOLEPRINTER_H_

#include <string>

#include "data/package/Component.h"
#include "data/package/Package.h"

namespace NSPackage
{

void displayComponents(const ComponentContainer& components, std::string pad = "");
void displayComponent(const Component& component, std::string pad = "");

void displayPackages(const PackageContainer& packages, std::string pad = "");
void displayPackage(const Package& package, std::string pad = "");

};

#endif
