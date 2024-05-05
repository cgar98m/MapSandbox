#ifndef _DATA_PACKAGE_PACKAGE_H_
#define _DATA_PACKAGE_PACKAGE_H_

#include <cstdint>
#include <string>

#include <windows.h>

namespace Data
{

/****************************
 * DATA MODEL
 ****************************/
struct PackageKey
{
    PackageKey();
    PackageKey(const PackageKey& key);

    uint32_t id;
    uint32_t version;
};

template < class ComponentContainer >
struct PackageData
{
    PackageData()
        : installing(false)
        , current(false)
        , owner(0)
        , description()
        , activation_date()
        , install_date()
        , components()
    {
    }

    PackageData(const PackageData& data)
        : installing(data.installing)
        , current(data.current)
        , owner(data.owner)
        , description(data.description)
        , activation_date(data.activation_date)
        , install_date(data.install_date)
        , components(data.components.begin(), data.components.end())
    {
    }

    PackageData& operator=(const PackageData& data)
    {
        if (this != &data)
        {
            installing      = data.installing;
            current         = data.current;
            owner           = data.owner;
            description     = data.description;
            activation_date = data.activation_date;
            install_date    = data.install_date;
            components      = data.components;
        }

        return *this;
    }

    bool               installing;          // Run-time info
    bool               current;
    uint32_t           owner;
    std::string        description;
    SYSTEMTIME         activation_date;
    SYSTEMTIME         install_date;
    ComponentContainer components;
};

template < class ComponentContainer >
struct Package
{
    Package()
        : key()
        , data()
    {
    }

    Package(const Package& package)
        : key(package.key)
        , data(package.data)
    {
    }
    
    Package(const PackageKey& key, const PackageData< ComponentContainer >& data)
        : key(key)
        , data(data)
    {
    }

    Package& operator=(const Package& package)
    {
        if (this != &package)
        {
            key  = package.key;
            data = package.data;
        }

        return *this;
    }

    PackageKey                        key;
    PackageData< ComponentContainer > data;
};

};

#endif
