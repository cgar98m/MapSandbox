#ifndef _DATA_PACKAGE_COMPONENT_H_
#define _DATA_PACKAGE_COMPONENT_H_

#include <cstdint>
#include <string>

namespace Data
{

/****************************
 * DATA MODEL
 ****************************/
struct ComponentKey
{
    ComponentKey();
    ComponentKey(const ComponentKey& key);

    uint32_t id;
    uint32_t version;
};

struct ComponentData
{
    ComponentData();
    ComponentData(const ComponentData& data);

    std::string description;
    std::string path;
};

struct Component
{
    Component();
    Component(const Component& component);
    Component(const ComponentKey& key, const ComponentData& data);

    ComponentKey  key;
    ComponentData data;
};

};

#endif
