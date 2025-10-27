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


#include <catui/widgets/statusbar.h>

namespace cat::ui
{


statusbar::statusbar()
{
}


statusbar::statusbar(object* parent_object, std::string _id): object(parent_object, _id)
{
    set_anchor(anchor::bottom | anchor::width);
    _geometry.size.h = 1;
    _geometry.size.min_size = {1,1};
    _geometry.size.max_size = {10000,1};

    if (_parent)
        _parent->compute_layout(this);
    else
        compute_layout(this);

}


statusbar::~statusbar()
{
}


void statusbar::draw()
{
    object::draw();
}


rem::code statusbar::update(ui::rectangle rect)
{
    return object::update(rect);
}


rem::code statusbar::resize(ui::rectangle rect)
{
    return object::resize(rect);
}
}
