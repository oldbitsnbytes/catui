//
// Created by Serge Lussier on 2025-10-02.
//

#include <catui/ui/dom/element.h>

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


namespace cat::ui
{
element::element() : object()
{
    ;
}


element::element(element* parent_element, const std::string&a_id, u16 cls_bits):object(parent_element, a_id)
{
    ;
}


element::~element()
{
    ;
}


rem::code element::draw()
{
    if (!_dc)
    {
        sys::error() << "Attempt to draw an element that have no dc." << sys::eol;
        return rem::code::rejected;
    }
    //...

    return rem::code::accepted;
}


rem::code element::ealloc(cpoint wxh)
{
    _dc = vchar::pad::create(std::move(wxh),{});
    return rem::code::accepted;
}


} // namespace ca::uit
