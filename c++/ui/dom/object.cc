//
// Created by Serge Lussier on 2025-10-02.
//

#include <catui/ui/dom/object.h>
#include <catui/io/console.h>
#include <utility>

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


namespace cat::dom
{
object::object()
{
    ;
}


object::~object()
{
     cat::con << rem::to_string(rem::fn::func) << " class " << color::chartreuse6 << "object[" << color::r << color::yellow << id() << color::r << ']' << conio::eol;
}


object::object(std::string a_id): _id(std::move(a_id)){}


object::object(const object::shared& parent_object, std::string a_id):  _id(std::move(a_id)),_parent(parent_object)
{
    if (_parent.get())
        _parent->_children.push_back(std::shared_ptr<object>(this));
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
    return std::ranges::find_if(_children, [&a_id](const object::shared& c) { return c->_id == a_id; } );
}


object::iterator object::child(const object::shared& child)
{
    return std::ranges::find_if(_children, [&child](const object::shared&  c){ return &(*child) == &(*c); });
}



ui::vchar::iterator object::operator[](ui::cxy pos) const
{
    if (!_geometry[pos]) return _dc->cursor; // return current _dc cursor pos... or throw o-o-boundaries
    return (*_dc)[_geometry.cursor];
}




} // namespace cat
