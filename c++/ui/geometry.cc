//
// Created by Serge Lussier on 2025-08-17.
//
#include <catui/ui/geometry.h>
#include <format>


namespace cat::ui
{


#pragma region _cpoint

cxy::operator std::string() const { return std::format("{},{}",x,y); }



cxy& cxy::operator++()
{
    ++x;
    return *this;
}


cxy& cxy::operator++(int)
{
    ++y;
    return *this;
}


cxy& cxy::operator--()
{
    --x;
    return *this;
}


cxy& cxy::operator--(int)
{
    --y;
    return *this;
}

#pragma endregion _cpoint




crect::crect(int X1, int X2, int Y1, int Y2):a{X1,Y1},b{X2,Y2}
{
    //@note For now, do not init b with {0,0} ...
    s.x = b.x - a.x - a.x==0?1:0;
    s.y = b.y - a.y - a.y==0?1:0;
    cursor = {0,0};
}


crect::crect(cxy Ap, cxy Bp)
{
    a = Ap;
    b = Bp;
    //@note For now, do not init b with {0,0} ...
    s.x = b.x - a.x - a.x==0?1:0;
    s.y = b.y - a.y - a.y==0?1:0;
    cursor = {0,0};
}


crect::crect(int X1, int Y1, cxy Sz)
{
    a = {X1,Y1};
    b = a + Sz;
    s = Sz;
    cursor = {0,0};
}


crect::crect(const crect&R): a(R.a), b(R.b), s(R.s), cursor(R.cursor){}


crect::crect(crect&&R) noexcept
{
    a = R.a;
    b = R.b;
    s = R.s;
    cursor = R.cursor;
    R.a = {0,0};
    R.b = {0,0};
    R.s = {0,0};
    R.cursor = {0,0};
}


void crect::Assign(int X1, int X2, int Y1, int Y2)
{
    //@note For now, do not init b with {0,0} ...
    s.x = b.x - a.x - a.x==0?1:0;
    s.y = b.y - a.y - a.y==0?1:0;
    cursor = {0,0};
}


void crect::Resize(cxy Sz)
{
    s = Sz;
    cursor = {0,0};
    b.x = a.x+b.x+Sz.x + a.x==0?-1:0;
    b.y = a.y+b.y+Sz.y + a.y==0?-1:0;
}


void crect::Resize(int Dx, int Dy)
{
    s = {Dx,Dy};
    cursor = {0,0};
    b.x = a.x+b.x+s.x + a.x==0?-1:0;
    b.y = a.y+b.y+s.y + a.y==0?-1:0;
}


bool crect::operator[](cxy P) const
{
    return P.x >= a.x && P.x < b.x && P.y >= a.y && P.y < b.y;
}


bool crect::operator[](int Ix) const
{
    return Ix >= 0 && Ix <= s.x * s.y;
}


bool crect::SetCursorPos(cxy P)
{
    if (! (*this)[P+a]) return false;
    cursor = P;
    return true;
}


bool crect::SetCursorPos(int Ix, int Iy)
{
    if (! (*this)[cxy{Ix,Iy}+a]) return false;
    cursor = {Ix,Iy};
    return true;
}


/**
 *
 */
bool crect::SetCursorOffset(int Ix)
{
    auto [x,y] = cxy{Ix%s.x, Ix/s.y};
    if (! (*this)[cxy{x,y}+a]) return false;
    cursor = {x,y};
    return true;
}


cxy crect::top_left() const
{
    return a;
}


cxy crect::top_right() const
{
    return {b.x,a.y};
}


cxy crect::bottom_left() const
{
    return {a.x,b.y};
}


cxy crect::bottom_right() const
{
    return b;
}


bool crect::operator++()
{
    ScrollDirection = 0;
    ++cursor.x;
    if (cursor.x > s.x) {
        if (NoWrap) {
            ScrollDirection= Direction::Right;
            --cursor.x;
            return false;
        }
        cursor.x = 0;
        ++cursor.y;
        if (cursor.y > s.y) {
            --cursor.y;
            ScrollDirection = Direction::Down;
            ////sys::status() << " cursor wraps to home.";
            return false;
        }
    }
    return true;
}


bool crect::operator++(int)
{
    ScrollDirection = 0;
    ++cursor.y;
    if (cursor.y > s.y)
    {
        if (NoWrap)
        {
            ScrollDirection = Direction::Down;
            --cursor.y;
            return false;
        }
    }
    return true;
}


bool crect::operator--()
{
    ScrollDirection = 0;
    --cursor.x;
    if (cursor.x < 0)
    {
        if (NoWrap)
        {
            ScrollDirection = Direction::Left;
            ++cursor.x;
            return false;
        }
    }
    --cursor.y;
    cursor.x=s.x;
    if (cursor.y < 0)
    {
        if (NoWrap)
        {
            ScrollDirection = Direction::Up;
            ++cursor.y;
        }
    }
    return true;
}


bool crect::operator--(int)
{
    --cursor.y;
    if (cursor.y < 0)
    {
        if (NoWrap)
        {
            ScrollDirection = Direction::Up;
            ++cursor.y;
            return false;
        }
    }
    return true;
}


crect& crect::operator+=(cxy P)
{
    a += P;
    b += P;

    return *this;
}


crect& crect::operator-=(cxy P)
{
    a -= P;
    b -= P;

    return *this;
}


crect& crect::operator*=(cxy P)
{
    a *= P;
    b *= P;
    return *this;
}


crect& crect::operator/=(const crect&Rhs)
{
    crect R = *this;
    *this = R / Rhs;
    *this -= Rhs.a;
    return *this;
}


crect crect::operator-(cxy P) const
{
    return {a.x-P.x,a.y-P.y,b.x-P.x,b.y-P.y};
}


crect crect::operator+(cxy P) const
{
    return {a.x+P.x,a.y+P.y,b.x+P.x,b.y+P.y};
}


crect& crect::operator=(const crect&R)
{
    a = R.a;
    b = R.b;
    s = R.s;
    cursor = R.cursor;

    return *this;
}


crect& crect::operator=(crect&&R) noexcept
{
    a = R.a;
    b = R.b;
    s = R.s;
    cursor = R.cursor;
    R.a = {0,0};
    R.b = {0,0};
    R.s = {0,0};
    R.cursor = {0,0};
    return *this;
}


void crect::assign(int X1, int X2, int Y1, int Y2)
{
    a =  {X1,Y1};
    b =  {X2,Y2};
    s.x = b.x - a.x - a.x==0?1:0;
    s.y = b.y - a.y - a.y==0?1:0;
    cursor = {0,0};
}


void crect::assign(int X1, int Y1, cxy dxy)
{
    a =  {X1,Y1};
    b = {X1+dxy.x-(X1==0?1:0),Y1+dxy.y-(Y1==0?1:0)};
    s= dxy;
}


/*!
    @brief intersection between this (a) and r (b).

    @note a & b must be of the same offset's origin. Undefined behaviour otherwise.
    @author &copy; 1996, 2023, Serge luxsier, (oldlonecoder'@'gmail.com)
    @code
   a+==============================+
    |                              |
    |  b+==========================|===========+
    |   |                          |           |
    |   |                        +-|--+        |
    +============================|=+  |        |
        |                        |    |        |
        |                        +----+        |
        +======================================+
    @endcode

    @note to get target's inner coords after intersection, subtract from intersection the r.a of the target rectangle.
    ex: r1 & r2 := inter; inter <- r1 := inter.a - r1.a;
*/
crect crect::operator&(const crect& Rhs) const
{
    crect R;
    R.Assign(
        Rhs.a.x > a.x ? Rhs.a.x : a.x,
        Rhs.a.y > a.y ? Rhs.a.y : a.y,
        Rhs.b.x > b.x ? b.x : Rhs.b.x,
        Rhs.b.y > b.y ? b.y : Rhs.b.y
    );
    return R;
}


crect crect::operator<<(const crect& Rhs) const
{
    crect R = (*this) & Rhs;
    //...
    //auto Log = //Sys::Warning(1); Log << "Not implemented yet";
    return R;
}


crect crect::operator>>(const crect& rhs) const
{
    crect R = (*this) & rhs;
    //...
    //auto Log = //Sys::Warning(1); Log << "Not implemented yet";
    return R;
}


crect crect::operator|(const crect& rhs) const
{
    return {a.x+rhs.a.x,b.x+rhs.b.x,{a.y+rhs.a.y,b.y+rhs.b.y}};
}


crect& crect::operator |=(const crect&rhs)
{

    if(!rhs) return *this;
    *this = this->operator |(rhs);
    return *this;
    return *this;
}


crect crect::operator/(const crect&Rhs) const
{
    crect R;
    R.Assign(
        Rhs.a.x < a.x ? Rhs.a.x : a.x,
        Rhs.a.y < a.y ? Rhs.a.y : a.y,
        Rhs.b.x < b.x ? b.x : Rhs.b.x,
        Rhs.b.y < b.y ? b.y : Rhs.b.y
    );
    return R - a;
}

crect::operator std::string() const
{
    return std::format("({},{}) {},{} {}x{}",cursor.x, cursor.y,a.x,a.y,s.x,s.y);
}



}
