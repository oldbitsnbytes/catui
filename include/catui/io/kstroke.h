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

namespace cat::io
{
struct  CATUI_LIB kstroke
{
    enum enums : u8
    {
        ARROW_UP              ,
        ARROW_DOWN            ,
        ARROW_LEFT            ,
        ARROW_RIGHT           ,
        ENTER                 ,
        ESCAPE                ,
        BACKSPACE             ,
        HOME                  ,
        END                   ,
        PAGE_UP               ,
        PAGE_DOWN             ,
        INSERT                ,
        DELETE                ,
        TAB                   ,
        F1                    ,
        F2                    ,
        F3                    ,
        F4                    ,
        F5                    ,
        F6                    ,
        F7                    ,
        F8                    ,
        F9                    ,
        F10                   ,
        F11                   ,
        F12                   ,
        SHIFT_ARROW_UP        ,
        SHIFT_ARROW_DOWN      ,
        SHIFT_ARROW_LEFT      ,
        SHIFT_ARROW_RIGHT     ,
        SHIFT_END             ,
        SHIFT_HOME            ,
        SHIFT_PAGE_UP         ,
        SHIFT_PAGE_DOWN       ,
        SHIFT_F1              ,
        SHIFT_F2              ,
        SHIFT_F3              ,
        SHIFT_F4              ,
        SHIFT_F5              ,
        SHIFT_F6              ,
        SHIFT_F7              ,
        SHIFT_F8              ,
        SHIFT_F9              ,
        SHIFT_F10             ,
        SHIFT_F11             ,
        SHIFT_F12             ,
        SHIFT_TAB             ,
        SHIFT_ENTER           ,
        CTRL_PAGE_UP          ,
        CTRL_PAGE_DOWN        ,
        CTRL_DELETE           ,
        CTRL_END              ,
        CTRL_ARROW_LEFT       ,
        CTRL_ARROW_RIGHT      ,
        CTRL_ARROW_UP         ,
        CTRL_ARROW_DOWN       ,
        CTRL_HOME             ,
        CTRL_INSERT           ,
        CTRL_Q                ,
        CTRL_S                ,
        CTRL_V                ,
        CTRL_BACKSPACE        ,
        CTRL_F8               ,
        ALT_ARROW_LEFT        ,
        ALT_ARROW_RIGHT       ,
        ALT_ARROW_UP          ,
        ALT_ARROW_DOWN        ,
        SHIFT_CTRL_ARROW_LEFT ,
        SHIFT_CTRL_ARROW_RIGHT,
        SHIFT_CTRL_ARROW_UP   ,
        SHIFT_CTRL_ARROW_DOWN ,
        SHIFT_CTRL_DEL        ,
        SHIFT_CTRL_HOME       ,
        SHIFT_ALT_ARROW_LEFT  ,
        SHIFT_ALT_ARROW_RIGHT ,
        SHIFT_ALT_ARROW_UP    ,
        SHIFT_ALT_ARROW_DOWN  ,
        SHIFT_ALT_END         ,
        SHIFT_ALT_HOME        ,
        SHIFT_ALT_PAGE_UP     ,
        SHIFT_ALT_PAGE_DOWN   ,
        CTRL_ALT_ARROW_LEFT   ,
        CTRL_ALT_ARROW_RIGHT  ,
        CTRL_ALT_ARROW_UP     ,
        CTRL_ALT_ARROW_DOWN   ,
        CHARACTER             ,
        NO_KEY,
    };
    struct  state
    {
        u8 shift : 1;
        u8 ctrl  : 1;
        u8 alt   : 1;
        u8 sup   : 1;
    }kst{0,0,0,0};

    kstroke::enums       mnemonic{kstroke::NO_KEY};
    u64 kcode{0};
    std::string name{"no_key"};

    kstroke() = default;
    ~kstroke(){name.clear();}

    kstroke(kstroke::enums e,  u64 c, const std::string& n);

    kstroke(kstroke&& ks) noexcept{ *this = std::move(ks);}
    kstroke& operator=(kstroke&& akst)noexcept
    {
        kst = akst.kst;
        mnemonic = akst.mnemonic;
        kcode = akst.kcode;
        name = akst.name;

        return *this;
    }
    kstroke(const kstroke& akst)
    {
        *this = akst;
    }
    kstroke& operator=(const kstroke& akst)
    {
        kst = akst.kst;
        mnemonic = akst.mnemonic;
        kcode = akst.kcode;
        name = akst.name;
        return *this;
    }

    explicit operator bool() const{ return mnemonic != kstroke::NO_KEY;};

    using refdb = std::map<kstroke::enums, kstroke>;
    using textdb = std::map<std::string_view, kstroke>;

    using dbgroup = std::vector<kstroke>;
    static dbgroup keysdb;

    static kstroke query(u64 bytes_seq);
    static kstroke query(std::string_view s);
    static std::pair<rem::code, kstroke> parse(pollin& fd);

    static kstroke none;


private:

};
} // namespace cat::io
