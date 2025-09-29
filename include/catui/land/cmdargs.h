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


#include <catui/land/sys/sys.h>
#include <functional>

namespace cat::cmd
{
struct  CATUI_LIB arg
{
    using data = std::vector<std::string_view>;
    using shared = std::shared_ptr<arg>;
    using array = std::vector<arg::shared>;
    using iterator = arg::array::iterator;

    // ----------  ------------------------------------------
    std::string            name;
    std::string            switch_char;
    std::string            switch_text;
    std::string            descriptions;
    int                    required { 0 }; ///< Required mandatory number of arguments.
    int                    count    { 0 }; ///< Number of arguments.
    //--------------------------------------------------------


    data                   arguments{};
    bool                   enabled{ false };
    std::function<rem::action(arg&)> callback{nullptr};

    explicit operator bool() const { return callback != nullptr; }

    template<typename T> rem::code set_handler(std::function<rem::action(arg&)>&& cb){
        callback = std::move(cb);
        return rem::code::accepted;
    }

    arg& set_descriptions(const std::string& Txt);
    arg& set_char(const std::string& Txt);
    arg& set_long_switch(const std::string& Txt);
    arg& set_required(int N);

    ~arg();
};



struct  CATUI_LIB line
{

    static constexpr auto expr = "{:>2s} | {:>20s} | {:>45s}";
    arg::array arguments;
    arg defaults;
    std::function<rem::action(arg&)> default_callback{nullptr};
    arg::iterator A{};
public:
    line() = default;
    ~line();

    template<typename T> void set_default_callback(T* Obj, std::function<rem::action(arg&)> Fn){
        default_callback = Fn;
    }

    arg::iterator& query(std::string_view arg);
    arg& operator<<(const arg& Arg);
    arg& operator [] (const std::string& ArgName);

    rem::code     input(const std::vector<std::string_view>& StrArray);
    arg& add_cmd(const std::string& cId);
    rem::action process();
    bool        empty() const { return arguments.empty(); }
    std::string usage() const;
};


}
