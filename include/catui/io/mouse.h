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

#include <catui/io/polling.h>
#include <catui/land/geometry.h>

namespace cat::io
{

struct CATUI_LIB mouse
{
    ///////////////////////////////////////////////////////////////////////////////////////
    /// \brief BUTTON_UP
    /// ex.: button.left == Mouse::BUTTON_UP;
    static constexpr u8 BUTTON_UP = 0;
    ///////////////////////////////////////////////////////////////////////////////////////
    /// \brief BUTTON_PRESSED
    /// ex.: button.left == BUTTON_PRESSED;
    static constexpr u8 BUTTON_PRESSED = 3;
    ///////////////////////////////////////////////////////////////////////////////////////
    /// \brief BUTTON_DOWN
    /// ex.: button.left == Mouse::BUTTON_DOWN;
    static constexpr u8 BUTTON_DOWN = 1;
    ///////////////////////////////////////////////////////////////////////////////////////
    /// \brief BUTTON_RELEASE
    /// ex : button.left == BUTTON_RELEASE;
    static constexpr u8 BUTTON_RELEASE = 2;

    mouse()=default;
    ~mouse() = default;

    mouse(const mouse&);
    mouse(mouse&&) noexcept;

    mouse& operator=(const mouse& amouse);
    mouse& operator=(mouse&& amouse) noexcept;

    struct  buttons
    {
        u8 left  : 2; // 0 = up; 1 = down; 2 = pressed event; 3 = released event;
        u8 mid   : 2; // 0 = up; 1 = down; 2 = pressed event; 3 = released event;
        u8 right : 2; // 0 = up; 1 = down; 2 = pressed event; 3 = released event;
        u8 b4    : 2;
        u8 b5    : 2;
        u8 b6    : 2;
        u8 st    : 2; // 0: noevent; 1: pressed; 2: released;
    }button{0,0,0};

    struct
    {
        u8 shift :1;
        u8 alt   :1;
        u8 win   :1;
    }state{0,0,0};

    ui::cpoint pos{};
    ui::cpoint dxy{};

    bool left   (){return button.left;}
    bool middle (){return button.mid;}
    bool right  (){return button.right;}

    mouse& operator & (const mouse& mev);
    static std::pair<rem::code, mouse> parse(pollin& fd);
    static mouse smev;
    operator bool();
    std::string operator()() const;
    static std::string direction_arrow(ui::cpoint xy);
    bool pressed = false;
private:
    static std::pair<rem::code, mouse>  parse(bool arel, std::vector<int> args_);

};
} // namespace cat::io
