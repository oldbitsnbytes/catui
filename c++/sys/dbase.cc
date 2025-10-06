//
// Created by oldlonecoder on 2025-10-06.
//

#include <utility>

#include "../../include/catui/sys/dbase.h"

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


namespace cat::db
{
field::field(std::string a_name, field::type field_type, field::relation field_rel):name(std::move(a_name)), value_type(field_type), rel(field_rel){}


field::~field()
{
    if (!values.empty())
        values.clear();

}


field& field::operator=(const field&rhs)
{
    return *this;
}


field& field::operator=(field&&rhs) noexcept
{
    return *this;
}


field& field::operator<<(const std::string&val)
{
    values.push_back(val);
    return *this;
}


field& field::operator<<(const char* val)
{
    values.push_back(val);
    return *this;
}


field& field::operator<<(const std::string_view&val)
{
    values.push_back(val);
    return *this;
}


field& field::operator<<(const std::vector<std::string_view>&val)
{
    values.append_range(val);
    return *this;
}


field& field::operator<<(const std::vector<std::string>&val)
{
    values.append_range(val);
    return *this;
}


std::string_view field::operator[](size_t ind) const
{
    if (ind>=values.size())
        return {};
    return values[ind];
}
} // namespace cat::db
