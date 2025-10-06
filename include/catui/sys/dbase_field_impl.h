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
#include <catui/sys/dbase.h>



namespace cat::db
{

template<typename T> field& field::operator >> (T&)
{
    sys::warning() << "not implemented yet" << sys::eol;
    return *this;

}
template<typename T> T  field::value()
{
    sys::warning() << "not implemented yet" << sys::eol;
    return T{};
}



template<typename T> field& field::operator << (const T&  val)
{
    sys::warning() << "not implemented yet" << sys::eol;
    return *this;
}





}
