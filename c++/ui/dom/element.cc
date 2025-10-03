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
    _children.clear();
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


rem::code element::update(crect r)
{
    return rem::code::notimplemented;
}


/**
 * Allocates a drawing context (_dc) for the element. If the element has a parent,
 * it inherits the parent's drawing context. Otherwise, a new drawing context
 * is created with the specified dimensions.
 *
 * @param wxh The dimensions for the drawing context, represented as a cpoint.
 * @return A rem::code value indicating whether the operation was accepted.
 */
rem::code element::_alloc_dc(cpoint wxh)
{
    if (const auto* pr = dom_parent<element>(); pr)
        _dc = pr->_dc;
    else
        _dc = vchar::pad::create(std::move(wxh),{});
    return rem::code::accepted;
}


} // namespace ca::uit
