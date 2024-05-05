#include "data/package/Package.h"

#include "data/package/Container.h"

namespace Data
{

/****************************
 * DATA MODEL
 ****************************/

/*
 * PackageKey
 */
PackageKey::PackageKey()
    : id()
    , version()
{
}

PackageKey::PackageKey(const PackageKey& key)
    : id(key.id)
    , version(key.version)
{
}

};
