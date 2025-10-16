//
// Created by oldlonecoder on 2025-08-18.
//
#include <catui/ui/vchar.h>
#include "catui/sys/sys.h"
#include <catui/io/console.h>


namespace cat::ui
{



#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))


vchar::iterator vchar::bloc::set_position(cxy _pos)
{
    if (!geometry[_pos])
    {
        state = rem::code::oob;
        return cursor;
    }

    state = rem::code::accepted;
    geometry.cursor = _pos;
    return dc.begin() + geometry.width()*_pos.y + _pos.x;
}


/**
 * @brief Moves the bloc to a specified position.
 *
 * Updates the geometric position of the bloc to the provided coordinates.
 *
 * @param P The target coordinates to move the bloc to.
 * @return A rem::code indicating the operation result (always rem::code::accepted in current implementation).
 *
 * @todo Check coords ...or not...
 */
rem::code vchar::bloc::move_to(cxy P)
{
    geometry.move_at(P);
    return rem::code::accepted;
}


vchar::iterator vchar::bloc::peek(int l, int column)
{
    if (l>=geometry.size.h)
    {
        throw sys::exception()[sys::error() << rem::code::oob << " vchar::pad::line(int) : request line:" << l << "; within 0-" << color::hotpink4 << geometry.size.h];
        //return dc.end();
    }
    return (*this)[cxy{column,l}];
}


rem::code vchar::bloc::render(const rectangle&area)
{
    if (!area)
        return rem::code::rejected;



    return rem::code::accepted;

}

#define _eol_ color::pair(color::r, color::r)()

std::string vchar::bloc::render(cxy xy, int w)
{
    auto c = at(xy);
    color::pair current_colors = c->colors();
    sys::debug() << "col 1's detail:" << c->details() << color::r << sys::eol;
    std::string _o = current_colors();
    std::cout << _o;

    for(int x =0; x< w; x++)
    {
        vchar ch = *c++;

        auto  [fg, bg] = ch.colors();
        if(current_colors.bg != bg)
        {
            current_colors.bg = bg;
            _o += color::render_background_rgb(current_colors.bg);
        }
        if(current_colors.fg != fg)
        {
            current_colors.fg = fg;
            _o += color::render_rgb(current_colors.fg);
        }
        if (ch.D&ASCII)
        {
            _o += ch.ascii();
            continue;
        }
        if(ch.D & UTFBITS)
        {
            if(ch.D & Frame)
                _o += border()[ch.border_index()];
            else
                if(ch.D & Accent)
                    _o += accent_fr::data[ch.accent_index()];
                else
                    if(ch.D & UGlyph)
                    {
                        auto w = glyph::data[ch.icon_index()];
                        _o += w;
                        _o += "\033[D";
                        //l = Sys::Debug(1);
                        //l << "sizeof " << color::Yellow << w << color::R << "=" << std::strlen(w) << l;
                    }
        }
    }
    _o += _eol_;
    return _o;

}


/**
 *  @brief Write std::string at the current position.
 *
 * ...
 *  @return ref to self for chaining calls.
 *
vchar::pad& vchar::pad::operator<<(const std::string& _str)
{
    if (_str.length() >= (dc.end() - cursor_ptr))
        throw sys::exception()[
            sys::except(1) << rem::type::fatal << rem::code::oob
                << rem::fn::endl << "strlen:" << color::yellow << _str.length() << color::r
                << rem::fn::endl << "buffer length from end() pointer: " << color::yellow << (dc.end() - dc.begin())
                << rem::fn::endl << "logical position of the cursor: " << color::yellow << geometry.cursor << rem::fn::endl
        ];

    for (auto c: _str)
        **cursor_ptr++ << colors << c;
    sync_cursor(); // We must sync internal cursors before further inputs.
    return *this;
}




 *
vchar::pad& vchar::pad::operator<<(glyph::type _glyph)
{
    // if (!++geometry)
    // {
    //     auto l = sys::error(1); l << " vchar::pad::operator<<(glyph::type) : request area:" << geometry.size << l;
    //     return *this;
    // }
    **cursor_ptr++ << colors << _glyph;
    return *this;
}




 *
vchar::pad& vchar::pad::operator<<(color::value _color)
{
    if (_color == color::reset)
        _color = colors.fg;

    cursor_ptr->set_bg(_color);
    return *this;
}


vchar::pad& vchar::pad::operator<<(color::pair _colors)
{
    if (_colors.fg == color::reset)
        _colors.fg = colors.fg;
    if (_colors.bg == color::reset)
        _colors.bg = colors.bg;

    cursor_ptr->set_colors(_colors);
    return *this;
}


vchar::pad& vchar::pad::operator<<(cadre::index _frameindex)
{
    **cursor_ptr++ << _frameindex;
    return *this;
}


vchar::pad& vchar::pad::operator<<(ui::cxy xy)
{
    gotoxy(xy);
    // Handle result...
    return *this;
}


vchar::pad& vchar::pad::operator<<(const vchar::pad& blk)
{
    return *this;
}


vchar::pad& vchar::pad::operator<<(char c)
{
    **cursor_ptr << c;
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////
/// \brief vchar::pad::clear
///     Clears sub-area given by \arg r using colors attributes \arg cp
/// \param r
/// \param cp
/// \return accepted if all of the clear went ok, rem::code::rejected otherwise
///
rem::code vchar::pad::clear(ui::rectangle r, color::pair cp)
{
    auto rw = geometry.to_local() & (r);
    if(!rw){
        auto l = sys::status(); l << rem::code::oob << " : request area:" << r << "; within " << geometry.size << l;
        return rem::code::rejected;
    }

    for(int y=0; y < rw.height(); y++){
        if(auto c = set_pos({rw.a.x, rw.a.y+y}); !c)
            return c;
        for(int x=0; x < rw.width(); x++){
            ***this << cp << ' ';
            if(!++*this)
                return rem::code::rejected;
        }
    }
    return rem::code::accepted;
}
*/


/*!
 * @note bypasses natural increment-decrement because this method is the convenient way to advance the internal cursor with our boundaries.
 * @return true if the cursor is within the boundaries  false otherwise.
 * @author Serge luxsier (oldlonecoder)
 */


bool vchar::bloc::operator++()
{
    if (++geometry)
    {
        ++cursor;
        return true;
    }
    return false;
}


/*!
 * @note bypass natural increment-decrement because this method is the convenient way to advance the internal cursor with our boundaries.
 * @return true if the cursor is within the boundaries  false otherwise.
 * @author Serge luxsier (oldlonecoder)
 */
bool vchar::bloc::operator++(int)
{
    if (++geometry)
    {
        ++cursor;
        return true;
    }
    return false;
}


/*!
 *
 * @note bypass natural increment-decrement because this method is the convenient way to advance the internal cursor with our boundaries.
 * @return true if the cursor is within the boundaries  false otherwise.
 * @author Serge luxsier (oldlonecoder)
 */
bool vchar::bloc::operator--()
{
    if (--geometry)
    {
        --cursor;
        return true;
    }
    return false;
}

// rem::code vchar::pad::draw_frame()
// {
//     home();
//     *this<< cadre::TopLeft
//          << geometry.top_right() << cadre::TopRight
//          << geometry.bottom_right() << cadre::BottomRight
//          << geometry.bottom_left() << cadre::BottomLeft;
//
//
//     gotoxy(ui::cxy{1,0}); // Real assign from here.
//     std::fill(cursor_ptr,cursor_ptr + geometry.size.w-2, vchar(colors) << cadre::Horizontal);
//     gotoxy(ui::cxy{1,geometry.b.y});
//     std::fill(cursor_ptr,cursor_ptr + geometry.size.w-2, vchar(colors) << cadre::Horizontal);
//
//     for(int y=1; y < geometry.size.h-1; y++)
//         *this << ui::cxy{0,y} << cadre::Vertical << ui::cxy{geometry.b.x,y} << cadre::Vertical;
//
//     return rem::code::done;
// }
//
//
// rem::code vchar::pad::draw_line(int w)
// {
//     if (w<0)
//     {
//         w = geometry.size.w;
//         set_pos({0,geometry.cursor.y});
//     }
//     for(int i=0; i < w; i++)
//         *this << colors << cadre::Horizontal;
//
//     return rem::code::done;
// }
//

/*!
 *
 * @return true if the cursor is within the boundaries  false otherwise.
 * @author Serge luxsier (oldlonecoder)
 */
bool vchar::bloc::operator--(int)
{
    if (--geometry)
    {
        --cursor;
        return true;
    }
    return false;
}



vchar::bloc::~bloc()
{
    dc.clear();
    geometry={};
}


vchar::bloc::shared vchar::bloc::create(csz sz, color::pair a_colours)
{
    auto p  = std::make_shared<vchar::bloc>();

    p->dc = vchar::string(sz.area(),vchar(color::pair(a_colours)));
    p->colors = a_colours;
    p->geometry = {{0,0},sz};
    p->clear();
    //auto l = sys::Info(1); l << " vchar::pad size:" << color::Yellow << p->geometry.size.Area() << l;
    return p;
}





//////////////////////////////////////////////////////////////
/// \brief vchar::pad::clear
///        Clears the buffer with the current colors attributes
void vchar::bloc::clear(const rectangle& subarea)
{
    if (!subarea)
    {
        std::fill_n(dc.begin(),geometry.size.area(), vchar(color::pair(colors)));
        return;
    }

    for (int y=0;y<subarea.size.h; ++y)
        std::fill_n(dc.begin()+subarea.a.x + ((subarea.a.y + y) * geometry.size.w), subarea.size.w, vchar(color::pair(colors)));

}


/**
 *  @brief Copies a defined inner area of one pad into another pad.
 *
 *  This function takes a specified inner area from the provided source pad and
 *  copies it into the calling pad instance. It calculates the absolute positions
 *  based on the geometry of the source pad and the destination pad.
 *
 *  @param pad_dc The source pad from which the inner area will be copied.
 *  @param inner_area The rectangular region within the source pad that is to be copied.
 *  @return rem::code::accepted if the operation completes successfully.
 */
rem::code vchar::bloc::copy(vchar::bloc&pad_dc, rectangle inner_area)
{
    auto rw = inner_area+pad_dc.geometry.a;
    for (int y = 0;y < rw.size.h; y++)
        std::copy_n(pad_dc[inner_area.a+cxy{0,y}],rw.size.w, (*this)[rw.a+cxy{0,y}]);

    return rem::code::accepted;
}


//////////////////////////////////////////////////////////////////////
/// \brief vchar::pad::home
///     Resets iterator and internal cursor at {0,0};
///
vchar::iterator vchar::bloc::at(const cxy& offset)
{
    if (geometry[offset])
        return dc.begin() + (geometry.width() * offset.y) + offset.x;

    return cursor;
}


rem::code vchar::bloc::goto_xy(const cxy&offset)
{
    if (!geometry[offset])
    {
        sys::error() << " vchar::pad::goto_xy : request area:" << rem::code::oob << ";" <<  offset << "; within " << geometry.size << sys::eol;
        return rem::code::oob;
    }
    geometry.cursor = offset;
    cursor = dc.begin() + (geometry.width() * geometry.cursor.y) + geometry.cursor.x;
    return rem::code::accepted;
}


////////////////////////////////////////
/// \defgroup pad-colors
///     Just copying into the current colors member vchar::pad::colors
///


///////////////////////////////////////////////////////////////////////////////
/// \brief vchar::pad::set_foreground_color
/// \param fg
/// \group pad-colors
void vchar::bloc::set_foreground_color(color::value fg)
{
    colors.fg = fg;
    cursor->set_fg(fg);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief vchar::pad::set_background_color
/// \param bg
/// \group pad-colors
void vchar::bloc::set_background_color(color::value bg)
{
    colors.bg = bg;
    cursor->set_bg(bg);
}

///////////////////////////////////////////////////////
/// \brief vchar::pad::set_colors
/// \param cp
/// \group pad-colors
void vchar::bloc::set_colors(color::pair cp)
{
    colors = cp;
    cursor->set_colors(cp);
}


rem::code vchar::bloc::print(const std::string& str)
{
    auto size = str.length();
    // Re-assure syncing iterator position with the cursor position
    //cursor = (*this)[geometry.cursor];
    auto count = MIN(size, (dc.end() - cursor));

    for (int x=0; x < count; x++)  *cursor++ << str[x];

    return rem::code::accepted;
}


////////////////////////////////////////////////////////////
/// \brief vchar::pad::fg
/// \return color code
/// \group pad-colors
/// \note Statusquo sur lire la couleur de la cellule au cursor_ptr ou donner la couleur courante a appliquer
color::value vchar::bloc::fg() const { return colors.fg; }

////////////////////////////////////////////////////////////
/// \brief vchar::pad::bg
/// \return
/// \group pad-colors
/// \note Statusquo sur lire la couleur de la cellule au cursor_ptr ou donner la couleur courante a appliquer
///
color::value vchar::bloc::bg() const { return colors.bg; }



////////////////////////////////////////////////////////////////////////
/// \brief vchar::pad::operator &
///     Intersect the rectangular geometry of this pad with \arg rhs.
/// \param rhs
/// \return resulting of the intersection.
/// \note \arg rhs origin must be on the same origin of this pad.
///
rectangle vchar::bloc::operator &(const rectangle& rhs) const { return geometry & rhs; }


////////////////////////////////////////////////////////////////////////
/// \brief vchar::pad::operator /
///     Intersect the rectangular inner geometry ( origin at {0,0} ) of this pad with \arg rhs.
/// \param rhs
/// \return resulting of the intersection shifted to the inner origin {0,0}.
/// \note \arg rhs must be on the same origin scale of this pad. So the resulting rectangle will have its offset moved to the relative geometry of this pad
///
rectangle vchar::bloc::operator /(const rectangle& rhs) const { return geometry / rhs; }


/**
 *  brief peek.
 */
vchar::iterator vchar::bloc::operator[](cxy P)
{
    auto r = geometry;
    if (!r[P])
        return cursor;

    return dc.begin() + (P.y * geometry.size.w) + P.x;
}



vchar::bloc& vchar::bloc::operator *() { return *this; }




//-----------------------------------------------------------------------------





}
