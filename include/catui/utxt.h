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

#include <catui/land/sys/rem.h>

#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <catui/land/sys/expect.h>
#include <catui/land/geometry.h>
#include <catui/land/vchar.h>

namespace cat
{
/*!
 * Utility class for:
 *
 *  @li formatting
 *  @li converting
 *  @li accumulate/aggregate text
 *  @li slice/tokenize
 *  <br />
 *  embedded std::string and operates on and from it.
 *  @author Serge Lussier ( oldbitsnbytes/oldlonecoder )
 */
class CATUI_LIB utxt
{

    std::string m_txt{};
    using list = std::vector<std::string>;

public:

    struct CATUI_LIB word
    {
        std::string::iterator begin{};
        std::string::iterator cur{};
        std::string::iterator end{};

        word() = delete;
        word(std::string& txt);
        word(std::string::iterator begin, std::string::iterator end);
        ~word() = default;
        std::string     operator()() const;
        void            reset() { cur=begin;}
        [[nodiscard]]   bool empty() const { return begin==end;}
        explicit        operator bool() const { return begin!=end;}
        rem::code       skip_ws();

    }cursor{m_txt};




    utxt() = default;
    explicit utxt(std::string_view txt);
    ~utxt() = default;

    utxt(const utxt&) = default;
    utxt& operator=(const utxt&) = default;

    utxt(utxt&& _txt) noexcept = default;
    utxt& operator=(utxt&& _txt) noexcept = default;

    utxt(const std::string& txt) : m_txt(txt){ cursor.begin = m_txt.begin();}
    utxt(std::string&& txt) : m_txt(std::move(txt)){cursor.begin = m_txt.begin();}
    utxt(const char* txt) : m_txt(txt){ cursor.begin = m_txt.begin();}
    utxt& operator=(const char* txt) {m_txt = txt; cursor={m_txt}; cursor.begin = m_txt.begin(); return  *this;}
    utxt& operator=(const std::string& txt) { m_txt = txt;  cursor={m_txt};cursor.begin = m_txt.begin(); return *this; }
    utxt& operator=(std::string&& txt) { m_txt = std::move(txt);  cursor={m_txt}; cursor.begin = m_txt.begin(); return *this;}


    template<typename T> void append(T&& _blk);
    template<typename T> utxt& operator << (T&& _blk);
    template<typename T>  rem::code operator >> (T& val);

    utxt& operator << (const char* txt);
    utxt& operator << (const std::string& txt);
    utxt& operator << (std::string_view txt);
    utxt& operator << (color::value c);
    utxt& operator << (color::pair p);
    utxt& operator << (ui::crect rect);
    utxt& operator << (ui::cpoint pt);
    utxt& operator << (ui::vchar vc);
    utxt& operator << (const ui::vchar::string& )

    [[nodiscard]] size_t size() const { return m_txt.length();}
    [[nodiscard]] size_t length() const { return m_txt.length();}
    [[nodiscard]] size_t count() const { return m_txt.length();}

    bool operator ++();
    bool operator --();


};



}



#include <catui/utxt.impl.h>
