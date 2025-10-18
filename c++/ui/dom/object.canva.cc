//
// Created by Serge Lussier on 2025-10-17.
//
#include <catui/ui/dom/object.h>


#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))


namespace cat::dom
{




object::canva::canva(object::shared _parent, ui::rectangle _geometry)
{
    parent = _parent;
    geometry = _geometry;
    colors= parent->_theme_colors;
}


 object::canva::canva()
{
    ;
}


 object::canva::~canva()
{
    ;
}


 void object::canva::clear()
{

}


 rem::code object::canva::position(const ui::cxy&xy)
{
    cursor = parent->dc().at(xy+geometry.a);
    geometry.cursor = xy;
    return rem::code::accepted;
}


bool object::canva::operator++()
{
    if (!+geometry) return false;
    cursor = parent->dc().at(geometry.a + geometry.cursor);
    return true;

}


bool object::canva::operator--()
{
    if (!--geometry)
        return false;
    cursor = parent->dc().at(geometry.a + geometry.cursor);
    return true;
}


bool object::canva::operator++(int)
{
    if (!geometry++)
        return false;
    cursor = parent->dc().at(geometry.a + geometry.cursor);
    return true;
}


bool object::canva::operator--(int)
{
    if (!--geometry)
        return false;
    cursor = parent->dc().at(geometry.a + geometry.cursor);
    return true;
}


object::canva& object::canva::draw_frame()
{
    position({0,0});
    (*cursor) << border::TopLeft;
    position(geometry.bottom_left());
    (*cursor) << border::BottomLeft;
    position(geometry.bottom_right());
    (*cursor) << border::BottomRight;
    position(geometry.top_right());
    (*cursor) << border::TopRight;

    for (int x=1;x<geometry.width()-1; x++)
    {
        position(geometry.top_left() + ui::cxy{x,0});
        (*cursor) << border::Horizontal;
        position(geometry.bottom_left() + ui::cxy{x,0});
    }

    for (int x=1;x<geometry.height()-1; x++)
    {
        position(geometry.top_left() + ui::cxy{0,x});
        (*cursor) << border::Vertical;
        position(geometry.top_right() + ui::cxy{0,x});
        (*cursor) << border::Vertical;
    }

    return *this;
}


 object::canva& object::canva::operator<<(ui::color::pair cp)
{
    colors = cp;
    return *this;
}


 object::canva& object::canva::operator<<(ui::color::value c)
{
    colors.fg = c;
    return *this;
}


void object::canva::set_background_color(color::value aBg)
{
    colors.bg = aBg;
}


object::canva& object::canva::write(const std::string&str)
{
    auto wsz = MIN(str.length(),geometry.width()-geometry.cursor.x);
    for (int i=0; i<wsz; i++)
    {
        (*cursor) << str[i];
        if (!(*this)++)
            return *this;
    }

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
