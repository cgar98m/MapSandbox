#ifndef _DATA_PACKAGE_COMPONENT_H_
#define _DATA_PACKAGE_COMPONENT_H_

#include <cstdint>
#include <map>
#include <string>

namespace NSPackage
{

struct ComponentKey
{
    uint32_t id;
    uint32_t version;
};

struct ComponentData
{
    std::string description;
    std::string path;
};

typedef std::pair< ComponentKey, ComponentData > Component;
typedef std::map< ComponentKey, ComponentData >  ComponentContainer;
typedef ComponentContainer::const_iterator       CompContConstIter;
typedef ComponentContainer::iterator             CompContIter;

struct ComponentCompare
{
    ComponentCompare(const Component& component);

    bool operator()(const Component& component) const;

private:
    const Component component_;
};

bool operator<(const ComponentKey& lhs, const ComponentKey& rhs);

};

#endif
