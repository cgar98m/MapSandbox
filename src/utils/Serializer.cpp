#include "utils/Serializer.h"

#include <iomanip>

namespace Utils
{

/****************************
 * SERIALIZER
 ****************************/

/*
 * Serializer< std::string >
 */
template class Serializer< std::string >;

template <>
bool Serializer< std::string >::serialize(bool show_progress, std::string padding)
{
    // Temp
    size_t tmp_sizet;

    if (show_progress) std::cout << padding << "[INFO] Serializing text: size=" << data.size() << " text=" << (data.empty() ? "" : data) << std::endl;
    
    // Serialize text length
    tmp_sizet = data.size();
    if (!appendDataToBuffer(static_cast<const void*>(&tmp_sizet), sizeof(tmp_sizet), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Text size not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize padding length
    tmp_sizet = data.size() % 2;
    if (!appendDataToBuffer(static_cast<const void*>(&tmp_sizet), sizeof(tmp_sizet), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Text padding size not serialized" << std::endl;
        clean();
        return false;
    }

    // Serialize text?
    if (!data.empty())
    {
        if (!appendDataToBuffer(static_cast<const void*>(data.c_str()), data.size(), show_progress, padding))
        {
            if (show_progress) std::cout << padding << "[ERROR] Text not serialized" << std::endl;
            clean();
            return false;
        }
    }

    // Serialize padding?
    if (tmp_sizet > 0)
    {
        std::string text_padding(tmp_sizet, '\0');
        if (!appendDataToBuffer(static_cast<const void*>(text_padding.c_str()), text_padding.size(), show_progress, padding))
        {
            if (show_progress) std::cout << padding << "[ERROR] Text padding not serialized" << std::endl;
            clean();
            return false;
        }
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Text serialized" << std::endl;
    return true;
}

/*
 * Serializer< SYSTEMTIME >
 */
template class Serializer< SYSTEMTIME >;

template <>
bool Serializer< SYSTEMTIME >::serialize(bool show_progress, std::string padding)
{
    // Temp
    size_t tmp_sizet;

    if (show_progress) std::cout << padding << "[INFO] Serializing date: "
        << std::setw(4) << std::setfill('0') << data.wYear         << "/"
        << std::setw(2) << std::setfill('0') << data.wMonth        << "/"
        << std::setw(2) << std::setfill('0') << data.wDay          << " "
        << std::setw(2) << std::setfill('0') << data.wHour         << ":"
        << std::setw(2) << std::setfill('0') << data.wMinute       << ":"
        << std::setw(2) << std::setfill('0') << data.wSecond       << "."
        << std::setw(3) << std::setfill('0') << data.wMilliseconds << std::endl;
    
    // Serialize date
    if (!appendDataToBuffer(static_cast<const void*>(&data), sizeof(data), show_progress, padding))
    {
        if (show_progress) std::cout << padding << "[ERROR] Date not serialized" << std::endl;
        clean();
        return false;
    }

    if (show_progress) std::cout << padding << "[SUCCESS] Date serialized" << std::endl;
    return true;
}

};
