#ifndef _UTILS_PACKAGE_SERIALIZER_H_
#define _UTILS_PACKAGE_SERIALIZER_H_

#include <iomanip>
#include <iostream>

#include <windows.h>

#include "data/package/Package.h"
#include "utils/package/console/ConsolePrinter.h"

#define UTILS_PACKAGE_SERIALIZER_BUFFER_BASE_SIZE (1024L)
#define UTILS_PACKAGE_SERIALIZER_BUFFER_MAX_SIZE  (static_cast<size_t>(-1))

namespace NSPackage
{

template <class Data>
class Serializer
{
public:
    Serializer(const Data& data);
    ~Serializer();

    bool serialize(BYTE*& buffer_out, size_t& buffer_size_out, bool show_progress = false, std::string pad = "");

private:
    bool updateBuffer(BYTE* buffer_in, size_t buffer_in_size, bool show_progress, std::string pad);

    const Data& data;

    BYTE*  buffer;
    size_t buffer_size;
    size_t buffer_max_size;
};

};

#endif
