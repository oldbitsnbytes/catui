//
// Created by oldlonecoder on 2025-09-23.
//

//#ifndef CATUI_EXPECT_H
//#define CATUI_EXPECT_H
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

#include <catui/sys/rem.h>
#include <any>
namespace cat
{
template<typename T> class expect
{
    rem::code state{rem::code::failed};
    std::any value{}; ///< < default & copy || POD > - constructible object.


public:

    expect(){};
    expect(T val): state(rem::code::valid), value(val){}
    expect(rem::code c): state(c){}
    ~expect(){ value.reset(); }
    //expect(T&& val) :state(rem::code::valid), value(std::move(val)){}


    explicit operator T() const { return value; }
    explicit operator bool() const {return !!state; }


    expect& operator=(T val) { value = val; return *this; }
    //expect& operator=(T&& val) noexcept { value = std::move(val); return *this; }
    expect& operator=(const expect& val) { value = val.value; return *this; }
    expect& operator=(expect&& val) noexcept  { value = std::move(val.value); return *this; }
    expect& operator=(rem::code c) { state = c; return *this; }
    //expect& operator=(T& val) { state = rem::code::valid; value = val; return *this; }
    T operator->() { return std::any_cast<T>(value); }
    T operator*() { return std::any_cast<T>(value); }
    rem::code error() {  return state; }

};
}
