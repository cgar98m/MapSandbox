#include "utils/package/Sampler.h"

#include <sstream>

#define UTILS_PACKAGE_SAMPLER_COMP_ID_BASE  101
#define UTILS_PACKAGE_SAMPLER_COMP_ID_MAX   102
#define UTILS_PACKAGE_SAMPLER_COMP_VER_BASE 1
#define UTILS_PACKAGE_SAMPLER_COMP_VER_MAX  2

#define UTILS_PACKAGE_SAMPLER_PACK_ID_BASE  205
#define UTILS_PACKAGE_SAMPLER_PACK_ID_MAX   206
#define UTILS_PACKAGE_SAMPLER_PACK_VER_BASE 18
#define UTILS_PACKAGE_SAMPLER_PACK_VER_MAX  19

namespace NSPackage
{

ComponentContainer getSampleComponents()
{
    ComponentContainer cs;

    for (uint32_t id = UTILS_PACKAGE_SAMPLER_COMP_ID_BASE; id <= UTILS_PACKAGE_SAMPLER_COMP_ID_MAX; ++id)
    {
        for (uint32_t version = UTILS_PACKAGE_SAMPLER_COMP_VER_BASE; version <= UTILS_PACKAGE_SAMPLER_COMP_VER_MAX; ++version)
        {
            cs.insert(getSampleComponent(id, version));
        }
    }

    return cs;
}

Component getSampleComponent(uint32_t id, uint32_t version)
{
    Component      c;
    ComponentKey&  c_key  = c.first;
    ComponentData& c_data = c.second;

    c_key.id      = id;
    c_key.version = version;

    std::stringstream ss;
    ss << c_key.id << "-" << c_key.version;

    c_data.description = ss.str() + "_description";
    c_data.path        = ss.str() + "_path";

    return c;
}

PackageContainer getSamplePackages()
{
    PackageContainer ps;

    for (uint32_t id = UTILS_PACKAGE_SAMPLER_PACK_ID_BASE; id <= UTILS_PACKAGE_SAMPLER_PACK_ID_MAX; ++id)
    {
        for (uint32_t version = UTILS_PACKAGE_SAMPLER_PACK_VER_BASE; version <= UTILS_PACKAGE_SAMPLER_PACK_VER_MAX; ++version)
        {
            ps.insert(getSamplePackage(id, version));
        }
    }

    return ps;
}

Package getSamplePackage(uint32_t id, uint32_t version)
{
    Package      p;
    PackageKey&  p_key  = p.first;
    PackageData& p_data = p.second;

    p_key.id      = id;
    p_key.version = version;

    std::stringstream ss;
    ss << p_key.id << "-" << p_key.version;

    p_data.current     = static_cast<bool>((p_key.id + p_key.version) % 2);
    p_data.installing  = false;
    p_data.owner       = p_key.id + p_key.version;
    p_data.description = ss.str() + "_description";

    p_data.activation_date.wYear         = 2024;
    p_data.activation_date.wMonth        = 4;
    p_data.activation_date.wDayOfWeek    = 3;
    p_data.activation_date.wDay          = 24;
    p_data.activation_date.wHour         = 23;
    p_data.activation_date.wMinute       = 12;
    p_data.activation_date.wSecond       = 25;
    p_data.activation_date.wMilliseconds = 0;

    p_data.install_date.wYear         = 0;
    p_data.install_date.wMonth        = 0;
    p_data.install_date.wDayOfWeek    = 0;
    p_data.install_date.wDay          = 0;
    p_data.install_date.wHour         = 0;
    p_data.install_date.wMinute       = 0;
    p_data.install_date.wSecond       = 0;
    p_data.install_date.wMilliseconds = 0;

    p_data.components = getSampleComponents();

    return p;
}

};
