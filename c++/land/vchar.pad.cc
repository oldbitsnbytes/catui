//
// Created by oldlonecoder on 2025-08-18.
//
#include <catui/land/vchar.h>




namespace cat::ui
{





vchar::iterator vchar::pad::set_position(cpoint _pos)
{
    if (!geometry.SetCursorPos(_pos))
    {
        state = rem::code::oob;
        return cursor;
    }

    state = rem::code::accepted;
    return dc.begin() + geometry.Width()*_pos.Y + _pos.X;
}




/**
 *  @brief Write std::string at the current position.
 *
 * ...
 *  @return ref to self for chaining calls.
 *
vchar::Pad& vchar::Pad::operator<<(const std::string& _str)
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
vchar::Pad& vchar::Pad::operator<<(glyph::type _glyph)
{
    // if (!++geometry)
    // {
    //     auto l = sys::error(1); l << " vchar::Pad::operator<<(glyph::type) : request area:" << geometry.dwh << l;
    //     return *this;
    // }
    **cursor_ptr++ << colors << _glyph;
    return *this;
}




 *
vchar::Pad& vchar::Pad::operator<<(color::code _color)
{
    if (_color == color::reset)
        _color = colors.fg;

    cursor_ptr->set_bg(_color);
    return *this;
}


vchar::Pad& vchar::Pad::operator<<(color::pair _colors)
{
    if (_colors.fg == color::reset)
        _colors.fg = colors.fg;
    if (_colors.bg == color::reset)
        _colors.bg = colors.bg;

    cursor_ptr->set_colors(_colors);
    return *this;
}


vchar::Pad& vchar::Pad::operator<<(cadre::index _frameindex)
{
    **cursor_ptr++ << _frameindex;
    return *this;
}


vchar::Pad& vchar::Pad::operator<<(ui::cxy xy)
{
    gotoxy(xy);
    // Handle result...
    return *this;
}


vchar::Pad& vchar::Pad::operator<<(const vchar::Pad& blk)
{
    return *this;
}


vchar::Pad& vchar::Pad::operator<<(char c)
{
    **cursor_ptr << c;
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////
/// \brief vchar::Pad::clear
///     Clears sub-area given by \arg r using colors attributes \arg cp
/// \param r
/// \param cp
/// \return accepted if all of the clear went ok, rem::code::rejected otherwise
///
rem::code vchar::Pad::clear(ui::rectangle r, color::pair cp)
{
    auto rw = geometry.tolocal() & (r);
    if(!rw){
        auto l = sys::status(); l << rem::code::oob << " : request area:" << r << "; within " << geometry.dwh << l;
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


bool vchar::pad::operator++()
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
bool vchar::pad::operator++(int)
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
bool vchar::pad::operator--()
{
    if (--geometry)
    {
        --cursor;
        return true;
    }
    return false;
}

// rem::code vchar::Pad::draw_frame()
// {
//     home();
//     *this<< cadre::TopLeft
//          << geometry.top_right() << cadre::TopRight
//          << geometry.bottom_right() << cadre::BottomRight
//          << geometry.bottom_left() << cadre::BottomLeft;
//
//
//     gotoxy(ui::cxy{1,0}); // Real assign from here.
//     std::fill(cursor_ptr,cursor_ptr + geometry.dwh.w-2, vchar(colors) << cadre::Horizontal);
//     gotoxy(ui::cxy{1,geometry.b.y});
//     std::fill(cursor_ptr,cursor_ptr + geometry.dwh.w-2, vchar(colors) << cadre::Horizontal);
//
//     for(int y=1; y < geometry.dwh.h-1; y++)
//         *this << ui::cxy{0,y} << cadre::Vertical << ui::cxy{geometry.b.x,y} << cadre::Vertical;
//
//     return rem::code::done;
// }
//
//
// rem::code vchar::Pad::draw_line(int w)
// {
//     if (w<0)
//     {
//         w = geometry.dwh.w;
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
bool vchar::pad::operator--(int)
{
    if (--geometry)
    {
        --cursor;
        return true;
    }
    return false;
}



vchar::pad::~pad()
{
    dc.clear();
    geometry={};
}


vchar::pad::shared vchar::pad::create(cpoint _dim, color::pair _colours)
{
    auto p  = std::make_shared<vchar::pad>();

    p->dc = vchar::string(_dim.Area(),vchar(color::pair(_colours)));
    p->colors = _colours;
    p->geometry = {0,0,_dim};
    p->clear();
    //auto l = sys::Info(1); l << " vchar::Pad size:" << Color::Yellow << p->Geometry.S.Area() << l;
    return p;
}





//////////////////////////////////////////////////////////////
/// \brief vchar::Pad::clear
///        Clears the buffer with the current colors attributes
void vchar::pad::clear()
{
    std::fill_n(dc.begin(),geometry.S.Area(), vchar(color::pair(colors)));
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
Rem::Code vchar::Pad::Copy(vchar::Pad&pad_dc, CRect inner_area)
{
    auto rw = inner_area+pad_dc.Geometry.A;
    for (int y = 0;y < rw.S.Y; y++)
        std::copy_n(pad_dc[inner_area.A+CPoint{0,y}],rw.S.X, (*this)[rw.A+CPoint{0,y}]);

    return Rem::Code::Accepted;
}


//////////////////////////////////////////////////////////////////////
/// \brief vchar::Pad::home
///     Resets iterator and internal cursor at {0,0};
///
vchar::Iterator vchar::Pad::Home()
{
    Geometry.SetCursorPos({0,0});
    Cursor = Dc.begin();
    return Cursor;
}



////////////////////////////////////////
/// \defgroup pad-colors
///     Just copying into the current colors member vchar::Pad::colors
///


///////////////////////////////////////////////////////////////////////////////
/// \brief vchar::Pad::set_foreground_color
/// \param fg
/// \group pad-colors
void vchar::Pad::SetForegroundColor(Color::Code fg)
{
    Colors.Fg = fg;
    Cursor->SetFg(fg);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief vchar::Pad::set_background_color
/// \param bg
/// \group pad-colors
void vchar::Pad::SetBackgroundColor(Color::Code bg)
{
    Colors.Bg = bg;
    Cursor->SetBg(bg);
}

///////////////////////////////////////////////////////
/// \brief vchar::Pad::set_colors
/// \param cp
/// \group pad-colors
void vchar::Pad::SetColors(Color::Pair cp)
{
    Colors = cp;
    Cursor->SetColors(cp);
}

////////////////////////////////////////////////////////////
/// \brief vchar::Pad::fg
/// \return color code
/// \group pad-colors
/// \note Statusquo sur lire la couleur de la cellule au cursor_ptr ou donner la couleur courante a appliquer
Color::Code vchar::Pad::Fg() const { return Colors.Fg; }

////////////////////////////////////////////////////////////
/// \brief vchar::Pad::bg
/// \return
/// \group pad-colors
/// \note Statusquo sur lire la couleur de la cellule au cursor_ptr ou donner la couleur courante a appliquer
///
Color::Code vchar::Pad::Bg() const { return Colors.Bg; }



////////////////////////////////////////////////////////////////////////
/// \brief vchar::Pad::operator &
///     Intersect the rectangular geometry of this pad with \arg rhs.
/// \param rhs
/// \return resulting of the intersection.
/// \note \arg rhs origin must be on the same origin of this pad.
///
CRect vchar::Pad::operator &(const CRect& rhs) const { return Geometry & rhs; }


////////////////////////////////////////////////////////////////////////
/// \brief vchar::Pad::operator /
///     Intersect the rectangular inner geometry ( origin at {0,0} ) of this pad with \arg rhs.
/// \param rhs
/// \return resulting of the intersection shifted to the inner origin {0,0}.
/// \note \arg rhs must be on the same origin scale of this pad. So the resulting rectangle will have its offset moved to the relative geometry of this pad
///
CRect vchar::Pad::operator /(const CRect& rhs) const { return Geometry / rhs; }


/**
 *
 */
vchar::Iterator vchar::Pad::operator[](CPoint P)
{
    return Dc.begin() + (P.Y * Geometry.S.X) + P.X;
}



vchar::Pad& vchar::Pad::operator *() { return *this; }




//-----------------------------------------------------------------------------





}
