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


#include <catui/io/console.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <unistd.h>


namespace cat::io::console
{

termios _saved, _this;
ui::crect       _geometry{};
color::pair     _colors{};

u8                  _flags{0};
u8                  _state{0};

pollfd              _con_events={
        .fd     = STDIN_FILENO,
        .events = POLLIN|POLLHUP|POLLERR,
        .revents= 0,
};

cat::io::pollin _pollin(_con_events, 1024, nullptr);



rem::code start()
{
    tcgetattr(STDIN_FILENO, &_saved);
    _this = _saved;

    _this.c_iflag &= ~(BRKINT | PARMRK | ISTRIP | IGNCR | IXON );
    _this.c_oflag &= ~OPOST;
    _this.c_cflag |= (CS8);
    _this.c_cflag &= ~PARENB;
    _this.c_lflag &= ~(ICANON | ECHO | IEXTEN | TOSTOP | ECHONL);
    _this.c_cc[VMIN] = 0;
    _this.c_cc[VTIME] = 1;
    _this.c_cc[VSTART] = 0;
    _this.c_cc[VSTOP] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &_this);

    //sys::write() << " terminal set to raw mode..." << //sys::endl;

    //::signal(SIGWINCH, &terminal::resize_signal); // --> Must be Handled in the thread/proc/ env
    //if(_flags & terminal::use_double_buffer)
    //Console::SwitchAlternate();
    caret_off();
    get_geometry();
    start_mouse();
    save_screen();

    // Fd.SetReadFN([](IO::UFD& Ufd) -> Rem::Action {
    //     if (auto R =  Console::StdInProc(Ufd); !R)
    //     {
    //         Sys::Error(1) << "StdInProc() failed!" << Rem::Fn::Endl;
    //         return Rem::Action::End;
    //     }
    //     return Rem::Action::Continue;
    // });

    return rem::code::done;
}


void caret_off()            { std::cout << "\x1b[?25l"; std::cout.flush(); }
void caret_on()             { std::cout << "\x1b[?25h"; std::cout.flush(); }
void clear()                { std::cout << "\x1b[2J"; std::cout.flush(); }
void clear_line()           { std::cout << "\x1b[2K"; std::cout.flush(); }
void clear_to_bottom()      { std::cout << "\x1b[0J"; std::cout.flush(); }
void clear_to_top()         { std::cout << "\x1b[1J"; std::cout.flush(); }
void clear_to_end_line()    { std::cout << "\x1b[0K"; std::cout.flush(); }
void clear_to_start_line()  { std::cout << "\x1b[1K"; std::cout.flush(); }
void move_cursor_down()     { std::cout << "\x1b[1B"; std::cout.flush(); }
void move_cursor_left()     { std::cout << "\x1b[1D"; std::cout.flush(); }
void move_cursor_right()    { std::cout << "\x1b[1C"; std::cout.flush(); }
void move_cursor_up()       { std::cout << "\x1b[1A"; std::cout.flush(); }


rem::code get_geometry()
{
    winsize win{};
    ioctl(fileno(stdout), TIOCGWINSZ, &win);
    if((!win.ws_col)||(!win.ws_row))
        return rem::code::rejected;

    _geometry = {0,0, {win.ws_col, win.ws_row}};

    // debug or info:
    auto log = sys::info(); log << " (new) terminal size: [" // << color::yellow << std::string(std::format("{:>3d}x{:<3d}",_geometry.S.X,_geometry.S.Y)).c_str() << color::r << "]" << log;
                                << color::yellow << _geometry.S.X
                                << color::r << "x"
                                << color::yellow << _geometry.S.Y << color::r;

    return rem::code::done;
}


/**
 *
 */
void save_screen()
{
    std::cout << "\x1b[0m\x1b[?1049h" << std::flush;
    _flags |= ST_SAVED;

}

void restore_screen()
{
    std::cout << "\x1b[0m\x1b[?1049l" << std::flush;
    _flags &= ~ST_SAVED;
}


/**
 * @brief Set terminal to report the mouse events.

    @note Execute CSI on each parameters because I realized that "\x1b[?1000;1002;...h" is not working.
 *
 */
rem::code start_mouse()
{
    //std::cout << MOUSE_VT200            << terminal::SET;
    std::cout << MOUSE_REPORT_BUTTONS   << SET;
    //std::cout << MOUSE_REPORT_ANY       << SET << std::flush;
    std::cout << MOUSE_SGR_EXT_MODE     << SET<< std::flush;
    //std::cout << MOUSE_URXVT_MODE       << SET << std::flush;
    _flags |= USE_MOUSE;

    return rem::code::accepted;
}

rem::code stop_mouse()
{
    //std::cout << MOUSE_VT200            << RESET;
    std::cout << MOUSE_REPORT_BUTTONS   << RESET;
    //std::cout << MOUSE_REPORT_ANY       << RESET;
    std::cout << MOUSE_SGR_EXT_MODE     << RESET << std::flush;
    //std::cout << MOUSE_URXVT_MODE       << RESET << std::flush;

    _flags &= ~USE_MOUSE;

    return rem::code::accepted;
}


rem::code end()
{
    caret_on();
    stop_mouse();
    restore_screen();
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &_saved);
    return rem::code::done;
}


cat::io::pollin& poll_fd()
{
    return _pollin;
}


mk_event::mk_event(kstroke&& ks)
{
    k=ks;
    k = {};
}


mk_event::mk_event(mouse&&mev)
{
    m = mev;
    mev={};
}


mk_event& mk_event::operator=(mk_event&& ce) noexcept
{

    return *this;
}


mk_event& mk_event::operator=(const mk_event&)
{
    return *this;
}
} // namespace cat::io::console;



namespace cat
{



conio& conio::operator << (const char* str)
{
    std::cout << str;
    return *this;
}


conio& conio::operator<<(color::value clr)
{
    std::cout << color::render_rgb(clr);
    return *this;
}


conio& conio::operator<<(color::pair clr)
{
    std::cout << color::render_rgb(clr);
    return *this;
}


conio& conio::operator<<(rem::code c)
{
    std::cout << rem::render(c);
    return *this;
}


conio& conio::operator<<(rem::type ty)
{
    std::cout << rem::to_string(ty);
    return *this;
}


conio& conio::operator<<(ui::cpoint xy)
{
    std::cout << std::format(io::console::set_caret_pos, xy.Y,xy.X);//"\x1b[" << xy.Y << ";" << xy.X << "H";
    std::cout.flush();
    return *this;
}


conio& conio::operator<<(glyph::value f)
{
    std::cout << glyph::data[f];
    return *this;
}


conio& conio::operator<<(ui::vchar::pad& ui_bloc)
{

    for (int Y=0; Y<ui_bloc.geometry.S.Y; ++Y)
    {
        con << ui_bloc.geometry.A + ui::cpoint{0,Y} << ui_bloc.colors << ui::vchar::render_line(ui_bloc[{0,Y}],ui_bloc.geometry.Width());
    }

    return *this;
}


conio& conio::operator>>(int&i)
{
    io::console::poll_fd()();
    i = 42;
    return *this;
}
} // io
