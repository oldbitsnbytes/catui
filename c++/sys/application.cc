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

#include <catui/sys/application.h>
#include <catui/io/console.h>
#include <catui/ui/dom/object.h>

#include <csignal>


using cat::ui::cxy;
using cat::ui::rectangle;
using namespace cat::ui;
namespace cat
{

application::application()
{
    ;
}


application::application(const std::string&app_name, cat::string::view_list&& arguments)
{

}


application::~application()
{
    sys::info() << "application::~application(); terminate interactive console and flush remaining application logs{ catui_tests.sys." << sys::eol;
    io::console::end();
    sys::flush("catui_test.sys");
}


rem::code application::setup()
{
    application::install_signals();
    io::console::start();
    _root = std::make_shared<dom::object>(nullptr, "root");
    _root->set_theme("C128");
    _root->set_dom_status(dom::dom_status_enums::active);
    _root->set_geometry({cxy{2,5},ui::csz{40,5}});
    con.render(*_root->bloc_dc(), {});
    return rem::code::done;
}


rem::code application::run()
{
    setup();
    try
    {

        con << rem::code::ready << conio::eol;

        bool fini = false;
        while (!fini)
        {
            auto cev = cat::conio::wait();
            if (cev.is<cat::io::kstroke>())
            {
                cat::con << cxy{1,3} <<  "keystroke (mnemonic name): " << cat::io::kstroke::name(cev.k.mnemonic) << conio::eol;
                sys::debug() << "keystroke (mnemonic name): " << cat::io::kstroke::name(cev.k.mnemonic) << sys::eol;
                if (cev.k.mnemonic == cat::io::kstroke::ESCAPE)
                    fini = true;
            }
            else
            {
                cat::con << cxy{1,3} << "mouse event: " << cev.m() << conio::eol;
                cat::con << cev.m.pos << cat::ui::rectangle{cev.m.pos,ui::csz{20,5}};
                sys::debug() << "mouse event: " << cev.m() << sys::eol;
            }
        }
        cat::con << "press " << color::blue << glyph::mouse << color::r << "| " << color::skyblue3 << glyph::esc << conio::eol;
        cat::con >> cat::io::console::ignore;
        return end();
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return end();
    }
}


rem::code application::end()
{
    // io::console::end();
    // sys::flush("catui_test.sys");
    // return rem::code::done;
    return rem::code::ok;
}

void application::install_signals()
{
        std::signal(SIGSEGV, &application::sig_crash);
        sys::info()  << "signal SIGSEV installed."  << sys::eol;
        std::signal(SIGABRT, &application::sig_aborted);
        sys::info() << "signal SIGABRT installed."  << sys::eol;
        std::signal(SIGINT, &application::sig_interrupted);
        sys::info() << "signal SIGINT installed."  << sys::eol;
        std::signal(SIGWINCH, &application::sig_winch);
        sys::info() << "signal SIGWINCH installed."  << sys::eol;
        // std::signal(SIGHUP, &application::sig_winch);
        std::signal(SIGKILL, &application::sig_interrupted);
        sys::info() << "signal SIGKILL installed." << sys::eol;
        std::signal(SIGTERM, &application::sig_interrupted);
        sys::info() << "signal SIGTERM installed." << sys::eol;
}


void application::sig_crash(int)
{
    sys::segfault() << "SIGSEGV" << sys::eol;
    sys::flush("catui_test.sys");
    io::console::end();
}


void application::sig_aborted(int)
{
    sys::aborted() << "SIGABRT" << sys::eol;
    sys::flush("catui_test.sys");
    io::console::end();
}


void application::sig_interrupted(int)
{
    sys::interrupted() << "SIGINT" << sys::eol;
    sys::flush("catui_test.sys");
    io::console::end();
}


void application::sig_winch(int)
{
    sys::info() << "SIGWINCH" << sys::eol;
    io::console::get_geometry();
}


void application::sig_hup(int)
{
    sys::info() << "SIGHUP" << sys::eol;

}


void application::sig_term(int)
{
    sys::info() << "SIGTERM" << sys::eol;
    sys::flush("catui_test.sys");
    io::console::end();
}


void application::sig_kill(int)
{
    sys::info() << "SIGKILL" << sys::eol;
    sys::flush("catui_test.sys");
    io::console::end();
}


void application::sig_pipe(int)
{
}


// void application::sig_segv(int)
// {
//     sys::info() << "SIGSEGV" << sys::eol;
//     sys::flush("catui_test.sys");
//     io::console::end();
// }

} // cat
