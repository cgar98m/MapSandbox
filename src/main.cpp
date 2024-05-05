#include "data/package/Container.h"
#include "utils/print/ConsolePrinter.h"
#include "utils/random/Sampler.h"
//#include "utils/package/Serializer.h"

int main(int argc, char **argv)
{
    Data::PackagesMap packages = Utils::Sampler< Data::PackagesMap >().make();
    
    Utils::ConsolePrinter< Data::PackagesMap > packages_printer(packages);
    packages_printer.print();

    /*Data::Serializer<Data::PackageContainer> s(packages);
    BYTE*  buff      = NULL;
    size_t buff_size = 0L;
    bool result = s.serialize(buff, buff_size, true);*/

    return 0;
}
