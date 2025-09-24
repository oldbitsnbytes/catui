
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
#include <catui/land/sys/rem.h>

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



struct cpoint
{
    int X;
    int Y;

    cpoint(int X, int Y) : X(X), Y(Y){}
    cpoint() : X(0), Y(0){}
    cpoint(const cpoint& P) : X(P.X), Y(P.Y){}
    cpoint(cpoint&& P) noexcept: X(P.X), Y(P.Y){}
    ~cpoint() = default;
    cpoint& operator=(const cpoint& P) = default;
    cpoint& operator=(cpoint&& P) noexcept{ X = P.X; Y = P.Y; return *this; }
    cpoint operator+(const cpoint& P) const { return {X+P.X, Y+P.Y}; }
    cpoint operator-(const cpoint& P) const { return {X-P.X, Y-P.Y}; }
    cpoint operator*(const cpoint& P) const { return {X*P.X, Y*P.Y}; }
    cpoint operator/(const cpoint& P) const { return {X/P.X, Y/P.Y}; }
    cpoint operator+(int P) const { return {X+P, Y+P}; }
    cpoint operator-(int P) const { return {X-P, Y-P}; }

    bool        operator==(const cpoint& P) const { return X == P.X && Y == P.Y; }
    bool        operator!=(const cpoint& P) const { return X != P.X || Y != P.Y; }
    bool        operator<(const cpoint& P) const { return X < P.X || (X == P.X && Y < P.Y); }
    bool        operator>(const cpoint& P) const { return X > P.X || (X == P.X && Y > P.Y); }
    bool        operator<=(const cpoint& P) const { return X <= P.X || (X == P.X && Y <= P.Y); }
    bool        operator>=(const cpoint& P) const { return X >= P.X || (X == P.X && Y >= P.Y); }
    cpoint&     operator+=(const cpoint& P) { X += P.X; Y += P.Y; return *this; }
    cpoint&     operator-=(const cpoint& P) { X -= P.X; Y -= P.Y; return *this; }
    cpoint&     operator*=(const cpoint& P) { X *= P.X; Y *= P.Y; return *this; }
    cpoint&     operator/=(const cpoint& P) { X /= P.X; Y /= P.Y; return *this; }
    cpoint&     operator+=(int P) { X += P; Y += P; return *this; }
    cpoint&     operator-=(int P) { X -= P; Y -= P; return *this; }
    cpoint&     operator ++();
    cpoint&     operator ++(int);
    cpoint&     operator --();
    cpoint&     operator --(int);
    I64         Area() const { return static_cast<I64>(X)*static_cast<I64>(Y);}
    explicit    operator std::string() const;
    std::string operator()() const { return std::string(*this); }

};

struct crect
{
    cpoint A{},         ///< Topleft coords.
    B{},                ///< BootomRight coords.
    S{};                ///< Width, Height.
    cpoint Cursor{};    ///< Internal Cursor - Modifiable by operator --(),++() -> Cursor.X; ++(int),--(int) -> Cursor.Y
                        ///<  {0 <= Cursor.X <= S.X};  {0 <= Cursor.Y <= S.Y};
    Direction::Value  ScrollDirection = 0;
    bool NoWrap = false;
    crect() = default;
    crect(int X1, int X2, int Y1, int Y2);
    crect(cpoint A, cpoint B);
    crect(int X1, int Y1, cpoint Sz);
    crect(const crect& R);
    crect(crect&& R) noexcept;
    ~crect() = default;

    ////////////// ----- Cursor movements :
    bool operator++();
    bool operator++(int);
    bool operator--();
    bool operator--(int);
    // -------------------------------------

    // ------ Displacement operators : -------------
    crect& operator+=(cpoint P);
    crect& operator-=(cpoint P);
    crect& operator*=(cpoint P);
    crect& operator/=(const crect& Rhs);
    // --------------------------------------------

    crect operator - (cpoint P) const;
    crect operator + (cpoint P) const;
    // ---- Intersect operators -------
    crect operator/(const crect& Rhs) const;
    crect operator&(const crect& Rhs) const;
    crect operator << (crect Rhs);
    crect operator >> (crect Rhs);
    // ----------------------------------

    // -- Copy and move assignment operatora:
    crect& operator=(const crect& R);
    crect& operator=(crect&& R) noexcept;
    //----------------------------------------

    explicit operator std::string() const;
    std::string operator()() const { return std::string(*this); }
    [[nodiscard]] int Width() const { return S.X;}
    [[nodiscard]] int Height() const { return S.Y;}

    void Assign(int X1, int X2, int Y1, int Y2);
    void Resize(cpoint Sz);
    void Resize(int Dx, int Dy);

    crect Local() const { return (*this)-A; }

    bool operator[](cpoint P) const;
    bool operator[](int Ix) const;
    bool SetCursorPos(cpoint P);
    bool SetCursorPos(int Ix, int Iy);
    bool SetCursorOffset(int Ix);

    operator bool() const { return S.X > 0 && S.Y > 0;}

};

}
