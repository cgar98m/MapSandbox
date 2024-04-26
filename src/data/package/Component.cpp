#include "data/package/Component.h"

namespace NSPackage
{

ComponentCompare::ComponentCompare(const Component& component)
    : component_(component)
{
}

bool ComponentCompare::operator()(const Component& component) const
{
    return component_.first.id == component.first.id
        && component_.first.version == component.first.version;
}

bool operator<(const ComponentKey& lhs, const ComponentKey& rhs)
{
    return lhs.id < rhs.id
        || lhs.id == rhs.id && lhs.version <= rhs.version;
}

};
