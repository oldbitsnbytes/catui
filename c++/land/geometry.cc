//
// Created by Serge Lussier on 2025-08-17.
//
#include <catui/land/geometry.h>
#include <format>


namespace cat::ui
{


#pragma region _cpoint

cpoint::operator std::string() const { return std::format("{},{}",X,Y); }



cpoint& cpoint::operator++()
{
    ++X;
    return *this;
}


cpoint& cpoint::operator++(int)
{
    ++Y;
    return *this;
}


cpoint& cpoint::operator--()
{
    --X;
    return *this;
}


cpoint& cpoint::operator--(int)
{
    --Y;
    return *this;
}

#pragma endregion _cpoint




crect::crect(int X1, int X2, int Y1, int Y2):A{X1,Y1},B{X2,Y2}
{
    //@note For now, do not init B with {0,0} ...
    S.X = B.X - A.X - A.X==0?1:0;
    S.Y = B.Y - A.Y - A.Y==0?1:0;
    Cursor = {0,0};
}


crect::crect(cpoint Ap, cpoint Bp)
{
    A = Ap;
    B = Bp;
    //@note For now, do not init B with {0,0} ...
    S.X = B.X - A.X - A.X==0?1:0;
    S.Y = B.Y - A.Y - A.Y==0?1:0;
    Cursor = {0,0};
}


crect::crect(int X1, int Y1, cpoint Sz)
{
    A = {X1,Y1};
    B = A + Sz;
    S = Sz;
    Cursor = {0,0};
}


crect::crect(const crect&R): A(R.A), B(R.B), S(R.S), Cursor(R.Cursor){}


crect::crect(crect&&R) noexcept
{
    A = R.A;
    B = R.B;
    S = R.S;
    Cursor = R.Cursor;
    R.A = {0,0};
    R.B = {0,0};
    R.S = {0,0};
    R.Cursor = {0,0};
}


void crect::Assign(int X1, int X2, int Y1, int Y2)
{
    //@note For now, do not init B with {0,0} ...
    S.X = B.X - A.X - A.X==0?1:0;
    S.Y = B.Y - A.Y - A.Y==0?1:0;
    Cursor = {0,0};
}


void crect::Resize(cpoint Sz)
{
    S = Sz;
    Cursor = {0,0};
    B.X = A.X+B.X+Sz.X + A.X==0?-1:0;
    B.Y = A.Y+B.Y+Sz.Y + A.Y==0?-1:0;
}


void crect::Resize(int Dx, int Dy)
{
    S = {Dx,Dy};
    Cursor = {0,0};
    B.X = A.X+B.X+S.X + A.X==0?-1:0;
    B.Y = A.Y+B.Y+S.Y + A.Y==0?-1:0;
}


bool crect::operator[](cpoint P) const
{
    return P.X >= A.X && P.X < B.X && P.Y >= A.Y && P.Y < B.Y;
}


bool crect::operator[](int Ix) const
{
    return Ix >= 0 && Ix <= S.X * S.Y;
}


bool crect::SetCursorPos(cpoint P)
{
    if (! (*this)[P+A]) return false;
    Cursor = P;
    return true;
}


bool crect::SetCursorPos(int Ix, int Iy)
{
    if (! (*this)[cpoint{Ix,Iy}+A]) return false;
    Cursor = {Ix,Iy};
    return true;
}


/**
 *
 */
bool crect::SetCursorOffset(int Ix)
{
    auto [x,y] = cpoint{Ix%S.X, Ix/S.Y};
    if (! (*this)[cpoint{x,y}+A]) return false;
    Cursor = {x,y};
    return true;
}


bool crect::operator++()
{
    ScrollDirection = 0;
    ++Cursor.X;
    if (Cursor.X > S.X) {
        if (NoWrap) {
            ScrollDirection= Direction::Right;
            --Cursor.X;
            return false;
        }
        Cursor.X = 0;
        ++Cursor.Y;
        if (Cursor.Y > S.Y) {
            --Cursor.Y;
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
    ++Cursor.Y;
    if (Cursor.Y > S.Y)
    {
        if (NoWrap)
        {
            ScrollDirection = Direction::Down;
            --Cursor.Y;
            return false;
        }
    }
    return true;
}


bool crect::operator--()
{
    ScrollDirection = 0;
    --Cursor.X;
    if (Cursor.X < 0)
    {
        if (NoWrap)
        {
            ScrollDirection = Direction::Left;
            ++Cursor.X;
            return false;
        }
    }
    --Cursor.Y;
    Cursor.X=S.X;
    if (Cursor.Y < 0)
    {
        if (NoWrap)
        {
            ScrollDirection = Direction::Up;
            ++Cursor.Y;
        }
    }
    return true;
}


bool crect::operator--(int)
{
    --Cursor.Y;
    if (Cursor.Y < 0)
    {
        if (NoWrap)
        {
            ScrollDirection = Direction::Up;
            ++Cursor.Y;
            return false;
        }
    }
    return true;
}


crect& crect::operator+=(cpoint P)
{
    A += P;
    B += P;

    return *this;
}


crect& crect::operator-=(cpoint P)
{
    A -= P;
    B -= P;

    return *this;
}


crect& crect::operator*=(cpoint P)
{
    A *= P;
    B *= P;
    return *this;
}


crect& crect::operator/=(const crect&Rhs)
{
    crect R = *this;
    *this = R / Rhs;
    *this -= Rhs.A;
    return *this;
}


crect crect::operator-(cpoint P) const
{
    return {A.X-P.X,A.Y-P.Y,B.X-P.X,B.Y-P.Y};
}


crect crect::operator+(cpoint P) const
{
    return {A.X+P.X,A.Y+P.Y,B.X+P.X,B.Y+P.Y};
}


crect& crect::operator=(const crect&R)
{
    A = R.A;
    B = R.B;
    S = R.S;
    Cursor = R.Cursor;

    return *this;
}


crect& crect::operator=(crect&&R) noexcept
{
    A = R.A;
    B = R.B;
    S = R.S;
    Cursor = R.Cursor;
    R.A = {0,0};
    R.B = {0,0};
    R.S = {0,0};
    R.Cursor = {0,0};
    return *this;
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
crect crect::operator&(const crect&Rhs) const
{
    crect R;
    R.Assign(
        Rhs.A.X > A.X ? Rhs.A.X : A.X,
        Rhs.A.Y > A.Y ? Rhs.A.Y : A.Y,
        Rhs.B.X > B.X ? B.X : Rhs.B.X,
        Rhs.B.Y > B.Y ? B.Y : Rhs.B.Y
    );
    return R;
}


crect crect::operator<<(crect Rhs)
{
    crect R = (*this) & Rhs;
    //...
    //auto Log = //Sys::Warning(1); Log << "Not implemented yet";
    return R;
}


crect crect::operator>>(crect Rhs)
{
    crect R = (*this) & Rhs;
    //...
    //auto Log = //Sys::Warning(1); Log << "Not implemented yet";
    return R;
}


crect crect::operator/(const crect&Rhs) const
{
    crect R;
    R.Assign(
        Rhs.A.X < A.X ? Rhs.A.X : A.X,
        Rhs.A.Y < A.Y ? Rhs.A.Y : A.Y,
        Rhs.B.X < B.X ? B.X : Rhs.B.X,
        Rhs.B.Y < B.Y ? B.Y : Rhs.B.Y
    );
    return R - A;
}

crect::operator std::string() const
{
    return std::format("({},{}) {},{} {}x{}",Cursor.X, Cursor.Y,A.X,A.Y,S.X,S.Y);
}



}
