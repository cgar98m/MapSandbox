#include "data/package/Container.h"
#include "utils/print/ConsolePrinter.h"
#include "utils/random/Sampler.h"
#include "utils/Serializer.h"

int main(int argc, char **argv)
{
    Data::PackagesMap packages = Utils::Sampler< Data::PackagesMap >().make();
    
    Utils::ConsolePrinter< Data::PackagesMap > packages_printer(packages);
    packages_printer.print();

    BYTE*  buff        = NULL;
    size_t buff_cursor = 0;
    size_t buff_size   = 0;
    Utils::Serializer< Data::PackagesMap > packages_serializer(packages, buff, buff_cursor, buff_size);
    bool result = packages_serializer.serialize(true);
    
    if (buff != NULL) delete [] buff;
    return 0;
}
