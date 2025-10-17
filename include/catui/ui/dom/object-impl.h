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
