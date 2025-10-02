//
// Created by oldlonecoder on 2025-09-29.
//

#include <catui/land/cmdargs.h>

#include "catui/io/console.h"


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


namespace cat::cmd
{



arg::iterator& line::query(std::string_view SwitchData)
{
    A = arguments.begin();
    std::string Check = SwitchData.data();
    for (; A != arguments.end(); ++A)
    {
        std::string str = A->name;
        std::string str2 = A->switch_text;
        std::string str3 = A->switch_char;
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        std::transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
        std::transform(str3.begin(), str3.end(), str3.begin(), ::toupper);
        cat::io::con << Check << " <> " << str << " " << str2 << " " << str3 << '\n';
        if ((Check == str ) || (Check == str2 ||( Check == str3)))
            return A;
    }
    return A;
}


line::~line()
{
    arguments.clear(); // doh ...

}


/*!
 * @brief input operator
 * @param Arg
 * @return Pointer to arg instance.
 * @author &copy;2023/2024, oldlonecoder/serge.luxsier@oldbitsnbytes.club
 *
 * @note Because of the action<>, We must instantiate a unique non-copiable arg using <i>new</i> to ensure
 * that there will be NO move/copy of the instances. We may instantiate directly into the arguments using emplace_back tho. -
 * to be considered...
 */
line& line::operator<<(const arg &Arg)
{
    arguments.push_back(Arg);
    arg Sw = arguments.back();
    Sw.name = Arg.name;
    Sw.switch_char = Arg.switch_char;
    Sw.switch_text = Arg.switch_text;
    Sw.descriptions = Arg.descriptions;
    Sw.required = Arg.required;
    Sw.count = 0;
    Sw.callback = Arg.callback;
    return *this;
}


/**
 *
 */
rem::code line::input(const std::vector<std::string_view>& StrArray)
{
    auto a = arguments.end();

    if(StrArray.empty())
        return rem::code::empty;

    for(auto sv : StrArray)
    {
        auto next = query(sv);

        //rem::debug() << color::cyan << "line::input" << color::white << '(' << color::yellow << sv << color::white << ") :";

        if(next == arguments.end())
        {
            // It is not a switch - so must be an argument data for the CurArg/NextArg...
            if((a != arguments.end()) &&
                (a->required > a->count) && (a->required > 0))
            {
                a->arguments.emplace_back(sv);
                ++a->count;
                a->enabled = true;
                //rem::debug() << color::yellow << (*a)->name << color::reset << " arg:" << (*a)->count << " '" << sv << '\'';
            }
            else
            {
                // ... or non-switch arg
                defaults.arguments.emplace_back(sv);
                ++defaults.count;
                defaults.enabled = true;
                //rem::debug() << color::yellow << defaults.name << color::reset << " arg:" << defaults.count << " '" << sv << '\'';
            }
        }
        else
        {
            if ((a != arguments.end()) && (a->count < a->required))
            {
                //rem::error() << " argument " << color::yellow << (*a)->name << color::reset << " is missing " << color::red4 << (*a)->required - (*a)->count << color::reset << " arguments / " << color::lime << (*a)->required;
                return rem::code::failed;
            }
            a = next;
            a->enabled = true;
        }
    }
    return rem::code::ok;
}


/**
 *
 */
rem::action  line::process()
{
    auto r = rem::action::end;
    if (!arguments.empty())
    {
        for (auto& arg : arguments)
        {
            if (arg)
            {
                if (arg.required > arg.count)
                {
                    arg.enabled = false;
                    // throw rem::except() << " arg '" << color::yellow << arg->name
                    //     << color::reset << " is missing "
                    //     << color::red4 << arg->required - arg->count
                    //     << color::reset << " arguments: requires "
                    //     << color::lime << arg->required;

                    // // throw did not work? :
                    // rem::except() << " if this is shown, it means exceptions are deactivated. i suggest to enable it... ";
                    // rem::write() << usage();
                    return rem::action::leave;

                }
                cat::io::con << "callback :" << (arg.callback != nullptr) << '\n';
                return arg.callback(arg);
            }
        }
    }
    if(!defaults.arguments.empty())
    {
        if(defaults.enabled)
        {
            r = defaults.callback(defaults);
            if (r != rem::action::cont)
                return rem::action::leave;
        }
    }
    return rem::action::cont;
}

arg &line::operator[](const std::string &ArgName)
{
    for(auto& Arg :arguments)
    {
        if(Arg.name == ArgName) return Arg;
    }
    return defaults;
}

std::string line::usage() const
{
    cat::utxt Str;
    Str << "usage:\n";
    cat::utxt Unused, Used, Used0;

    Unused << color::red1 << glyph::unauth;
    Used   << color::lightgreen2 << glyph::ok;

    Str << "------------------------------------------------------------------------------\n";
    for (auto Arg : arguments)
    {
        Str << std::format(line::expr,
                Arg.switch_char,
                Arg.switch_text ,
                Arg.descriptions ,
                (Arg.enabled ? Used() : Unused())
            );

        Str << color::reset << "\n------------------------------------------------------------------------------\n";
    }
    return Str();
}


/**
 *
 */
arg &line::add_cmd(const std::string &cId)
{
    arguments.push_back({});
    arg& Sw = arguments.back();
    Sw.name = cId;
    Sw.callback = nullptr;
    return Sw;
}


arg::~arg()
{
    arguments.clear();
    callback = nullptr;
}

arg &arg::set_descriptions(const std::string &Txt)
{
    descriptions = Txt;
    return *this;
}

arg &arg::set_char(const std::string &Txt)
{
    switch_char = Txt;
    return *this;
}

arg &arg::set_long_switch(const std::string &Txt)
{
    switch_text = Txt;
    return *this;
}

arg &arg::set_required(int N)
{
    required = N;
    return *this;
}
}
