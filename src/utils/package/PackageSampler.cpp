#include "utils/random/Sampler.h"

#include <algorithm>
#include <sstream>

#include "data/package/Container.h"

#define MIN_COMPONENTS        1
#define MAX_COMPONENTS        4
#define MIN_COMPONENT_ID      1
#define MAX_COMPONENT_ID      1000
#define MIN_COMPONENT_VERSION 1
#define MAX_COMPONENT_VERSION 1000

#define MIN_PACKAGES        1
#define MAX_PACKAGES        3
#define MIN_PACKAGE_ID      1
#define MAX_PACKAGE_ID      1000
#define MIN_PACKAGE_VERSION 1
#define MAX_PACKAGE_VERSION 1000

namespace Utils
{

/****************************
 * SAMPLES GENERATION
 ****************************/

/*
 * Sampler::make< Data::ComponentsMap >
 */
template class Sampler< Data::ComponentsMap >;

template <>
Data::ComponentsMap Sampler< Data::ComponentsMap >::make()
{
    Data::ComponentsMap data;
    Data::Component     data_child;

    size_t data_total = randomizer_.get32bNumber(MIN_COMPONENTS, MAX_COMPONENTS);
    while (data_total-- > 0)
    {
        data_child = Sampler< Data::Component >().make();
        while (std::find_if(data.begin(), data.end(), Data::ComponentFinder(data_child)) != data.end())
        {
            data_child.key = Sampler< Data::ComponentKey >().make();
        }

        data.insert(std::pair< Data::ComponentKey, Data::ComponentData >(data_child.key, data_child.data));
    }

    return data;
}

/*
 * Sampler::make< Data::ComponentsVector >
 */
template class Sampler< Data::ComponentsVector >;

template <>
Data::ComponentsVector Sampler< Data::ComponentsVector >::make()
{
    Data::ComponentsVector data;
    Data::Component        data_child;

    size_t data_total = randomizer_.get32bNumber(MIN_COMPONENTS, MAX_COMPONENTS);
    while (data_total-- > 0)
    {
        data_child = Sampler< Data::Component >().make();
        while (std::find_if(data.begin(), data.end(), Data::ComponentFinder(data_child)) != data.end())
        {
            data_child.key = Sampler< Data::ComponentKey >().make();
        }

        data.push_back(data_child);
    }

    return data;
}

/*
 * Sampler::make< Data::Component >
 */
template class Sampler< Data::Component >;

template <>
Data::Component Sampler< Data::Component >::make()
{
    return Data::Component(Sampler< Data::ComponentKey >().make(), Sampler< Data::ComponentData >().make());
}

/*
 * Sampler::make< Data::ComponentKey >
 */
template class Sampler< Data::ComponentKey >;

template <>
Data::ComponentKey Sampler< Data::ComponentKey >::make()
{
    Data::ComponentKey data;

    data.id      = randomizer_.get32bNumber(MIN_COMPONENT_ID, MAX_COMPONENT_ID);
    data.version = randomizer_.get32bNumber(MIN_COMPONENT_VERSION, MAX_COMPONENT_VERSION);

    return data;
}

/*
 * Sampler::make< Data::ComponentData >
 */
template class Sampler< Data::ComponentData >;

template <>
Data::ComponentData Sampler< Data::ComponentData >::make()
{
    Data::ComponentData data;

    data.description = randomizer_.getString();
    data.path        = randomizer_.getString();

    return data;
}

/*
 * Sampler::make< Data::PackagesMap >
 */
template class Sampler< Data::PackagesMap >;

template <>
Data::PackagesMap Sampler< Data::PackagesMap >::make()
{
    Data::PackagesMap                    data;
    Data::Package< Data::ComponentsMap > data_child;

    size_t data_total = randomizer_.get32bNumber(MIN_PACKAGES, MAX_PACKAGES);
    while (data_total-- > 0)
    {
        data_child = Sampler< Data::Package< Data::ComponentsMap > >().make();
        while (std::find_if(data.begin(), data.end(), Data::PackageFinder< Data::ComponentsMap >(data_child)) != data.end())
        {
            data_child.key = Sampler< Data::PackageKey >().make();
        }

        data.insert(std::pair< Data::PackageKey, Data::PackageData< Data::ComponentsMap > >(data_child.key, data_child.data));
    }

    return data;
}

/*
 * Sampler::make< Data::PackagesVector >
 */
template class Sampler< Data::PackagesVector >;

template <>
Data::PackagesVector Sampler< Data::PackagesVector >::make()
{
    Data::PackagesVector                    data;
    Data::Package< Data::ComponentsVector > data_child;

    size_t data_total = randomizer_.get32bNumber(MIN_COMPONENTS, MAX_COMPONENTS);
    while (data_total-- > 0)
    {
        data_child = Sampler< Data::Package< Data::ComponentsVector > >().make();
        while (std::find_if(data.begin(), data.end(), Data::PackageFinder< Data::ComponentsVector >(data_child)) != data.end())
        {
            data_child.key = Sampler< Data::PackageKey >().make();
        }

        data.push_back(data_child);
    }

    return data;
}

/*
 * Sampler::make< Data::Package< Data::ComponentsMap > >
 */
template class Sampler< Data::Package< Data::ComponentsMap > >;

template <>
Data::Package< Data::ComponentsMap > Sampler< Data::Package< Data::ComponentsMap > >::make()
{
    return Data::Package< Data::ComponentsMap >(Sampler< Data::PackageKey >().make(),
        Sampler< Data::PackageData< Data::ComponentsMap > >().make());
}

/*
 * Sampler::make< Data::Package< Data::ComponentsVector > >
 */
template class Sampler< Data::Package< Data::ComponentsVector > >;

template <>
Data::Package< Data::ComponentsVector > Sampler< Data::Package< Data::ComponentsVector > >::make()
{
    return Data::Package< Data::ComponentsVector >(Sampler< Data::PackageKey >().make(),
        Sampler< Data::PackageData< Data::ComponentsVector > >().make());
}

/*
 * Sampler::make< Data::PackageKey >
 */
template class Sampler< Data::PackageKey >;

template <>
Data::PackageKey Sampler< Data::PackageKey >::make()
{
    Data::PackageKey data;

    data.id      = randomizer_.get32bNumber(MIN_PACKAGE_ID, MAX_PACKAGE_ID);
    data.version = randomizer_.get32bNumber(MIN_PACKAGE_VERSION, MAX_PACKAGE_VERSION);

    return data;
}

/*
 * Sampler::make< Data::PackageData< Data::ComponentsMap > >
 */
template class Sampler< Data::PackageData< Data::ComponentsMap > >;

template <>
Data::PackageData< Data::ComponentsMap > Sampler< Data::PackageData< Data::ComponentsMap > >::make()
{
    Data::PackageData< Data::ComponentsMap > data;

    data.installing      = randomizer_.getBool();
    data.current         = randomizer_.getBool();
    data.owner           = randomizer_.get32bNumber();
    data.description     = randomizer_.getString();
    data.activation_date = randomizer_.getDate();
    data.install_date    = randomizer_.getDate(data.activation_date);
    data.components      = Sampler< Data::ComponentsMap >().make();

    return data;
}

/*
 * Sampler::make< Data::PackageData< Data::ComponentsVector > >
 */
template class Sampler< Data::PackageData< Data::ComponentsVector > >;

template <>
Data::PackageData< Data::ComponentsVector > Sampler< Data::PackageData< Data::ComponentsVector > >::make()
{
    Data::PackageData< Data::ComponentsVector > data;

    data.installing      = randomizer_.getBool();
    data.current         = randomizer_.getBool();
    data.owner           = randomizer_.get32bNumber();
    data.description     = randomizer_.getString();
    data.activation_date = randomizer_.getDate();
    data.install_date    = randomizer_.getDate(data.activation_date);
    data.components      = Sampler< Data::ComponentsVector >().make();

    return data;
}

};
