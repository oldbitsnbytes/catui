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


rem::code object::set_theme(const std::string&theme_name)
{
    _palette = color::db::element_item(color::db::theme(theme_name), "object");
    _theme_colors = _palette[_dom_status];
    return rem::code::accepted;
}


ui::vchar::iterator object::operator[](ui::cxy pos) const
{
    if (!_geometry[pos]) return _dc->cursor; // return current _dc cursor pos... or throw o-o-boundaries
    return (*_dc)[_geometry.cursor];
}


object& object::dom_clear()
{
    _dc->clear(_geometry.to_local());
    return *this;
}


object& object::home()
{
    (*_dc)[_geometry.a];
    return *this;
}


object& object::operator<<(const std::string& str)
{

    return *this;
}


object& object::operator<<(const char* str)
{
    return *this;
}


object& object::operator<<(const std::string_view&str)
{
    return *this;
}


object& object::operator<<(const std::vector<std::string_view>&str)
{
    return *this;
}


object& object::operator<<(const std::vector<std::string>&str)
{
    return *this;
}


object& object::operator<<(const ui::rectangle&frame_dim)
{
    return *this;
}


object& object::operator<<(color::pair clr)
{
    return *this;
}


object& object::operator<<(color::value clr)
{
    return *this;
}


object& object::operator<<(glyph::value f)
{
    return *this;
}


object& object::operator<<(cat::string str)
{
    return *this;
}


object& object::operator<<(cat::ui::cxy xy)
{
    return *this;
}


object& object::operator<<(sys::fn f)
{
    return *this;
}


object& object::operator<<(cat::ui::rectangle rect)
{
    return *this;
}


object& object::operator<<(cat::ui::border::Index idx)
{
    return *this;
}


ui::vchar::bloc::shared object::_alloc_bloc_dc(ui::csz wxh)
{
    if (_parent)
        _dc = parent()->bloc_dc();
    else
        _dc = ui::vchar::bloc::create(wxh, _theme_colors);
    dom_clear();
    //...
    return _dc;
}


} // namespace cat
