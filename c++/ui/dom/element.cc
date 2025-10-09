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

#include <catui/ui/dom/element.h>
#include <catui/io/console.h>
namespace cat::ui
{
element::element() : object()
{
    ;
}


element::element(element* parent_element, const std::string&a_id, u16 cls_bits):object(parent_element, a_id)
{
    if (parent_element)
    {
        _theme_colors = parent_element->_theme_colors;
        parent_element->_children.push_back(this);
    }

}


element::~element()
{
    //...
    sys::debug() << rem::fn::func << " class object<-" << color::chartreuse6 << "element" << color::r << " [" << color::yellow << id() << color::r << ']' << sys::eol;
}


rem::code element::draw()
{
    if (!_dc)
    {
        sys::error() << "Attempt to draw an element that have no dc." << sys::eol;
        return rem::code::rejected;
    }

    _dc->clear();

    //...

    return rem::code::accepted;
}


rem::code element::update(rectangle r)
{
    if (!r) r = _rect;
    if (auto p = dom_parent<element>(); p)
        return p->update(r);
    if (!_dirty_area)
        _dirty_area = r;
    else
        _dirty_area = r | _dirty_area;

    auto rend = _dirty_area.to_local();

    sys::debug() << "render tests, element::update: dirty area :" << color::yellow << _dirty_area << color::r << sys::eol;
    //...
    for (int y =0; y <rend.size.h; ++y)
    {
        con << (_dc->geometry.local() + rend.a + cxy{0,y});
        std::cout << vchar::render_line(_dc->peek(y,0),rend.size.w);
    }
    return rem::code::done;
}


rem::code element::set_geometry(const rectangle&a_geometry)
{
    _rect = a_geometry;
    sys::debug() << "set_geometry: " << color::yellow << _rect << color::r << sys::eol;
    _alloc_dc(_rect.size);

    if (!dom_parent<element>())
        _dc->geometry = _rect;
    return rem::code::accepted;
}


rem::code element::set_theme(const std::string&a_theme_name)
{
    _theme_id = a_theme_name;
    _palette = color::db::element_item(color::db::theme(_theme_id), class_name());
    _theme_colors = _palette[static_cast<int>(_status)];
    sys::debug() << "theme: '" << color::chartreuse6 << _theme_id << color::r << "' for element: " << color::yellow << id() << color::r << sys::eol;
    sys::write() << " colors: " << color::chartreuse6 << _theme_colors.name() << color::r << sys::eol;
    return rem::code::accepted;
}


void element::set_padding(padding a_padding)
{
    _padding = a_padding;
    //... Check if we shall redraw.
}


void element::set_margin(margin a_margin)
{
    _margin = a_margin;
    //... Check if we shall redraw.
}


void element::set_anchor(anchor::value a_anchor)
{
    _anchor = a_anchor;
    //... Check if we shall redraw.
}


void element::set_status(estatus::value a_status)
{
    _status = a_status;
    //... Check if we shall redraw.
}


void element::set_component(component::value a_component)
{
    _component |= a_component;
    //... Check if we shall redraw.
}


void element::set_type(e_type::value a_type)
{
    _type = a_type;
    //... Check if we shall redraw.
}


/**
 * Sets up the user interface for the element by applying the specified color theme.
 * If the specified theme is unknown, the setup process is rejected.
 *
 * @param _theme_name The name of the color theme to be applied to the element.
 * @return A rem::code value indicating whether the setup operation was successful.
 *         Returns rem::code::accepted if the theme is applied successfully,
 *         or rem::code::rejected if the theme is unknown.
 */
rem::code element::setup_ui(const std::string&_theme_name)
{
    _theme_id = _theme_name;
    auto& palette = color::db::theme(_theme_id)[class_name()];
    if (palette.empty())
    {
        sys::error() << "Attempt to setup an element with an unknown colors theme: " << _theme_name << sys::eol;
        return rem::code::rejected;
    }

    //...
    return rem::code::accepted;

}


/**
 * Allocates a drawing context (_dc) for the element. If the element has a parent,
 * it inherits the parent's drawing context. Otherwise, a new drawing context
 * is created with the specified dimensions.
 *
 * @param wxh The dimensions for the drawing context, represented as a cpoint.
 * @return A rem::code value indicating whether the operation was accepted.
 */
rem::code element::_alloc_dc(csz wxh)
{
    if (const auto* pr = dom_parent<element>(); pr)
        _dc = pr->_dc;
    else
        _dc = vchar::bloc::create(std::move(wxh),_theme_colors);
    //

    return rem::code::accepted;
}


} // namespace ca::uit
