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


using cat::ui::cxy;
using cat::ui::crect;

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
    ;
}


rem::code application::setup()
{
    io::console::start();
    return rem::code::done;
}


rem::code application::run()
{
    setup();
    try
    {
        auto element = std::make_shared<ui::element>(nullptr,"First element",0);
        element->set_theme("C128");
        element->set_geometry(crect{1,1,20,5});
        element->draw();
        element->update();

        cat::con << rem::code::ready << conio::eol;
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
                cat::con << cev.m.pos << cat::ui::crect{cev.m.pos.x,cev.m.pos.y,{20,5}};
                sys::debug() << "mouse event: " << cev.m() << sys::eol;
            }
        }
        cat::con << "press " << color::blue << glyph::mouse << color::r << "| " << color::skyblue3 << glyph::esc << conio::eol;
        cat::con >> cat::io::console::ignore;
        cat::io::console::end();
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    end();
    return rem::code::success;
}


rem::code application::end()
{
    io::console::end();
    sys::flush("catui_test.sys");
    return rem::code::done;
}
} // cat
