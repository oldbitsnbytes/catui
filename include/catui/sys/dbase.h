//
// Created by oldlonecoder on 2025-10-06.
//

//#ifndef CATUI_DBASE_H
//#define CATUI_DBASE_H
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
#include <sqlite3.h>
#include <catui/sys/sys.h>

namespace cat::db
{



struct CATUI_LIB field
{
    std::string name{};

    enum class type : u8
    {
        integer,
        real,
        text,
        blob,
        null,
    }value_type{field::type::null};

    struct relation
    {
        u8 FKEY     :1;
        u8 INDEX    :1;
        u8 UNIQUE   :1;
    }rel{0};

    std::vector<std::string_view> values;

    using shared = std::shared_ptr<field>;

    field(std::string  a_name, field::type field_type, field::relation field_rel);

    ~field();

    field& operator = (const field& rhs);
    field& operator = (field&& rhs) noexcept;

    field& operator << (const std::string& val);
    field& operator << (const char* val);
    field& operator << (const std::string_view& val);
    field& operator << (const std::vector<std::string_view>& val);
    field& operator << (const std::vector<std::string>& val);

    template<typename T> field& operator << (const T&  val);


    template<typename T> T  value();
    template<typename T> field& operator>>(T& val);

    std::string_view operator [](size_t ind) const;


};



class CATUI_LIB dbase
{
    sqlite3 *db{nullptr};


};
} // namespace cat::db


#include <catui/sys/dbase_field_impl.h>
