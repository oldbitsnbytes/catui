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
    allocate_bloc_dc(_geometry.size);
    return rem::code::accepted;
}


object& object::clear()
{
    _dc->clear(_geometry.to_local());
    return *this;
}




void object::set_status(dom_status_enums::value status)
{
    _dom_status = status;
    _theme_colors = (*_palette)[_dom_status];
}


void object::set_type(type_enums::value type)
{
    _dom_type = type;

}


void object::set_component(component::value component)
{
}


void object::set_anchor(anchor::value anchor)
{
    _anchor = anchor;

}


void object::set_padding(padding padding)
{
}


void object::set_margin(margin margin)
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
    if (_parent)
    {
        sys::comment() << "using parent '" << color::yellow << _parent->id()<< color::r << "':: BLOC DC" << sys::eol;
        _dc = _parent->bloc_dc();
    }
    else
    {
        if (_dc)
        {
            sys::comment() << "releasing old BLOC DC" << sys::eol;
            _dc.reset();
        }
        sys::comment() << "creating new BLOC DC: " << color::yellow << (std::string)wxh << sys::eol;
        _dc = ui::vchar::bloc::create(_geometry, _theme_colors);
        _dc->move_to(_geometry.a);

    }

    clear();
    //...
    return rem::code::accepted;
}




rem::code object::apply_width_constraints(object* _child)
{
    if (!_child)
    {
        sys::comment() << "applying width constraints on the console:" << sys::eol;
        _geometry = {_geometry.a,io::console::size()};
        return rem::code::done;
    }


    int child_width = width()-_child->_margin.left-_child->_margin.right-(_component&component::frame?2:0);
    int child_left  = _child->_margin.left+(_component&component::frame?1:0);
    //int child_top   = _child->_margin.top+(_component&component::frame?1:0);
    _child->_geometry = {cxy{child_left,_child->_geometry.a.y},csz{child_width,_child->_geometry.size.h}};
    return rem::code::accepted;
}


rem::code object::apply_height_constraints(object* _child)
{
    if (!(_child->_anchor & anchor::height))
        return rem::code::rejected;

    int child_height = height()-_child->_margin.top-_child->_margin.bottom-(_component&component::frame?2:0);
    int child_top    = _child->_margin.top+(_component&component::frame?1:0);
    _child->_geometry = {cxy{_child->_geometry.a.x,child_top},csz{_child->_geometry.size.w,child_height}};
    return rem::code::accepted;
}


rem::code object::apply_left_constraints(object* _child)
{
    return rem::code::notimplemented;
}


rem::code object::apply_right_constraints(object* _child)
{
    if (!_child)
    {
        sys::comment() << "applying right constraints on the console:" << sys::eol;
        _geometry = {{io::console::size().w-_geometry.size.w,_geometry.a.y},_geometry.size};
        return rem::code::done;
    }
    if (!(_child->_anchor & anchor::right))
        return rem::code::rejected;
    int child_right = width()-_child->_margin.right-(_component&component::frame?2:0);
    _child->_geometry.move_at(cxy{child_right,_child->_geometry.a.y});
    return rem::code::accepted;
}


rem::code object::apply_hcenter_constraints(object* _child)
{

    return rem::code::notimplemented;
}


rem::code object::apply_vcenter_constraints(object* _child)
{
    return rem::code::notimplemented;
}



rem::code object::apply_bottom_constraints(object* _child)
{
    if (!_child)
    {
        sys::comment() << "applying bottom constraints on the console:" << sys::eol;
        _geometry = {_geometry.a,io::console::size()};
        return rem::code::done;
    }


    if (!(_child->_anchor & anchor::bottom))
        return rem::code::rejected;

    int child_y = (_geometry.size.h-_child->_margin.bottom-(_component&component::frame?2:0))-_child->_geometry.size.h;
    _child->_geometry.move_at(cxy{_child->_geometry.a.x, child_y});
    return rem::code::accepted;
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
rem::code object::apply_constraints(object* _child)
{
    rem::code result;
    if (_child->_anchor &  anchor::width)
        apply_width_constraints(_child);
    if (_child->_anchor &  anchor::height)
        apply_height_constraints(_child);
    if (_child->_anchor &  anchor::left)
        apply_left_constraints(_child);
    if (_child->_anchor &  anchor::right)
        apply_right_constraints(_child);
    if (_child->_anchor &  anchor::hcenter)
        apply_hcenter_constraints(_child);
    if (_child->_anchor &  anchor::vcenter)
        apply_vcenter_constraints(_child);
    if (_child->_anchor &  anchor::bottom)
        apply_bottom_constraints(_child);

    compute_layout(_child);
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


rem::code object::compute_layout(object* _child)
{
    if (!!apply_constraints(_child))
    {
        return exec_layout(_child);
    }
    return rem::code::rejected;
}


rem::code object::exec_layout(object* _child)
{
    if (_child) return _child->exec_layout(nullptr);
    allocate_bloc_dc(_geometry.size);

    return rem::code::accepted;
}


}
