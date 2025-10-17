//
// Created by Serge Lussier on 2025-10-17.
//
#include <catui/ui/dom/object.h>




namespace cat::dom
{
object::canva::canva(object::shared _parent, ui::rectangle _geometry)
{
    parent = _parent;
    geometry = _geometry;
    colors= parent->_theme_colors;
}


inline object::canva::canva()
{
    ;
}


inline object::canva::~canva()
{
    ;
}


inline void object::canva::clear()
{

}


inline rem::code object::canva::position(const ui::cxy&xy)
{
    return rem::code::accepted;
}


inline object::canva& object::canva::operator++()
{
    return *this;

}


inline object::canva& object::canva::operator--()
{
    return *this;
}


inline object::canva& object::canva::operator++(int)
{
    return *this;
}


inline object::canva& object::canva::operator--(int)
{
    return *this;
}


inline object::canva& object::canva::draw_frame()
{
    return *this;
}


inline object::canva& object::canva::operator<<(ui::color::pair cp)
{
    return *this;
}


inline object::canva& object::canva::operator<<(ui::color::value c)
{
    return *this;
}


void object::canva::set_background_color(color::value aBg)
{

}


object::canva& object::canva::write(const std::string&str)
{
    return *this;
}


object::canva& object::begin_paint(ui::rectangle r)
{
    if (_parent.get())
        return *(new canva(*_parent->child(_id)));

    return *(new canva(shared(this), r));
}


void object::end_paint(object::canva& canva)
{
    // update(cana.geometry);
    delete &canva;
}


}
