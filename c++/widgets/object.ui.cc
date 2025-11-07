//
// Created by Serge Lussier on 2025-10-19.
//



#include <catui/widgets/object.h>
#include <catui/io/console.h>


namespace cat::ui
{

using namespace cat::ui;

rem::code object::set_geometry(const ui::rectangle& rect)
{
    _geometry = rect;
    if (_parent)
        _dc = _parent->bloc_dc();
    else
        allocate_bloc_dc();

    return rem::code::accepted;
}


object& object::clear()
{
    if (_parent)
        _dc->clear(_geometry);
    else
        _dc->clear(_geometry.to_local());
    return *this;
}




void object::set_status(dom_status_enums::value status)
{
    _dom_status = status;
    _theme_colors = (*_palette)[_dom_status];
    //@todo Propagate ui status changes
}


void object::set_type(type_enums::value type)
{
    _dom_type = type;

}


void object::set_component(component::value component)
{
    _component = component;
}


void object::set_anchor(anchor::value anchor)
{
    _anchor = anchor;
    ///@todo Propagate anchor chanages ( if in post setup )
}


void object::set_padding(padding padding)
{
    _padding = padding;
    ///@todo Propagate padding changes.
}


void object::set_margin(margin margin)
{
    _margin = margin;
    ///@todo Propagate maring changes
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
    std::map<ui::type_enums::value, std::string> type_names = {
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
    std::map<ui::anchor::value, std::string> anchor_names = {
        {ui::anchor::none    , "none"},
        {ui::anchor::fixed   , "fixed"},
        {ui::anchor::width   , "width"},
        {ui::anchor::height  , "height"},
        {ui::anchor::frame   , "frame"},
        {ui::anchor::right   , "right"},
        {ui::anchor::left    , "left"},
        {ui::anchor::top     , "top"},
        {ui::anchor::bottom  , "bottom"},
        {ui::anchor::center  , "center"},
        {ui::anchor::hcenter , "hcenter"},
        {ui::anchor::vcenter , "vcenter"}
    };
    return {anchor_names[_anchor],_anchor};
}


padding& object::dom_padding()
{
    return _padding;
}


margin& object::dom_margin()
{
    return _margin;
}


/**
 * Allocates or retrieves a display context (DC) associated with the object based on its parent or creates one
 * from the given dimensions and current theme colors. Clears the display context post allocation or retrieval.
 *
 * @param wxh The dimensions (width and height) used to create a new display context if the object has no parent.
 * @return A `rem::code` indicating the result:
 *         - `rem::code::accepted` if the display context is allocated or retrieved successfully.
 */
rem::code object::allocate_bloc_dc()
{
    if (_dom_type & type_enums::toplevel)
    {
        if (_dc)
        {
            _dc->geometry = _geometry;
            _dc->realloc();
        }
        else
            _dc = ui::vchar::bloc::create(_geometry, _theme_colors);

        sys::comment() << "creating new BLOC DC: " << color::yellow << (std::string)_geometry.size << sys::eol;

        _dc->move_to(_geometry.a);
    }

    clear();
    //...
    return rem::code::accepted;
}


//
// rem::code object::apply_right_constraints(object* _child)
// {
//     if (!_child)
//     {
//         sys::comment() << "applying right constraints on the console:" << sys::eol;
//         _geometry = {{io::console::size().w-_geometry.size.w,_geometry.a.y},_geometry.size};
//         return rem::code::done;
//     }
//     if (!(_child->_anchor & anchor::right))
//         return rem::code::rejected;
//     int child_right = width()-_child->_margin.right-(_component&component::frame?2:0);
//     _child->_geometry.move_at(cxy{child_right,_child->_geometry.a.y});
//     return rem::code::accepted;
// }



// rem::code object::apply_bottom_constraints(object* _child)
// {
//     if (!_child)
//     {
//         sys::comment() << "applying bottom constraints on the console:" << sys::eol;
//         _geometry = {_geometry.a,io::console::size()};
//         return rem::code::done;
//     }
//
//
//     if (!(_child->_anchor & anchor::bottom))
//         return rem::code::rejected;
//
//     int child_y = (_geometry.size.h-_child->_margin.bottom-(_component&component::frame?2:0))-_child->_geometry.size.h;
//     _child->_geometry.move_at(cxy{_child->_geometry.a.x, child_y});
//     return rem::code::accepted;
// }


rem::code object::layout_width()
{
    if (_dom_type & type_enums::toplevel)
    {
        sys::comment() << "applying width constraints on the console:" << sys::eol;
        _geometry = {cxy{0+_margin.left,_geometry.a.y}, csz{io::console::size().w-_margin.left-_margin.right-(_component&component::frame?2:0),_geometry.size.h}};
        return rem::code::done;
    }

    if (!_parent)
        return rem::code::rejected;

    int _width = _parent->width()-_margin.left-_margin.right-(_component&component::frame?2:0);
    int _left  = _margin.left+(_component&component::frame?1:0);
    _geometry = {cxy{_left,_geometry.a.y},csz{_width,_geometry.size.h}};
    return rem::code::accepted;
}


rem::code object::layout_height()
{
    if (!(_anchor & anchor::height))
        return rem::code::rejected;

    int _height = height()-_margin.top-_margin.bottom-(_component&component::frame?2:0);
    int _top    = _margin.top+(_component&component::frame?1:0);
    _geometry = {cxy{_geometry.a.x,_top},csz{_geometry.size.w,_height}};
    return rem::code::accepted;
}


rem::code object::layout_left()
{
    sys::warning() << "layout_left() not implemented yet" << sys::eol;
    return rem::code::notimplemented;
}


rem::code object::layout_right()
{
    sys::warning() << "layout_right() not implemented yet" << sys::eol;
    return rem::code::notimplemented;
}


rem::code object::layout_hcenter()
{
    sys::warning() << "layout_hcenter() not implemented yet" << sys::eol;
    return rem::code::notimplemented;
}


rem::code object::layout_vcenter()
{
    sys::warning() << "layout_vcenter() not implemented yet" << sys::eol;
    return rem::code::notimplemented;
}


rem::code object::layout_bottom()
{
    sys::warning() << "layout_bottom() not implemented yet" << sys::eol;
    //     if (!_child)
    //     {
    //         sys::comment() << "applying bottom constraints on the console:" << sys::eol;
    //         _geometry = {_geometry.a,io::console::size()};
    //         return rem::code::done;
    //     }
    //
    //
    //     if (!(_child->_anchor & anchor::bottom))
    //         return rem::code::rejected;
    //
    //     int child_y = (_geometry.size.h-_child->_margin.bottom-(_component&component::frame?2:0))-_child->_geometry.size.h;
    //     _child->_geometry.move_at(cxy{_child->_geometry.a.x, child_y});
    //     return rem::code::accepted;
    return rem::code::notimplemented;
}


rem::code object::layout_top()
{
    sys::warning() << "layout_top() not implemented yet" << sys::eol;
    return rem::code::notimplemented;
}


rem::code object::layout_center()
{
    sys::warning() << "layout_center() not implemented yet" << sys::eol;
    return rem::code::notimplemented;
}


/**
 * Applies anchor-based constraints to a child object based on its defined anchor properties.
 * Each anchor determines a specific type of alignment or size adjustment.
 *
 * @param _child A pointer to the child object whose anchor constraints will be applied.
 *               The `_anchor` property of this object is evaluated to determine the constraints.
 * @return A `rem::code` indicating the result of the operation:
 *         - `rem::code::done` if the anchor constraints are successfully applied.
 * @note if '_child' is nullptr, then the constraints are applied to this object, in absolute coords directly onto the console terminal.
 */
rem::code object::exec_layout()
{
    rem::code result;

    if (_anchor &  anchor::width)
        layout_width();
    if (_anchor &  anchor::height)
        layout_height();
    if (_anchor &  anchor::left)
        layout_left();
    if (_anchor &  anchor::right)
        layout_right();
    if (_anchor &  anchor::hcenter)
        layout_hcenter();
    if (_anchor &  anchor::vcenter)
        layout_vcenter();;
    if (_anchor &  anchor::bottom)
        layout_bottom();

    allocate_bloc_dc();
    return rem::code::done;
}


void object::draw()
{
    auto &cc = begin_paint();
    //cc.draw_frame(); // just for testing.
    cc.clear();
    end_paint(cc);
}








void object::redraw()
{
    sys::test() << " redraw Area : " << color::yellow << _dirty_area << color::r << " at " << color::yellow << _dc->geometry.a << color::r <<  sys::eol;
    con.render(*_dc, _dirty_area);
}


/**
 * Updates the specified area within the object's geometry and merges(union operation) it to the current dirty area if valid.
 *
 * @param rect The rectangle to be updated and intersected with the object's local geometry.
 * @return A `rem::code` indicating the outcome:
 *         - `rem::code::rejected` if the resulting rectangle is invalid.
 *         - `rem::code::accepted` if the rectangle is successfully updated and marked as dirty.
 */
rem::code object::update(ui::rectangle rect)
{
    if (!rect)
        rect = _geometry.to_local();

    rect = _geometry.to_local() & rect;
    if (!rect)
        return rem::code::rejected;

    _dirty_area |= rect;
    sys::debug() << rem::fn::func << ": dirty area: " << color::yellow << _dirty_area << color::r << sys::eol;

    return rem::code::accepted;
}


rem::code object::resize(ui::rectangle rect)
{
    set_geometry(rect);
    return rem::code::accepted;
}


void object::set_size_policy(ui::csz sz_policy) { _size_policy = sz_policy; }



}
