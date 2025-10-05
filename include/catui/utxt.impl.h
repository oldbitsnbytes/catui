//
// Created by oldlonecoder on 2025-09-23.
//

//#ifndef CATUI_UTXT_IMPL_H
//#define CATUI_UTXT_IMPL_H
////////////////////////////////////////////////////////////////////////////////////////////
//   Copyright (C) ...,2025,... by Serge Lussier
//   serge.lussier@oldbitsnbytes.club / lussier.serge@gmail.com
//   ----------------------------------------------------------------------------------
//   Unless otherwise specified, all Codes and files in this project is written
//   by the author and owned by the author (Serge Lussier), unless otherwise specified.
//   ----------------------------------------------------------------------------------
//   Copyrights from authors other than Serge Lussier also apply here.
//   Open source FREE licences also apply to the code from the author (Serge Lussier)
//   ----------------------------------------------------------------------------------
//   Usual GNU FREE GPL-1,2, MIT... or whatever -  apply to this project.
//   ----------------------------------------------------------------------------------
//   NOTE : All source code that I am the only author, I reserve for myself, the rights to
//   make it to restricted private license.
////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------


#pragma once
#include <iostream>
#include <catui/utxt.h>
#include <sstream>
#include <source_location>
namespace cat
{
template<typename str_type>
std::string utxt::location<str_type>::operator*() const
{
    return  std::string{begin,end};
}


template<typename T> void utxt::append(T&&_blk)
{
    std::ostringstream _ss;
    _ss << _blk;
    m_txt.append(_ss.str());
}


template<typename T> utxt& utxt::operator<<(T&&_blk)
{
    append(_blk);
    return *this;
}




/*!
 * @brief Extract/ Scan a value from the text from the current utxt::cursor position.
 */
template<typename T> rem::code  utxt::operator>>(T& val)
{
    if (m_txt.empty()) return rem::code::rejected;
    //utxt::word _word(m_txt);
    if constexpr (std::is_same<T, std::string>::value ||
        std::is_same<T, std::string_view>::value ||
        std::is_same<T, std::wstring>::value ||
        std::is_same<T, std::wstring_view>::value ||
        std::is_same<T, cat::utxt>::value
    )
    {
        // In all 'string' cases, we scan the word and return it.
        // if cursor is on quote symbol, then scan until the end of quote. complete the sequence with quote. and return the sequence.
        std::cout << std::source_location::current().function_name() << ":" << std::endl;
        std::cout << " cursor on '" << *cursor.begin << "'" << std::endl;
        cursor.skip_ws();
        std::cout << " after skip_wd() : cursor on '" << *cursor.begin << "'" << std::endl;
        auto ptr = cursor.begin;

        while (!std::isspace(*ptr) && (ptr++ != cursor.end));
        val = std::string{cursor.begin,ptr};
        cursor.begin = ptr;

        return rem::code::valid;
    }
    else
    {
        if constexpr (std::is_same<T, bool>::value  ||
            std::is_same<T, int>::value  ||
            std::is_same<T, unsigned int>::value  ||
            std::is_same<T, float>::value  ||
            std::is_same<T, double>::value  ||
            std::is_same<T, long double>::value ||
            std::is_same<T, long long>::value  ||
            std::is_same<T, unsigned long long>::value  ||
            std::is_same<T, long>::value  ||
            std::is_same<T, unsigned long>::value  ||
            std::is_same<T, short>::value  ||
            std::is_same<T, unsigned short>::value  ||
            std::is_same<T, char>::value  ||
            std::is_same<T, unsigned char>::value )
        {
            // In all 'number' cases, we scan the numeric sequence until non-numeric byte and return
            std::cout << std::source_location::current().function_name() << ":" << std::endl;
            std::cout << " cursor on '" << *cursor.begin << "'" << std::endl;
            cursor.skip_ws();
            std::cout << " after skip_wd() : cursor on '" << *cursor.begin << "'" << std::endl;
            auto ptr = cursor.begin;
            bool real=false;
            bool ok = true;
            if (!std::isdigit(*ptr))
            {
                if (*ptr == '.'){ ++ptr; real = true; }
                else
                    return rem::code::rejected;
            }

           cont: while (std::isdigit(*ptr) && (ptr++ != cursor.end));
           if (!real && (*ptr == '.'))
           {
               ++ptr;
               real = true;
               goto cont;
           }
           else
           {
                    if (real)
                        val = std::stod(std::string{cursor.begin,ptr});
                    else
                        val = std::stoll(std::string{cursor.begin,ptr});

                    cursor.begin = ptr;
           }
           return rem::code::valid;
        }
        else
        {
            if constexpr (std::is_same<T, const char*>::value ||
                std::is_same<T, const wchar_t*>::value ||
                std::is_same<T, char*>::value ||
                std::is_same<T, wchar_t*>::value)
            {
                // In all 'string' cases, we scan the word and return it.
                // if cursor is on quote symbol, then scan until the end of quote. complete the sequence with quote. and return the sequence.
                std::cout << std::source_location::current().function_name() << ":" << std::endl;
                std::cout << " cursor on '" << *cursor.begin << "'" << std::endl;
                cursor.skip_ws();
                std::cout << " after skip_wd() : cursor on '" << *cursor.begin << "'" << std::endl;
                auto ptr = cursor.begin;

                while (!std::isspace(*ptr) && (ptr++ != cursor.end));
                val = std::string{cursor.begin,ptr}.c_str();
                cursor.begin = ptr;

                return rem::code::valid;
            }
        }

    }

    return rem::code::rejected;
}



}
