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
using cat::color;
using cat::glyph;

class CATUI_LIB sys
{
    static std::vector<std::string> _ram;

public:


    struct out
    {
        std::ostream* OutFilePtr{&std::cout};
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
        std::string  text{};
        std::string  header{};

        header_component header_data{1,1,1,1,1,1,0,0,0};
        out() = default;
    private:
        out(rem::type message, std::source_location&& src={});
        out(rem::type message, sys::out::header_component hc, std::source_location&& src={});
        std::string location_tail(const std::string& Fn);
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
        out& operator << (std::string str);
        out& operator << (char c);
        out& operator << (color::value clr);
        out& operator << (color::pair clr);
        out& operator << (rem::code c);
        out& operator << (rem::type ty);
        out& operator << (rem::fn f);
        out& operator << (glyph::value f);
        //out& operator << (CPoint xy);
        // Out& operator << (whinfo z);
        //out& operator << (CRect Rect);
        //out& operator << (string2d s2d);

        template<typename T> out& operator << (const T& v)
        {
            std::ostringstream o;
            o << v;
            text += o.str();
            return *this;
        }

    };

    sys()=delete;
    ~sys() = default;


    static sys::out Error       (std::source_location&& src = std::source_location::current());
    static sys::out Status      (std::source_location&& src = std::source_location::current());
    static sys::out Warning     (std::source_location&& src = std::source_location::current());
    static sys::out Fatal       (std::source_location&& src = std::source_location::current());
    static sys::out Except      (std::source_location&& src = std::source_location::current());
    static sys::out Message     (std::source_location&& src = std::source_location::current());
    static sys::out Write       (std::source_location&& src = std::source_location::current());
    static sys::out Debug       (std::source_location&& src = std::source_location::current());
    static sys::out Info        (std::source_location&& src = std::source_location::current());
    static sys::out Comment     (std::source_location&& src = std::source_location::current());
    static sys::out Syntax      (std::source_location&& src = std::source_location::current());
    static sys::out Test        (std::source_location&& src = std::source_location::current());
    static sys::out Interrupted (std::source_location&& src = std::source_location::current());
    static sys::out Aborted     (std::source_location&& src = std::source_location::current());
    static sys::out Segfault    (std::source_location&& src = std::source_location::current());
    static sys::out Log         (std::source_location&& src = std::source_location::current());
    //...

    static rem::code CloseAll();
    //static sys::File& Cet(sys::File::Handle h);
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
