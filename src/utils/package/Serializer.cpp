#include "utils/package/Serializer.h"

namespace NSPackage
{

template Serializer<ComponentContainer>;
template Serializer<Component>;
template Serializer<PackageContainer>;
template Serializer<Package>;

template <class Data>
Serializer<Data>::Serializer(const Data& data)
    : data(data)
    , buffer(NULL)
    , buffer_size(0L)
    , buffer_max_size(0L)
{
}

template <class Data>
Serializer<Data>::~Serializer()
{
    if (buffer) delete [] buffer;
}

template <>
bool Serializer<ComponentContainer>::serialize(BYTE*& buffer_out, size_t& buffer_size_out, bool show_progress, std::string pad)
{
    //Already serialized?
    if (buffer)
    {
        buffer_out      = buffer;
        buffer_size_out = buffer_size;

        if (show_progress)
        {
            std::cout << pad << "Previously serialized:" << std::endl;
            displayComponents(data, pad);
        }

        return true;
    }

    //Begin serialization
    size_t tmp_size = data.size();
    if (show_progress) std::cout << pad << "Serializing components size: " << tmp_size << std::endl;
    if (!updateBuffer((BYTE*) &tmp_size, sizeof(size_t), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing components size" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized components size" << std::endl;

    if (show_progress) std::cout << pad << "Serializing components" << std::endl;
    std::string parent_pad = pad + " ";
    std::string child_pad  = parent_pad + " ";
    for (CompContConstIter it = data.begin(); it != data.end(); ++it)
    {
        Serializer<Component> serializer(*it);
        
        BYTE*  s_buff      = NULL;
        size_t s_buff_size = 0L;
        if (show_progress) std::cout << parent_pad << "Serializing component" << std::endl;
        if (!serializer.serialize(s_buff, s_buff_size, show_progress, child_pad))
        {
            if (show_progress) std::cout << parent_pad << "Error serializing component" << std::endl;
            return false;
        }
        if (show_progress) std::cout << parent_pad << "Serialized component" << std::endl;
        
        if (show_progress) std::cout << parent_pad << "Copying serialized component" << std::endl;
        if (!updateBuffer(s_buff, s_buff_size, show_progress, pad))
        {
            if (show_progress) std::cout << parent_pad << "Error copying serialized component" << std::endl;
            return false;
        }
        if (show_progress) std::cout << parent_pad << "Cpoied serialized component" << std::endl;
    }
    if (show_progress) std::cout << pad << "Serialized components" << std::endl;

    //OK
    buffer_out      = buffer;
    buffer_size_out = buffer_size;

    return true;
}

template <>
bool Serializer<Component>::serialize(BYTE*& buffer_out, size_t& buffer_size_out, bool show_progress, std::string pad)
{
    //Already serialized?
    if (buffer)
    {
        buffer_out      = buffer;
        buffer_size_out = buffer_size;

        if (show_progress)
        {
            std::cout << pad << "Previously serialized:" << std::endl;
            displayComponent(data, pad);
        }

        return true;
    }

    //Begin serialization
    const ComponentKey& key(data.first);
    if (show_progress) std::cout << pad << "Serializing component key: " << key.id << "-" << key.version << std::endl;
    if (!updateBuffer((BYTE*) &key, sizeof(ComponentKey), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing component key" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized component key" << std::endl;

    const ComponentData& info(data.second);
    size_t tmp_size = info.description.size();
    if (show_progress) std::cout << pad << "Serializing description size: " << tmp_size << std::endl;
    if (!updateBuffer((BYTE*) &tmp_size, sizeof(size_t), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing description size" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized description size" << std::endl;

    if (show_progress) std::cout << pad << "Serializing description: " << info.description << std::endl;
    if (!updateBuffer((BYTE*) info.description.c_str(), tmp_size, show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing description" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized description" << std::endl;

    if (tmp_size % 2)
    {
        BYTE tmp_byte = 0;
        if (show_progress) std::cout << pad << "Serializing description padding" << std::endl;
        if (!updateBuffer((BYTE*) &tmp_byte, sizeof(BYTE), show_progress, pad))
        {
            if (show_progress) std::cout << pad << "Error serializing description padding" << std::endl;
            return false;
        }
        if (show_progress) std::cout << pad << "Serialized description padding" << std::endl;
    }

    tmp_size = info.path.size();
    if (show_progress) std::cout << pad << "Serializing path size: " << tmp_size << std::endl;
    if (!updateBuffer((BYTE*) &tmp_size, sizeof(size_t), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing path size" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized path size" << std::endl;

    if (show_progress) std::cout << pad << "Serializing path: " << info.path << std::endl;
    if (!updateBuffer((BYTE*) info.path.c_str(), tmp_size, show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing path" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized path" << std::endl;

    if (tmp_size % 2)
    {
        BYTE tmp_byte = 0;
        if (show_progress) std::cout << pad << "Serializing path padding" << std::endl;
        if (!updateBuffer((BYTE*) &tmp_byte, sizeof(BYTE), show_progress, pad))
        {
            if (show_progress) std::cout << pad << "Error serializing path padding" << std::endl;
            return false;
        }
        if (show_progress) std::cout << pad << "Serialized path padding" << std::endl;
    }

    //OK
    buffer_out      = buffer;
    buffer_size_out = buffer_size;

    return true;
}

template <>
bool Serializer<PackageContainer>::serialize(BYTE*& buffer_out, size_t& buffer_size_out, bool show_progress, std::string pad)
{
    //Already serialized?
    if (buffer)
    {
        buffer_out      = buffer;
        buffer_size_out = buffer_size;

        if (show_progress)
        {
            std::cout << pad << "Previously serialized:" << std::endl;
            displayPackages(data, pad);
        }

        return true;
    }

    //Begin serialization
    size_t tmp_size = data.size();
    if (show_progress) std::cout << pad << "Serializing packages size: " << tmp_size << std::endl;
    if (!updateBuffer((BYTE*) &tmp_size, sizeof(size_t), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing packages size" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized packages size" << std::endl;

    if (show_progress) std::cout << pad << "Serializing packages" << std::endl;
    std::string parent_pad = pad + " ";
    std::string child_pad  = parent_pad + " ";
    for (PackContConstIter it = data.begin(); it != data.end(); ++it)
    {
        Serializer<Package> serializer(*it);
        
        BYTE*  s_buff      = NULL;
        size_t s_buff_size = 0L;
        if (show_progress) std::cout << parent_pad << "Serializing package" << std::endl;
        if (!serializer.serialize(s_buff, s_buff_size, show_progress, child_pad))
        {
            if (show_progress) std::cout << parent_pad << "Error serializing package" << std::endl;
            return false;
        }
        if (show_progress) std::cout << parent_pad << "Serialized package" << std::endl;

        if (show_progress) std::cout << parent_pad << "Copying serialized package" << std::endl;
        if (!updateBuffer(s_buff, s_buff_size, show_progress, pad))
        {
            if (show_progress) std::cout << parent_pad << "Error copying serialized package" << std::endl;
            return false;
        }
        if (show_progress) std::cout << parent_pad << "Cpoied serialized package" << std::endl;
    }
    if (show_progress) std::cout << pad << "Serialized packages" << std::endl;

    //OK
    buffer_out      = buffer;
    buffer_size_out = buffer_size;

    return true;
}

template <>
bool Serializer<Package>::serialize(BYTE*& buffer_out, size_t& buffer_size_out, bool show_progress, std::string pad)
{
    //Already serialized?
    if (buffer)
    {
        buffer_out      = buffer;
        buffer_size_out = buffer_size;

        if (show_progress)
        {
            std::cout << pad << "Previously serialized:" << std::endl;
            displayPackage(data, pad);
        }

        return true;
    }

    //Begin serialization
    const PackageKey& key(data.first);
    if (show_progress) std::cout << pad << "Serializing package key: " << key.id << "-" << key.version << std::endl;
    if (!updateBuffer((BYTE*) &key, sizeof(PackageKey), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing package key" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized package key" << std::endl;

    const PackageData& info(data.second);
    BYTE tmp_byte = static_cast<BYTE>(info.current);
    if (show_progress) std::cout << pad << "Serializing current: " << tmp_byte << std::endl;
    if (!updateBuffer((BYTE*) &tmp_byte, sizeof(BYTE), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing current" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized current" << std::endl;

    tmp_byte = 0;
    if (show_progress) std::cout << pad << "Serializing current padding" << std::endl;
    if (!updateBuffer((BYTE*) &tmp_byte, sizeof(BYTE), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing current padding" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized current padding" << std::endl;

    if (show_progress) std::cout << pad << "Serializing owner: " << info.owner << std::endl;
    if (!updateBuffer((BYTE*) &info.owner, sizeof(uint32_t), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing owner" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized owner" << std::endl;

    size_t tmp_size = info.description.size();
    if (show_progress) std::cout << pad << "Serializing description size: " << tmp_size << std::endl;
    if (!updateBuffer((BYTE*) &tmp_size, sizeof(size_t), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing description size:" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized description size" << std::endl;

    if (show_progress) std::cout << pad << "Serializing description: " << info.description;
    if (!updateBuffer((BYTE*) info.description.c_str(), tmp_size, show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing description" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized description" << std::endl;

    if (tmp_size % 2)
    {
        BYTE tmp_byte = 0;
        if (show_progress) std::cout << pad << "Serializing description padding" << std::endl;
        if (!updateBuffer((BYTE*) &tmp_byte, sizeof(BYTE), show_progress, pad))
        {
            if (show_progress) std::cout << pad << "Error serializing description padding" << std::endl;
            return false;
        }
        if (show_progress) std::cout << pad << "Serialized description padding" << std::endl;
    }

    if (show_progress) std::cout << pad << "Serializing activation_date: "
                            << std::setfill('0') << std::setw(2) << info.activation_date.wDay          << "/"
                            << std::setfill('0') << std::setw(2) << info.activation_date.wMonth        << "/"
                            << std::setfill('0') << std::setw(4) << info.activation_date.wYear         << " "
                            << std::setfill('0') << std::setw(2) << info.activation_date.wHour         << ":"
                            << std::setfill('0') << std::setw(2) << info.activation_date.wMinute       << ":"
                            << std::setfill('0') << std::setw(2) << info.activation_date.wSecond       << "."
                            << std::setfill('0') << std::setw(3) << info.activation_date.wMilliseconds << std::endl;
    if (!updateBuffer((BYTE*) &info.activation_date, sizeof(SYSTEMTIME), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing activation_date" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized activation_date" << std::endl;

    if (show_progress) std::cout << pad << "Serializing install_date: "
                            << std::setfill('0') << std::setw(2) << info.install_date.wDay          << "/"
                            << std::setfill('0') << std::setw(2) << info.install_date.wMonth        << "/"
                            << std::setfill('0') << std::setw(4) << info.install_date.wYear         << " "
                            << std::setfill('0') << std::setw(2) << info.install_date.wHour         << ":"
                            << std::setfill('0') << std::setw(2) << info.install_date.wMinute       << ":"
                            << std::setfill('0') << std::setw(2) << info.install_date.wSecond       << "."
                            << std::setfill('0') << std::setw(3) << info.install_date.wMilliseconds << std::endl;
    if (!updateBuffer((BYTE*) &info.install_date, sizeof(SYSTEMTIME), show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error serializing install_date" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized install_date" << std::endl;

    if (show_progress) std::cout << pad << "Serializing components" << std::endl;
    Serializer<ComponentContainer> serializer(info.components);
    BYTE*  s_buff      = NULL;
    size_t s_buff_size = 0L;
    if (!serializer.serialize(s_buff, s_buff_size, show_progress, pad + " "))
    {
        if (show_progress) std::cout << pad << "Error serializing components" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Serialized components" << std::endl;

    if (show_progress) std::cout << pad << "Copying serialized components" << std::endl;
    if (!updateBuffer(s_buff, s_buff_size, show_progress, pad))
    {
        if (show_progress) std::cout << pad << "Error copying serialized components" << std::endl;
        return false;
    }
    if (show_progress) std::cout << pad << "Copied serialized components" << std::endl;

    //OK
    buffer_out      = buffer;
    buffer_size_out = buffer_size;

    return true;
}

template < class Data >
bool Serializer<Data>::updateBuffer(BYTE* buffer_in, size_t buffer_in_size, bool show_progress, std::string pad)
{
    if (!buffer)
    {
        if (show_progress) std::cout << pad << "Initializing serializer buffer" << std::endl;
        buffer_size     = 0L;
        buffer_max_size = UTILS_PACKAGE_SERIALIZER_BUFFER_BASE_SIZE;
        buffer = new BYTE[buffer_max_size];
        if (!buffer)
        {
            buffer_max_size = 0L;
            if (show_progress) std::cout << pad << "Error initializing serializer buffer" << std::endl;
            return false;
        }
        ZeroMemory(buffer, buffer_max_size);
        if (show_progress) std::cout << pad << "Initialized serializer buffer" << std::endl;
    }

    if (buffer_in == NULL || buffer_in_size == 0) return true;

    if (buffer_max_size - buffer_size < buffer_in_size)
    {
        if (show_progress) std::cout << pad << "Redimensioning serializer buffer" << std::endl;
        if (UTILS_PACKAGE_SERIALIZER_BUFFER_MAX_SIZE - buffer_in_size < buffer_size)
        {
            buffer_size     = 0L;
            buffer_max_size = 0L;
            delete [] buffer;
            if (show_progress) std::cout << pad << "Error redimensioning serializer buffer: Surpassed max size" << std::endl;
            return false;
        }

        size_t buffer_min_size = buffer_size + buffer_in_size;
        buffer_max_size = ((buffer_min_size / UTILS_PACKAGE_SERIALIZER_BUFFER_BASE_SIZE) + 1) * UTILS_PACKAGE_SERIALIZER_BUFFER_BASE_SIZE;
        if (UTILS_PACKAGE_SERIALIZER_BUFFER_MAX_SIZE - UTILS_PACKAGE_SERIALIZER_BUFFER_BASE_SIZE < buffer_min_size)
            buffer_max_size = UTILS_PACKAGE_SERIALIZER_BUFFER_MAX_SIZE;
        
        BYTE* new_buffer = new BYTE[buffer_max_size];
        if (!new_buffer)
        {
            buffer_size     = 0L;
            buffer_max_size = 0L;
            delete [] buffer;
            if (show_progress) std::cout << pad << "Error redimensioning serializer buffer: Memory alloc failed" << std::endl;
            return false;
        }

        ZeroMemory(new_buffer, buffer_max_size);
        memcpy(new_buffer, buffer, buffer_size);
        delete [] buffer;
        buffer = new_buffer;
        if (show_progress) std::cout << pad << "Redimensioned serializer buffer" << std::endl;
    }

    if (show_progress) std::cout << pad << "Copying data to serializer buffer" << std::endl;
    memcpy(buffer + buffer_size, buffer_in, buffer_in_size);
    if (show_progress) std::cout << pad << "Copied data to serializer buffer" << std::endl;

    return true;
}

};
