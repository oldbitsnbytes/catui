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
#include <catui/io/console.h>
#include <catui/dom/object.h>

namespace cat
{


class CATUI_LIB application
{
    CLASSNAME_START(application)
    cat::string::view_list _arguments{};
    dom::object::shared _root{nullptr};
    color::db::palette* _palette{nullptr};
    std::string _theme_id{"C64"};

public:
    application();
    application(const std::string& app_name,cat::string::view_list&& arguments);
    virtual ~application();
    virtual rem::code setup();
    virtual rem::code run();
    virtual rem::code end();

    virtual rem::code setup_ui();
    virtual rem::code set_global_theme(const std::string& theme_name);
    std::string theme_id() const { return _theme_id; }
protected:
    static void install_signals();

    static void sig_segv(int);
    static void sig_aborted(int);
    static void sig_interrupted(int);
    static void sig_winch(int);
    static void sig_hup(int);
    static void sig_term(int);
    static void sig_kill(int);
    static void sig_pipe(int);

    // static void sig_usr1(int);
    // static void sig_usr2(int);
    // static void sig_chld(int);
    // static void sig_cont(int);
    // static void sig_stop(int);
    // static void sig_tstp(int);
    // static void sig_ttin(int);
    // static void sig_ttou(int);
    // static void sig_urg(int);
    // static void sig_xcpu(int);
    // static void sig_xfsz(int);
    // static void sig_vtalrm(int);
    //


};
} // cat

//#endif //CATUI_APPLICATION_H
