//
// Created by Serge Lussier on 2025-09-24.
//

//#ifndef CATUI_SYS_H
//#define CATUI_SYS_H
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
#include <catui/utxt.h>
#include <source_location>

using namespace cat::integers;
using cat::ui::color;
using cat::glyph;




class CATUI_LIB sys
{
    static std::vector<std::string> _ram;

public:
    enum  fn: u8
    {
        eol = 0,

       //...
    };

    static int indent,indentsize;
    struct CATUI_LIB out
    {
        struct header_component
        {
            U8 Type  : 1;
            U8 Stamp : 1;
            U8 Fun   : 1;
            U8 File  : 1;
            U8 Line  : 1;
            U8 Col   : 1;
            U8 HLine : 1;
            U8 VLine : 1;
            U8 BorderFrame : 1; ///< 1 = enable vline|hline|corners and joints.
            //...
        };
        rem::type type{};
        rem::code code{};
        std::source_location location{};
        // ---------------------------------
        cat::utxt  text{};
        cat::utxt  header{};

        header_component header_data{1,1,1,1,1,1,0,0,0};
        out() = default;
    private:
        out(rem::type message, std::source_location&& src={});
        out(rem::type message, sys::out::header_component hc, std::source_location&& src={});
        static std::string location_tail(const std::string& Fn);
        friend class sys;
    public:
        ~out();

        void init_header();
        out& write();
        out& eol();
        out& operator << (out&);
        out& operator << (const std::string&);
        out& operator << (const char*);
        out& operator << (std::string_view);
        //out& operator << (std::string str);
        out& operator << (char c);
        out& operator << (color::value clr);
        out& operator << (color::pair clr);
        out& operator << (rem::code c);
        out& operator << (rem::type ty);
        out& operator << (rem::fn f);
        out& operator << (glyph::value f);
        out& operator << (cat::utxt ut);
        out& operator << (cat::ui::cpoint xy);
        out& operator << (sys::fn f);
        // Out& operator << (whinfo z);
        out& operator << (cat::ui::crect rect);
        //out& operator << (string2d s2d);

        template<typename T> out& operator << (const T& v)
        {
            std::ostringstream o;
            o << v;
            text << o.str();
            return *this;
        }

    };

    sys()=delete;
    ~sys() = default;


    static sys::out error       (std::source_location&& src = std::source_location::current());
    static sys::out status      (std::source_location&& src = std::source_location::current());
    static sys::out warning     (std::source_location&& src = std::source_location::current());
    static sys::out fatal       (std::source_location&& src = std::source_location::current());
    static sys::out except      (std::source_location&& src = std::source_location::current());
    static sys::out message     (std::source_location&& src = std::source_location::current());
    static sys::out write       (std::source_location&& src = std::source_location::current());
    static sys::out debug       (std::source_location&& src = std::source_location::current());
    static sys::out info        (std::source_location&& src = std::source_location::current());
    static sys::out comment     (std::source_location&& src = std::source_location::current());
    static sys::out syntax      (std::source_location&& src = std::source_location::current());
    static sys::out test        (std::source_location&& src = std::source_location::current());
    static sys::out interrupted (std::source_location&& src = std::source_location::current());
    static sys::out aborted     (std::source_location&& src = std::source_location::current());
    static sys::out segfault    (std::source_location&& src = std::source_location::current());
    static sys::out log         (std::source_location&& src = std::source_location::current());
    //...

    static rem::code flush(std::string_view filename);

    class CATUI_LIB exception :  public std::exception
    {
    public:

        explicit exception():std::exception() { _e_ = true; }
        explicit exception(const char *txt) { _msg_ = txt; _e_ = false; }
        explicit exception(const std::string &txt) { _msg_ = txt; _e_ = false; }

        ~exception() noexcept override {
            _msg_.clear();
        }

        const char* what() const noexcept override;

        sys::exception operator[](const sys::out& el);
    private:
        bool _e_;
        mutable std::string _msg_;
        sys::out _log_;
    };

private:


    
};


//#endif //CATUI_SYS_H
