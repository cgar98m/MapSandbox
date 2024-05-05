#include "utils/Serializer.h"

#include <iomanip>

#include "data/package/Container.h"

namespace Utils
{

/****************************
 * SERIALIZER
 ****************************/

/*
 * Serializer< Data::ComponentsMap >
 */
template class Serializer< Data::ComponentsMap >;

template <>
bool Serializer< Data::ComponentsMap >::serialize(bool show_progress, std::string padding)
{
    // Temp
    size_t tmp_sizet;

    if (show_progress) std::cout << padding << "[INFO] Serializing components: " << data.size() << std::endl;

    // Serialize number of components
    tmp_sizet = data.size();
    if (!appendDataToBuffer(static_cast<const void*>(&tmp_sizet), sizeof(tmp_sizet), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Number of components not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize components
    std::string padding_child = padding + " ";
    for (Data::ComponentsMapConstIter it = data.begin(); it != data.end(); ++it)
    {
        Data::Component data_child(it->first, it->second);
        Serializer< Data::Component > serializer_child(data_child, buffer, buffer_cursor, buffer_size);
        if (!serializer_child.serialize(show_progress, padding_child))
        {
            if (show_progress) std::cout << padding << "[ERROR] Components not serialized" << std::endl;
            clean();
            return false;
        }
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Components serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::ComponentsVector >
 */
template class Serializer< Data::ComponentsVector >;

template <>
bool Serializer< Data::ComponentsVector >::serialize(bool show_progress, std::string padding)
{
    // Temp
    size_t tmp_sizet;

    if (show_progress) std::cout << padding << "[INFO] Serializing components: " << data.size() << std::endl;

    // Serialize number of components
    tmp_sizet = data.size();
    if (!appendDataToBuffer(static_cast<const void*>(&tmp_sizet), sizeof(tmp_sizet), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Number of components not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize components
    std::string padding_child = padding + " ";
    for (Data::ComponentsVectorConstIter it = data.begin(); it != data.end(); ++it)
    {
        Serializer< Data::Component > serializer_child(*it, buffer, buffer_cursor, buffer_size);
        if (!serializer_child.serialize(show_progress, padding_child))
        {
            if (show_progress) std::cout << padding << "[ERROR] Components not serialized" << std::endl;
            clean();
            return false;
        }
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Components serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::Component >
 */
template class Serializer< Data::Component >;

template <>
bool Serializer< Data::Component >::serialize(bool show_progress, std::string padding)
{
    if (show_progress) std::cout << padding << "[INFO] Serializing component" << std::endl;

    // Serialize key
    Serializer< Data::ComponentKey > serializer_key(data.key, buffer, buffer_cursor, buffer_size);
    if (!serializer_key.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Component key not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize data
    Serializer< Data::ComponentData > serializer_data(data.data, buffer, buffer_cursor, buffer_size);
    if (!serializer_data.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Component data not serialized" << std::endl;
        clean();
        return false;
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Component serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::ComponentKey >
 */
template class Serializer< Data::ComponentKey >;

template <>
bool Serializer< Data::ComponentKey >::serialize(bool show_progress, std::string padding)
{
    if (show_progress) std::cout << padding << "[INFO] Serializing component key: " << data.id << "-" << data.version << std::endl;

    // Serialize id
    if (!appendDataToBuffer(static_cast<const void*>(&data.id), sizeof(data.id), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Component key id not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize version
    if (!appendDataToBuffer(static_cast<const void*>(&data.version), sizeof(data.version), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Component key version not serialized" << std::endl;
        clean();
        return false;
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Component key serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::ComponentData >
 */
template class Serializer< Data::ComponentData >;

template <>
bool Serializer< Data::ComponentData >::serialize(bool show_progress, std::string padding)
{
    if (show_progress) std::cout << padding << "[INFO] Serializing component data: " << std::endl;

    // Serialize description
    Serializer< std::string > serializer_text_1(data.description, buffer, buffer_cursor, buffer_size);
    if (!serializer_text_1.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Component description not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize path
    Serializer< std::string > serializer_text_2(data.path, buffer, buffer_cursor, buffer_size);
    if (!serializer_text_2.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Component path not serialized" << std::endl;
        clean();
        return false;
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Component data serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::PackagesMap >
 */
template class Serializer< Data::PackagesMap >;

template <>
bool Serializer< Data::PackagesMap >::serialize(bool show_progress, std::string padding)
{
    // Temp
    size_t tmp_sizet;

    if (show_progress) std::cout << padding << "[INFO] Serializing packages: " << data.size() << std::endl;

    // Serialize number of packages
    tmp_sizet = data.size();
    if (!appendDataToBuffer(static_cast<const void*>(&tmp_sizet), sizeof(tmp_sizet), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Number of packages not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize packages
    std::string padding_child = padding + " ";
    for (Data::PackagesMapConstIter it = data.begin(); it != data.end(); ++it)
    {
        Data::Package< Data::ComponentsMap > data_child(it->first, it->second);
        Serializer< Data::Package< Data::ComponentsMap > > serializer_child(data_child, buffer, buffer_cursor, buffer_size);
        if (!serializer_child.serialize(show_progress, padding_child))
        {
            if (show_progress) std::cout << padding << "[ERROR] Packages not serialized" << std::endl;
            clean();
            return false;
        }
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Packages serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::PackagesVector >
 */
template class Serializer< Data::PackagesVector >;

template <>
bool Serializer< Data::PackagesVector >::serialize(bool show_progress, std::string padding)
{
    // Temp
    size_t tmp_sizet;

    if (show_progress) std::cout << padding << "[INFO] Serializing packages: " << data.size() << std::endl;

    // Serialize number of packages
    tmp_sizet = data.size();
    if (!appendDataToBuffer(static_cast<const void*>(&tmp_sizet), sizeof(tmp_sizet), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Number of packages not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize packages
    std::string padding_child = padding + " ";
    for (Data::PackagesVectorConstIter it = data.begin(); it != data.end(); ++it)
    {
        Serializer< Data::Package< Data::ComponentsVector > > serializer_child(*it, buffer, buffer_cursor, buffer_size);
        if (!serializer_child.serialize(show_progress, padding_child))
        {
            if (show_progress) std::cout << padding << "[ERROR] Packages not serialized" << std::endl;
            clean();
            return false;
        }
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Packages serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::Package< Data::ComponentsMap > >
 */
template class Serializer< Data::Package< Data::ComponentsMap > >;

template <>
bool Serializer< Data::Package< Data::ComponentsMap > >::serialize(bool show_progress, std::string padding)
{
    if (show_progress) std::cout << padding << "[INFO] Serializing package" << std::endl;

    // Serialize key
    Serializer< Data::PackageKey > serializer_key(data.key, buffer, buffer_cursor, buffer_size);
    if (!serializer_key.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package key not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize data
    Serializer< Data::PackageData< Data::ComponentsMap > > serializer_data(data.data, buffer, buffer_cursor, buffer_size);
    if (!serializer_data.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package data not serialized" << std::endl;
        clean();
        return false;
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Package serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::Package< Data::ComponentsVector > >
 */
template class Serializer< Data::Package< Data::ComponentsVector > >;

template <>
bool Serializer< Data::Package< Data::ComponentsVector > >::serialize(bool show_progress, std::string padding)
{
    if (show_progress) std::cout << padding << "[INFO] Serializing package" << std::endl;

    // Serialize key
    Serializer< Data::PackageKey > serializer_key(data.key, buffer, buffer_cursor, buffer_size);
    if (!serializer_key.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package key not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize data
    Serializer< Data::PackageData< Data::ComponentsVector > > serializer_data(data.data, buffer, buffer_cursor, buffer_size);
    if (!serializer_data.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package data not serialized" << std::endl;
        clean();
        return false;
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Package serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::PackageKey >
 */
template class Serializer< Data::PackageKey >;

template <>
bool Serializer< Data::PackageKey >::serialize(bool show_progress, std::string padding)
{
    if (show_progress) std::cout << padding << "[INFO] Serializing package key: " << data.id << "-" << data.version << std::endl;

    // Serialize id
    if (!appendDataToBuffer(static_cast<const void*>(&data.id), sizeof(data.id), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package key id not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize version
    if (!appendDataToBuffer(static_cast<const void*>(&data.version), sizeof(data.version), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package key version not serialized" << std::endl;
        clean();
        return false;
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Package key serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::PackageData< Data::ComponentsMap > >
 */
template class Serializer< Data::PackageData< Data::ComponentsMap > >;

template <>
bool Serializer< Data::PackageData< Data::ComponentsMap > >::serialize(bool show_progress, std::string padding)
{
    // Temp
    BYTE tmp_byte;

    if (show_progress) std::cout << padding << "[INFO] Serializing package data" << std::endl;

    // Serialize state
    tmp_byte = static_cast<BYTE>(data.current);
    if (!appendDataToBuffer(static_cast<const void*>(&tmp_byte), sizeof(tmp_byte), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package state not serialized" << std::endl;
        clean();
        return false;
    }

    tmp_byte = 0;
    if (!appendDataToBuffer(static_cast<const void*>(&tmp_byte), sizeof(tmp_byte), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package padding state not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize owner
    if (!appendDataToBuffer(static_cast<const void*>(&data.owner), sizeof(data.owner), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package owner not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize description
    Serializer< std::string > serializer_text(data.description, buffer, buffer_cursor, buffer_size);
    if (!serializer_text.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package description not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize activation date
    Serializer< SYSTEMTIME > serializer_date_1(data.activation_date, buffer, buffer_cursor, buffer_size);
    if (!serializer_date_1.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package activation date not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize install date
    Serializer< SYSTEMTIME > serializer_date_2(data.install_date, buffer, buffer_cursor, buffer_size);
    if (!serializer_date_2.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package install date not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize components
    Serializer< Data::ComponentsMap > serializer_child(data.components, buffer, buffer_cursor, buffer_size);
    if (!serializer_child.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package components not serialized" << std::endl;
        clean();
        return false;
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Package data serialized" << std::endl;
    return true;
}

/*
 * Serializer< Data::PackageData< Data::ComponentsVector > >
 */
template class Serializer< Data::PackageData< Data::ComponentsVector > >;

template <>
bool Serializer< Data::PackageData< Data::ComponentsVector > >::serialize(bool show_progress, std::string padding)
{
    // Temp
    BYTE tmp_byte;

    if (show_progress) std::cout << padding << "[INFO] Serializing package data" << std::endl;

    // Serialize state
    tmp_byte = static_cast<BYTE>(data.current);
    if (!appendDataToBuffer(static_cast<const void*>(&tmp_byte), sizeof(tmp_byte), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package state not serialized" << std::endl;
        clean();
        return false;
    }

    tmp_byte = 0;
    if (!appendDataToBuffer(static_cast<const void*>(&tmp_byte), sizeof(tmp_byte), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package padding state not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize owner
    if (!appendDataToBuffer(static_cast<const void*>(&data.owner), sizeof(data.owner), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package owner not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize description
    Serializer< std::string > serializer_text(data.description, buffer, buffer_cursor, buffer_size);
    if (!serializer_text.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package description not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize activation date
    Serializer< SYSTEMTIME > serializer_date_1(data.activation_date, buffer, buffer_cursor, buffer_size);
    if (!serializer_date_1.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package activation date not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize install date
    Serializer< SYSTEMTIME > serializer_date_2(data.install_date, buffer, buffer_cursor, buffer_size);
    if (!serializer_date_2.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package install date not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize components
    Serializer< Data::ComponentsVector > serializer_child(data.components, buffer, buffer_cursor, buffer_size);
    if (!serializer_child.serialize(show_progress, padding + " "))
    {
        if (show_progress) std::cout << padding << "[ERROR] Package components not serialized" << std::endl;
        clean();
        return false;
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Package data serialized" << std::endl;
    return true;
}

};
