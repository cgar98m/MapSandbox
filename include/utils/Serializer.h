#ifndef _UTILS_SERIALIZER_H_
#define _UTILS_SERIALIZER_H_

#include <iostream>
#include <string>
#include <windows.h>

#define UTILS_SERIALIZER_BUFFER_MAX_SIZE   static_cast<size_t>(-1)
#define UTILS_SERIALIZER_BUFFER_BASE_SIZE  256
#define UTILS_SERIALIZER_BUFFER_INC_FACTOR 2

namespace Utils
{

/****************************
 * SERIALIZER
 ****************************/

template <class Data>
class Serializer
{
public:
    Serializer(const Data& data, BYTE*& buffer, size_t& buffer_cursor, size_t& buffer_size)
        : data(data)
        , buffer(buffer)
        , buffer_cursor(buffer_cursor)
        , buffer_size(buffer_size)
    {
    }

    bool serialize(bool show_progress = false, std::string padding = "");

private:
    void clean()
    {
        if (buffer != NULL) delete [] buffer;
        buffer_cursor = 0;
        buffer_size   = 0;
    }

    bool appendDataToBuffer(const void* data, size_t data_size, bool show_progress, std::string padding)
    {
        // Any data?
        if (data == NULL || data_size == 0) return true;

        // Any buffer content?
        if (!buffer)
        {
            if (show_progress) std::cout << padding << "[INFO] Initializing buffer" << std::endl;

            buffer_cursor = 0;
            buffer_size   = 0;
            
            buffer = new BYTE[UTILS_SERIALIZER_BUFFER_BASE_SIZE];
            if (buffer == NULL)
            {
                if (show_progress) std::cout << padding << "[ERROR] Buffer not initialized" << std::endl;
                return false;
            }

            buffer_size = UTILS_SERIALIZER_BUFFER_BASE_SIZE;
            ZeroMemory(buffer, buffer_size);
            
            if (show_progress) std::cout << padding << "[SUCCESS] Buffer initialized" << std::endl;
        }

        // Enough memory?
        if (UTILS_SERIALIZER_BUFFER_MAX_SIZE - data_size < buffer_cursor)
        {
            if (show_progress) std::cout << padding << "[ERROR] Not enough memory" << std::endl;
            return false;
        }

        // Resize required?
        if (buffer_size - buffer_cursor < data_size)
        {
            if (show_progress) std::cout << padding << "[INFO] Buffer resize required" << std::endl;

            size_t buffer_min_size = buffer_cursor + data_size;
            size_t size_factor     = ((buffer_cursor + data_size) / UTILS_SERIALIZER_BUFFER_BASE_SIZE) + 1 + UTILS_SERIALIZER_BUFFER_INC_FACTOR;
            size_t buffer_new_size = size_factor * UTILS_SERIALIZER_BUFFER_BASE_SIZE;
            if (UTILS_SERIALIZER_BUFFER_MAX_SIZE / UTILS_SERIALIZER_BUFFER_BASE_SIZE < size_factor)
            {
                buffer_new_size = UTILS_SERIALIZER_BUFFER_MAX_SIZE;
            }

            BYTE* new_buffer = new BYTE[buffer_new_size];
            if (new_buffer == NULL)
            {
                if (show_progress) std::cout << padding << "[ERROR] Buffer resize failed" << std::endl;
                return false;
            }

            // Buffer migration
            ZeroMemory(new_buffer, buffer_new_size);
            memcpy(new_buffer, buffer, buffer_cursor);
            
            delete [] buffer;
            buffer      = new_buffer;
            buffer_size = buffer_new_size;

            if (show_progress) std::cout << padding << "[SUCCESS] Buffer resized" << std::endl;
        }

        // Append data
        memcpy(buffer + buffer_cursor, data, data_size);
        buffer_cursor += data_size;

        return true;
    }

    const Data& data;

    BYTE*&  buffer;
    size_t& buffer_cursor;
    size_t& buffer_size;
};

};

#endif
