#ifndef _DATA_PACKAGE_PACKAGE_H_
#define _DATA_PACKAGE_PACKAGE_H_

#include <cstdint>
#include <map>
#include <string>

#include <windows.h>

#include "data/package/Component.h"

namespace NSPackage
{

struct PackageKey
{
    uint32_t id;
    uint32_t version;
};

struct PackageData
{
    bool               current;
    bool               installing;
    uint32_t           owner;
    std::string        description;
    SYSTEMTIME         activation_date;
    SYSTEMTIME         install_date;
    ComponentContainer components;
};

typedef std::pair< PackageKey, PackageData > Package;
typedef std::map< PackageKey, PackageData >  PackageContainer;
typedef PackageContainer::const_iterator     PackContConstIter;
typedef PackageContainer::iterator           PackContIter;

struct PackageCompare
{
    PackageCompare(const Package& package);

    bool operator()(const Package& package) const;

private:
    const Package package_;
};

bool operator<(const PackageKey& lhs, const PackageKey& rhs);

};

#endif
