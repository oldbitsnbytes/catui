//
// Created by Serge Lussier on 2025-10-02.
//

//#ifndef CATUI_ELEMENT_H
//#define CATUI_ELEMENT_H
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
#include <catui/ui/vchar.h>
#include <catui/ui/dom/object.h>
namespace cat::ui
{

class CATUI_LIB element : public object
{
    CLASSNAME_DERIVED(element)
public:
    element();
    element(element* parent_element, const std::string& a_id, u16 cls_bits);

    ~element() override;
protected:

};

} // namespace cat::ui

//#endif //CATUI_ELEMENT_H
