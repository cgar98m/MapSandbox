#include "data/package/Component.h"

namespace Data
{

/****************************
 * DATA MODEL
 ****************************/

/*
 * ComponentKey
 */
ComponentKey::ComponentKey()
    : id()
    , version()
{
}

ComponentKey::ComponentKey(const ComponentKey& key)
    : id(key.id)
    , version(key.version)
{
}

/*
 * ComponentData
 */
ComponentData::ComponentData()
    : description()
    , path()
{
}

ComponentData::ComponentData(const ComponentData& data)
    : description(data.description)
    , path(data.path)
{
}

/*
 * Component
 */
Component::Component()
    : key()
    , data()
{
}

Component::Component(const Component& component)
    : key(component.key)
    , data(component.data)
{
}

Component::Component(const ComponentKey& key, const ComponentData& data)
    : key(key)
    , data(data)
{
}

};
