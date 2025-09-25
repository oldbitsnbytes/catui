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

#include <catui/utxt.h>

namespace cat
{

utxt::word::word(std::string&txt):begin(txt.end()), cur(begin),  end(txt.end()){}


utxt::word::word(std::string::iterator _begin, std::string::iterator _end):begin{_begin}, cur(begin),end(_end){}

std::string utxt::word::operator()() const { return {begin, end}; }


rem::code utxt::word::skip_ws()
{
    while(begin != end && std::isspace(*begin)) ++begin;
    return rem::code::valid;
}


utxt& utxt::operator<<(const char* txt)
{
    m_txt += txt;
    return *this;
}


utxt& utxt::operator<<(const std::string&txt)
{
    m_txt += txt;
    return *this;
}


utxt& utxt::operator<<(std::string_view txt)
{
    m_txt += txt;
    return *this;
}


utxt& utxt::operator<<(color::value c)
{
    m_txt += color::render_rgb(c);
    return *this;
}


utxt& utxt::operator<<(color::pair p)
{
    m_txt += color::render_rgb(p);
    return *this;
}


utxt& utxt::operator<<(ui::crect rect)
{
    m_txt += (std::string)rect;
    return *this;
}


utxt& utxt::operator<<(ui::cpoint pt)
{
    m_txt += (std::string)pt;
    return *this;
}


utxt& utxt::operator<<(ui::vchar vc)
{
    m_txt += (std::string)vc;
    return *this;
}


utxt& utxt::operator<<(const ui::vchar::string&)
{
    return *this;
}


bool utxt::operator++()
{
    if (cursor.cur == cursor.end) return false;
    ++cursor.cur;
    return true;
}


bool utxt::operator--()
{
    if (cursor.cur <= cursor.begin) return false;
    --cursor.cur;
    return true;
}


}
