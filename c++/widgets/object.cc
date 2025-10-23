//
// Created by Serge Lussier on 2025-10-02.
//

#include <catui/widgets/object.h>
#include <catui/io/console.h>
#include <utility>

#include "catui/sys/application.h"

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
object::object()
{
    ;
}


object::~object()
{
     cat::con << rem::to_string(rem::fn::func) << " class " << color::chartreuse6 << "object[" << color::r << color::yellow << id() << color::r << ']' << conio::eol;
    for (auto* o : _children) delete o;
    _children.clear();
}


object::object(std::string a_id): _id(std::move(a_id))
{
    _parent = nullptr;
    _dom_status = dom_status_enums::active;
    _theme_id = application::theme_id();
    _theme_colors = color::db::theme_palette(_theme_id)["object"][_dom_status];
}


object::object(object* parent_object, std::string a_id):  _id(std::move(a_id)),_parent(parent_object)
{
    if (_parent)
        _parent->_children.push_back(this);
    _dom_status = dom_status_enums::active;
    _theme_id = application::theme_id();
    _theme_colors = color::db::theme_palette(_theme_id)["object"][_dom_status];
}


object& object::operator=(object&&rhs) noexcept
{
    _id = rhs._id;
         rhs._id={};
    _parent = rhs._parent;
         rhs._parent = nullptr;

    _children = std::move(rhs._children);
        rhs._children.clear();

    return *this;
}


object& object::operator=(const object&rhs)
{
    _id = rhs._id;
    _parent = rhs._parent;
    _children = rhs._children;
    return *this;
}





object::iterator object::child(const std::string& a_id)
{
    return std::ranges::find_if(_children, [&a_id](const object* c) { return c->_id == a_id; } );
}


object::iterator object::child(const object*& child)
{
    return std::ranges::find_if(_children, [&child](const object*  c){ return child == c; });
}



ui::vchar::iterator object::operator[](ui::cxy pos) const
{
    if (!_geometry[pos]) return _dc->cursor; // return current _dc cursor pos... or throw o-o-boundaries
    return (*_dc)[_geometry.cursor];
}




} // namespace cat
