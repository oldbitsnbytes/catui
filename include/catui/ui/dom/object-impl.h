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
#include <catui/ui/dom/object.h>



namespace cat::dom
{

inline object::canva::canva()
{
    ;
}


inline object::canva::~canva()
{
    ;
}


inline void object::canva::clear()
{

}


inline rem::code object::canva::position(const ui::cxy&xy)
{
}


inline object::canva& object::canva::operator++()
{
}


inline object::canva& object::canva::operator--()
{
}


inline object::canva& object::canva::operator++(int)
{
}


inline object::canva& object::canva::operator--(int)
{
}


inline object::canva& object::canva::draw_frame()
{
}


inline object::canva& object::canva::operator<<(ui::color::pair cp)
{
}


inline object::canva& object::canva::operator<<(ui::color::value c)
{
}


inline void object::canva::set_background_color(color::value aBg)
{
}


inline object::canva& object::canva::write(const std::string&str)
{
}


inline object::canva& object::begin_paint(ui::rectangle r)
{
}


inline object::canva& object::end_paint(object::canva&canva)
{
}


template<typename T> T* object::dom_parent()
{
    object* o = this;
    while (o->_parent)
    {
        T* p = dynamic_cast<T*>(o->_parent);
        if (p) return p;
    }
    return nullptr;
}


template<typename T>object::canva& object::canva::operator<<(const T&val)
{

    return *this;
}
}
