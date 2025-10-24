//
// Created by Serge Lussier on 2025-10-23.
//

#include "../../include/catui/widgets/label.h"

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



label::label()
{
}


label::~label()
{
}


label::label(std::string lbl_text): object(lbl_text)
{
    ;
}


label::label(object* parent_object, std::string lbl_text) : object(parent_object, lbl_text)
{

}


void label::draw()
{
    object::draw();
    auto paint = begin_paint();
    paint << cxy{0,0} << _text;
    end_paint(paint);
    update({});
}


rem::code label::update(ui::rectangle rect)
{
    return object::update(rect);
}


rem::code label::resize(ui::rectangle rect)
{
    return object::resize(rect);
}

} // namespace cat::ui
