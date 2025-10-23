//
// Created by Serge Lussier on 2025-10-17.
//
#include <catui/widgets/object.h>


#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))


namespace cat::ui
{




object::canva::canva(object* _parent, ui::rectangle _geometry)
{
    parent = _parent;
    if (!_geometry)
        geometry = parent->_geometry.to_local();
    else
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


void object::canva::clear() const
{
    if (geometry==parent->_geometry)
        parent->dc().clear();
    else
        parent->dc().clear(geometry);
}


rem::code object::canva::clear(const ui::rectangle&rect)
{
    auto area = rect;
    if (!area)
        area = geometry;
    else
    {
        area = area & geometry;
        if (!area)
        {
            sys::error() << "Invalid area: " << area<< sys::eol;
            return rem::code::rejected;
        }
    }

    parent->dc().clear(area,colors);

    return rem::code::accepted;
}


rem::code object::canva::position(const ui::cxy&xy)
{
    cursor = parent->dc().at(xy+geometry.a);
    geometry.cursor = xy;
    return rem::code::accepted;
}


bool object::canva::operator++()
{
    if (!++geometry) return false;
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
    if (!geometry--)
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
        (*cursor) << border::Horizontal;
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
    cp.fg = cp.fg == color::r ? parent->dc().colors.fg : cp.fg;
    cp.bg = cp.bg == color::r ? parent->dc().colors.bg : cp.bg;

    colors = cp;
    return *this;
}


 object::canva& object::canva::operator<<(ui::color::value c)
{
    colors.fg = c == color::r ? parent->dc().colors.fg : c;
    return *this;
}


void object::canva::set_background_color(color::value aBg)
{
    aBg = aBg==color::r ? parent->dc().colors.bg : aBg;
    colors.bg = aBg;
}


object::canva& object::canva::write(const std::string&str)
{
    auto wsz = MIN(str.length(),geometry.width()-geometry.cursor.x);
    for (int i=0; i<wsz; i++)
    {
        (*cursor) << str[i];
        if (!++(*this))
            break;
    }

    return *this;
}


object::canva& object::canva::operator<<(const std::string&str)
{
    return (*this) << str.c_str();
}


object::canva& object::canva::operator<<(const char* str)
{
    auto wsz = MIN(std::strlen(str),geometry.width()-geometry.cursor.x);
    for (int i=0; i<wsz; i++)
    {
        (*cursor) << str[i];
        if (!++(*this))
            break;
    }

    return *this;
}


/**
 * Overloads the left-shift operator to append a string view to the current canva instance.
 *
 * This operator function converts the given `std::string_view` to a `std::string` and forwards
 * the operation to another overloaded version of the left-shift operator that takes a `std::string` as input.
 *
 * @param str The string view to be appended to the canva instance.
 * @return A reference to the modified canva instance.
 * @todo Re-implement with string_view instead of converting to std::string overhead...
 */
object::canva& object::canva::operator<<(const std::string_view&str)
{
    auto wsz = MIN(str.length(),geometry.width()-geometry.cursor.x);
    for (int i=0; i<wsz; i++)
    {
        (*cursor) << str[i];
        if (!++(*this))
            break;
    }

    return *this;

}


object::canva& object::canva::operator<<(const ui::vchar::string&str)
{

    return *this;
}


object::canva& object::canva::operator<<(const ui::rectangle&frame_dim)
{

    return *this;
}


object::canva& object::canva::operator<<(glyph::value f)
{
    return *this;
}


object::canva& object::canva::operator<<(cat::string str)
{
    return *this << str().c_str();

}


object::canva& object::canva::operator<<(cat::ui::cxy xy)
{
    position(xy);
    return *this;
}


object::canva& object::canva::operator<<(sys::fn f)
{

    return *this;
}


object::canva& object::canva::operator<<(cat::ui::rectangle rect)
{
    return *this;
}


object::canva& object::canva::operator<<(cat::ui::border::Index idx)
{
    return *this;
}


object::canva& object::begin_paint(ui::rectangle r)
{
    return *new canva(this, r);
}


void object::end_paint(object::canva& canva)
{
    // update(cana.geometry);
    delete &canva;
}



}
