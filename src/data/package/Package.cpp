#include "data/package/Package.h"

namespace NSPackage
{

PackageCompare::PackageCompare(const Package& package)
    : package_(package)
{
}

bool PackageCompare::operator()(const Package& package) const
{
    return package_.first.id == package.first.id
        && package_.first.version == package.first.version;
}

bool operator<(const PackageKey& lhs, const PackageKey& rhs)
{
    return lhs.id < rhs.id
        || lhs.id == rhs.id && lhs.version <= rhs.version;
}

};
