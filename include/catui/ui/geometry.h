
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


#pragma once
#include <catui/sys/rem.h>

namespace cat::ui
{

using namespace integers;
namespace Direction
{
using Value = u8;

static constexpr Value Left        = 0x0001; ///< Justify left
static constexpr Value Right       = 0x0002; ///< Justify right
static constexpr Value Up          = 0x0004; ///< Justify align horizontally at the center
static constexpr Value Down        = 0x0008; ///< Justify Align vertically at the center

}



struct cxy
{
    int x;
    int y;

    cxy(int X, int Y) : x(X), y(Y){}
    cxy() : x(0), y(0){}
    cxy(const cxy& P) : x(P.x), y(P.y){}
    cxy(cxy&& P) noexcept: x(P.x), y(P.y){}
    ~cxy() = default;
    cxy& operator=(const cxy& P) = default;
    cxy& operator=(cxy&& P) noexcept{ x = P.x; y = P.y; return *this; }
    cxy operator+(const cxy& P) const { return {x+P.x, y+P.y}; }
    cxy operator-(const cxy& P) const { return {x-P.x, y-P.y}; }
    cxy operator*(const cxy& P) const { return {x*P.x, y*P.y}; }
    cxy operator/(const cxy& P) const { return {x/P.x, y/P.y}; }
    cxy operator+(int P) const { return {x+P, y+P}; }
    cxy operator-(int P) const { return {x-P, y-P}; }

    bool        operator==(const cxy& P) const { return x == P.x && y == P.y; }
    bool        operator!=(const cxy& P) const { return x != P.x || y != P.y; }
    bool        operator<(const cxy& P) const { return x < P.x || (x == P.x && y < P.y); }
    bool        operator>(const cxy& P) const { return x > P.x || (x == P.x && y > P.y); }
    bool        operator<=(const cxy& P) const { return x <= P.x || (x == P.x && y <= P.y); }
    bool        operator>=(const cxy& P) const { return x >= P.x || (x == P.x && y >= P.y); }
    cxy&     operator+=(const cxy& P) { x += P.x; y += P.y; return *this; }
    cxy&     operator-=(const cxy& P) { x -= P.x; y -= P.y; return *this; }
    cxy&     operator*=(const cxy& P) { x *= P.x; y *= P.y; return *this; }
    cxy&     operator/=(const cxy& P) { x /= P.x; y /= P.y; return *this; }
    cxy&     operator+=(int P) { x += P; y += P; return *this; }
    cxy&     operator-=(int P) { x -= P; y -= P; return *this; }
    cxy&     operator ++();
    cxy&     operator ++(int);
    cxy&     operator --();
    cxy&     operator --(int);
    I64         Area() const { return static_cast<I64>(x)*static_cast<I64>(y);}
    explicit    operator std::string() const;
    std::string operator()() const { return std::string(*this); }

};

struct crect
{
    cxy a{},         ///< Topleft coords.
    b{},                ///< BootomRight coords.
    s{};                ///< Width, Height.
    cxy cursor{};    ///< Internal cursor - Modifiable by operator --(),++() -> cursor.x; ++(int),--(int) -> cursor.y
                        ///<  {0 <= cursor.x <= s.x};  {0 <= cursor.y <= s.y};
    Direction::Value  ScrollDirection = 0;
    bool NoWrap = false;
    crect() = default;
    crect(int X1, int X2, int Y1, int Y2);
    crect(cxy A, cxy B);
    crect(int X1, int Y1, cxy Sz);
    crect(const crect& R);
    crect(crect&& R) noexcept;
    ~crect() = default;

    ////////////// ----- cursor movements :
    bool operator++();
    bool operator++(int);
    bool operator--();
    bool operator--(int);
    // -------------------------------------

    // ------ Displacement operators : -------------
    crect& operator+=(cxy P);
    crect& operator-=(cxy P);
    crect& operator*=(cxy P);
    crect& operator/=(const crect& Rhs);
    // --------------------------------------------

    crect operator - (cxy P) const;
    crect operator + (cxy P) const;
    // ---- Intersect operators -------
    crect operator/(const crect& Rhs) const;
    crect operator&(const crect& Rhs) const;
    crect operator << (const crect&Rhs) const;
    crect operator >> (const crect&Rhs) const;
    crect operator | (const crect&rhs) const;
    crect& operator |= (const crect&rhs);
    // ----------------------------------

    // -- Copy and move assignment operatora:
    crect& operator=(const crect& R);
    crect& operator=(crect&& R) noexcept;
    void assign(int X1, int X2, int Y1, int Y2);
    void assign(int X1, int X2, cxy dxy);
    //----------------------------------------

    explicit operator std::string() const;
    std::string operator()() const { return std::string(*this); }
    [[nodiscard]] int Width() const { return s.x;}
    [[nodiscard]] int Height() const { return s.y;}

    void Assign(int X1, int X2, int Y1, int Y2);
    void Resize(cxy Sz);
    void Resize(int Dx, int Dy);

    crect Local() const { return (*this)-a; }

    bool operator[](cxy P) const;
    bool operator[](int Ix) const;
    bool SetCursorPos(cxy P);
    bool SetCursorPos(int Ix, int Iy);
    bool SetCursorOffset(int Ix);
    cxy top_left() const;
    cxy top_right() const;
    cxy bottom_left() const;
    cxy bottom_right() const;
    operator bool() const { return s.x > 0 && s.y > 0;}

};

}
