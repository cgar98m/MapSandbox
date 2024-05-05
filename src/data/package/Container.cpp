#include "data/package/Container.h"

namespace Data
{

/****************************
 * CONTAINERS
 ****************************/

/*
 * COMPONENT MAP CONTAINER
 */
bool operator<(const ComponentKey& lhs, const ComponentKey& rhs)
{
    return (lhs.id < rhs.id) || (lhs.id == rhs.id && lhs.version <= rhs.version);
}

/*
 * COMPONENT VECTOR CONTAINER
 */
bool operator==(const Component& lhs, const Component& rhs)
{
    return lhs.key.id == rhs.key.id && lhs.key.version == rhs.key.version;
}

/*
 * COMPONENT FINDER
 */
ComponentFinder::ComponentFinder(const ComponentKey& key)
    : key(key)
{
}

ComponentFinder::ComponentFinder(const Component& component)
    : key(component.key)
{
}

bool ComponentFinder::operator()(const ComponentKey& key)
{
    return key.id == this->key.id && key.version == this->key.version;
}

bool ComponentFinder::operator()(const Component& component)
{
    return operator()(component.key);
}

bool ComponentFinder::operator()(const std::pair< ComponentKey, ComponentData >& component)
{
    return operator()(component.first);
}

/*
 * PACKAGE MAP CONTAINER
 */
bool operator<(const PackageKey& lhs, const PackageKey& rhs)
{
    return (lhs.id < rhs.id) || (lhs.id == rhs.id && lhs.version < rhs.version);
}

/*
 * PACKAGE VECTOR CONTAINER
 */
bool operator==(const Package< ComponentsVector >& lhs, const Package< ComponentsVector >& rhs)
{
    return lhs.key.id == rhs.key.id && lhs.key.version == rhs.key.version;
}

};
