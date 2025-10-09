//
// Created by Serge Lussier on 2025-10-02.
//

#include <catui/ui/dom/object.h>

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
     sys::debug() << rem::fn::func << " class " << color::chartreuse6 << "object[" << color::r << color::yellow << id() << color::r << ']' <<  sys::eol;
}


object::object(std::string a_id): _id(std::move(a_id)){}


object::object(object* parent_object, std::string a_id):_parent(parent_object), _id(std::move(a_id)){}


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
    return std::find_if(_children.begin(), _children.end(), [&a_id](const object* c) { return c->_id == a_id; } );
}


object::iterator object::child(object* child)
{
    return std::find_if(_children.begin(), _children.end(), [&child](const object* c){ return child == c; });
}


} // namespace cat
