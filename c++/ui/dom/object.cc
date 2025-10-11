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
    if (_parent)
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


rem::code object::set_geometry(const ui::rectangle&rect)
{
    _geometry = rect;
    _alloc_bloc_dc(_geometry.size);
    bloc_dc()->geometry = _geometry;
    return rem::code::accepted;
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


void object::set_dom_status(dom_status_enums::value status)
{
    _dom_status = status;
    _theme_colors = _palette[_dom_status];
}


void object::set_dom_type(type_enums::value type)
{
    _dom_type = type;

}


void object::set_dom_component(component::value component)
{
}


void object::set_dom_anchor(anchor::value anchor)
{
}


void object::set_dom_padding(padding padding)
{
}


void object::set_dom_margin(margin margin)
{
}


std::pair<std::string, dom_status_enums::value> object::dom_status() const
{
    std::map<dom_status_enums::value, std::string> status_data={
        {dom_status_enums::none     ,"none"},
        {dom_status_enums::normal   ,"normal"},
        {dom_status_enums::warning  ,"warning"},
        {dom_status_enums::error    ,"error"},
        {dom_status_enums::success  ,"success"},
        {dom_status_enums::focussed ,"focussed"},
        {dom_status_enums::disabled ,"disabled"},
        {dom_status_enums::selected ,"selected"},
        {dom_status_enums::checked  ,"checked"},
        {dom_status_enums::unchecked,"unchecked"},
        {dom_status_enums::inactive ,"inactive"},
        {dom_status_enums::active   ,"active"},
        {dom_status_enums::hidden   ,"hidden"},
        {dom_status_enums::visible  ,"visible"},
        {dom_status_enums::locked   ,"locked"},
        {dom_status_enums::unlocked ,"unlocked"}
    };

    return {status_data[_dom_status], _dom_status};
}


std::pair<std::string, type_enums::value> object::dom_type() const
{
    std::map<dom::type_enums::value, std::string> type_names = {
        {type_enums::dialog,    "dialog"},
        {type_enums::floating,  "floating"},
        {type_enums::menu,      "menu"},
        {type_enums::toolbar,   "toolbar"},
        {type_enums::toplevel,  "toplevel"},
        {type_enums::none,      "none"}
    };

    return {type_names[_dom_type], _dom_type};
}


/**
 * Retrieves the associated DOM component of the `object` instance.
 *
 * @return A `std::pair` containing a string identifier and a `component::value`.
 *         - The string identifier represents a textual description or key for the component.
 *         - The `component::value` contains the actual component value tied to the DOM object.
 */
std::pair<std::string, component::value> object::dom_component() const
{

    return {};
}


std::pair<std::string, anchor::value> object::dom_anchor() const
{
    return {};
}


padding& object::dom_padding()
{
    return _padding;
}


margin& object::dom_margin()
{
    return _margin;
}


rem::code object::_alloc_bloc_dc(ui::csz wxh)
{
    if (_parent)
        _dc = parent()->bloc_dc();
    else
        _dc = ui::vchar::bloc::create(wxh, _theme_colors);
    dom_clear();
    //...
    return rem::code::accepted;
}


} // namespace cat
