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




//////////////////////////////////////////////////////////////
/// \brief CString::now
///
///     \b time/date format, given by \a str_fmt.
///
///     [https://cpluxplux.com/reference/ctime/strftime]
///
///   \li %a	Abbreviated weekday name
///   \li %A	Full weekday name
///   \li %b	Abbreviated month name
///   \li %B	Full month name
///   \li %c	Date and time representation (ex.:)	Thu Aug 23 14:55:02 2001
///   \li %C	Year divided by 100 and truncated to integer (00-99)
///   \li %d	Day of the month, zero-padded (01-31)
///   \li %D	Short MM/DD/YY date, equivalent to %m/%d/%y
///   \li %e	Day of the month, space-padded ( 1-31)
///   \li %F	Short YYYY-MM-DD date, equivalent to %Y-%m-%d
///   \li %g	Week-based year, last two digits (00-99)
///   \li %G	Week-based year
///   \li %h	Abbreviated month name * (same as %b)
///   \li %H	Hour in 24h format (00-23)
///   \li %I	Hour in 12h format (01-12)
///   \li %j	Day of the year (001-366)
///   \li %m	Month as a decimal number (01-12)
///   \li %M	Minute (00-59)
///   \li %n	New-line character ('\n')
///   \li %p	AM or PM designation
///   \li %r	12-hour clock time
///   \li %R	24-hour HH:MM time, equivalent to %H:%M
///   \li %S	Second (00-61)
///   \li %t	Horizontal-tab character ('\t')
///   \li %T	ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S
///   \li %u	ISO 8601 weekday as number with Monday as 1 (1-7)
///   \li %U	Week number with the first Sunday as the first day of week one (00-53)
///   \li %V	ISO 8601 week number (01-53)
///   \li %w	Weekday as a decimal number with Sunday as 0 (0-6)
///   \li %W	Week number with the first Monday as the first day of week one (00-53)
///   \li %x	Date representation
///   \li %X	Time representation
///   \li %y	Year, last two digits (00-99)
///   \li %Y	Year
///   \li %z	ISO 8601 offset from UTC in timezone (1 minute=1, 1 hour=100)
///   \li %Z	Timezone name or abbreviation
///

/// \param str_fmt
/// \return
///
///
///
std::string utxt::now(const std::string& str_fmt)
{
    // Old archaic Code...
    // time_t rawtime;
    // struct tm* timeinfo;
    // char tmb[180];
    // std::time(&rawtime);
    // timeinfo = std::localtime(&rawtime);
    // std::strftime(tmb, 60, str_fmt.c_str(), timeinfo);
    // std::string _s = tmb;
    // //return tmb;


    auto current = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::to_time_t(current);
    auto local = localtime(&now);
    std::ostringstream ostr;
    ostr << std::put_time(local, str_fmt.c_str());
    return ostr.str();
}

std::string utxt::bytes(std::string_view a_seq)
{
    std::string outstr{};

    int c = 0;
    for(auto ch  : a_seq)
    {
        outstr += std::format("0x{:02x}", static_cast<int>(ch));
        if(c++ < (a_seq.size()-1)) outstr += ',';
    }

    return outstr;
}

std::string utxt::bytes(std::vector<int> a_seq)
{
    std::string outstr{};
    int c = 0;
    for(auto n  : a_seq)
    {
        if(std::isprint(n))
            outstr += std::format("x{:02x}|u{:d}'{}'", n,n, char(n) );
        else
            outstr += std::format("x{:02x}|u{:d}", n,n);
        if(c++ < (a_seq.size()-1)) outstr += ',';
    }

    return outstr;
}


std::string utxt::bytes(std::vector<integers::U8> a_seq)
{
    std::string outstr{};
    int c = 0;
    for(auto n  : a_seq)
    {
        if(std::isprint(n))
            outstr += std::format("x{:02x}|u{:d}'{}'", n,n, char(n) );
        else
            outstr += std::format("x{:02x}|u{:d}", n,n);
        if(c++ < (a_seq.size()-1)) outstr += ',';
    }

    return outstr;
}


std::vector<std::string_view> utxt::make_view_list(int Count, char** s, int offset)
{
    std::vector<std::string_view> result;
    if (offset == Count) return {};
    for(int i = offset; i < Count; ++i) result.emplace_back(s[i]);
    return result;
}


std::vector<std::string> utxt::make_list(int argc, char** argv, int offset)
{
    std::vector<std::string> result;
    for(int i = offset; i < argc; ++i) result.emplace_back(argv[i]);
    return result;
}


}
