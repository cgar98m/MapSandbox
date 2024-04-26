#ifndef _UTILS_PACKAGE_SAMPLER_H_
#define _UTILS_PACKAGE_SAMPLER_H_

#include "data/package/component.h"
#include "data/package/package.h"

namespace NSPackage
{

ComponentContainer getSampleComponents();
Component getSampleComponent(uint32_t id, uint32_t version);

PackageContainer getSamplePackages();
Package getSamplePackage(uint32_t id, uint32_t version);

};

#endif
