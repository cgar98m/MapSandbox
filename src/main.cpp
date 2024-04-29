#include "data/package/Package.h"
#include "utils/package/Sampler.h"
#include "utils/package/console/ConsolePrinter.h"
#include "utils/package/Serializer.h"

int main(int argc, char **argv)
{
    NSPackage::PackageContainer packages = NSPackage::getSamplePackages();
    NSPackage::displayPackages(packages);

    NSPackage::Serializer<NSPackage::PackageContainer> s(packages);
    BYTE*  buff      = NULL;
    size_t buff_size = 0L;
    bool result = s.serialize(buff, buff_size, true);

    return 0;
}
