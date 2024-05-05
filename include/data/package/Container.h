#ifndef _DATA_PACKAGE_CONTAINER_H_
#define _DATA_PACKAGE_CONTAINER_H_

#include <map>
#include <vector>

#include "data/package/Component.h"
#include "data/package/Package.h"

namespace Data
{

/****************************
 * CONTAINERS
 ****************************/

/*
 * COMPONENT MAP CONTAINER
 */
bool operator<(const ComponentKey& lhs, const ComponentKey& rhs);

typedef std::map< ComponentKey, ComponentData > ComponentsMap;
typedef ComponentsMap::const_iterator           ComponentsMapConstIter;
typedef ComponentsMap::iterator                 ComponentsMapIter;

/*
 * COMPONENT VECTOR CONTAINER
 */
bool operator==(const Component& lhs, const Component& rhs);

typedef std::vector< Component >         ComponentsVector;
typedef ComponentsVector::const_iterator ComponentsVectorConstIter;
typedef ComponentsVector::iterator       ComponentsVectorIter;

/*
 * COMPONENT FINDER
 */
struct ComponentFinder
{
    ComponentFinder(const ComponentKey& key);
    ComponentFinder(const Component& component);
    
    bool operator()(const ComponentKey& key);
    bool operator()(const Component& component);
    bool operator()(const std::pair< ComponentKey, ComponentData >& component);

private:
    const ComponentKey& key;
};

/*
 * PACKAGE MAP CONTAINER
 */
bool operator<(const PackageKey& lhs, const PackageKey& rhs);

typedef std::map< PackageKey, PackageData< ComponentsMap > > PackagesMap;
typedef PackagesMap::const_iterator                          PackagesMapConstIter;
typedef PackagesMap::iterator                                PackagesMapIter;

/*
 * PACKAGE VECTOR CONTAINER
 */
bool operator==(const Package< ComponentsVector >& lhs, const Package< ComponentsVector >& rhs);

typedef std::vector< Package< ComponentsVector > > PackagesVector;
typedef PackagesVector::const_iterator             PackagesVectorConstIter;
typedef PackagesVector::iterator                   PackagesVectorIter;

/*
 * PACKAGE FINDER
 */
template < class ComponentContainer >
struct PackageFinder
{
    PackageFinder(const PackageKey& key)
        : key(key)
    {
    }

    PackageFinder(const Package< ComponentContainer >& package)
        : key(package.key)
    {
    }
    
    bool operator()(const PackageKey& key)
    {
        return key.id == this->key.id && key.version == this->key.version;
    }
    
    bool operator()(const Package< ComponentContainer >& package)
    {
        return operator()(package.key);
    }

    bool operator()(const std::pair< PackageKey, PackageData< ComponentContainer > >& package)
    {
        return operator()(package.first);
    }

private:
    const PackageKey& key;
};

};

#endif
