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
#include <signal.h>

namespace cat::io::console
{

termios _saved, _this;
ui::rectangle       _geometry{};
color::pair     _colors{};

u8                  _flags{0};
u8                  _state{0};

pollfd              _con_events={
        .fd     = STDIN_FILENO,
        .events = POLLIN|POLLHUP|POLLERR,
        .revents= 0,
};

cat::io::pollin _pollin(_con_events, 1024, nullptr);


void resize_signal(int i)
{
    get_geometry();
    CONSOLE_RESIZE_FLAG = true;
    //...
}


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

    ::signal(SIGWINCH, &console::resize_signal); // --> Must be Handled in the thread/proc/ env

    caret_off();
    get_geometry();
    start_mouse();
    save_screen();

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

    _geometry = {{0,0}, ui::csz{win.ws_col, win.ws_row}};

    // debug or info:
    sys::info() << " console geometry: ["
                << color::yellow << _geometry.size.w
                << color::r << "x"
                << color::yellow << _geometry.size.h << color::r << ']' << sys::eol;

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


mk_event::mk_event(const kstroke& ks)
{
    k=ks;
    event_type = mk_event::type::KEY_EVENT;
}


mk_event::mk_event(const mouse& mev)
{
    m = mev;
    event_type = mk_event::type::MOUSE_EVENT;
}


mk_event::~mk_event()
{
    ;
}


mk_event& mk_event::operator=(const mk_event& cev)
{
    if (cev.is<kstroke>()) k = cev.k;
    else if (cev.is<mouse>()) m = cev.m;
    event_type = cev.event_type;
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


conio& conio::operator<<(ui::cxy xy)
{
    std::cout << std::format(io::console::set_caret_pos, xy.y+1,xy.x+1);//"\x1b[" << xy.y << ";" << xy.x << "H";
    std::cout.flush();
    return *this;
}


conio& conio::operator<<(glyph::value f)
{
    std::cout << glyph::data[f];
    return *this;
}


conio& conio::operator<<(ui::vchar::bloc& ui_bloc)
{

    sys::debug() << rem::fn::func << ": " << ui_bloc.geometry.size << " << " << ui_bloc.geometry.a << sys::eol;
    for (int Y=0; Y<ui_bloc.geometry.size.h; ++Y)
    {
        auto t = ui_bloc.render(ui::cxy{0,Y},ui_bloc.geometry.size.w);
        con << ui_bloc.geometry.a + ui::cxy{0,Y} << t;
        sys::write() << t << sys::eol;
    }

    return *this;
}


conio& conio::operator<<(ui::rectangle rect)
{
    *this << rect.top_left() << ui::border::TopLeft
        << rect.top_right() << ui::border::TopRight
        << rect.bottom_left() << ui::border::BottomLeft
        << rect.bottom_right() << ui::border::BottomRight;


    for (int x = 1; x < rect.size.w-1; ++x)
    {
        *this << rect.a + ui::cxy{x,0};
        *this << ui::border::Horizontal;
        *this << ui::cxy{rect.a.x+x,rect.b.y};
        *this << ui::border::Horizontal;
    }

    for (int y =1; y < rect.size.h-1; ++y)
    {
        *this << rect.a + ui::cxy{0,y};
        *this << ui::border::Vertical;
        *this << ui::cxy{rect.b.x,rect.a.y+y};
        *this << ui::border::Vertical;
    }
    return *this;
}


conio& conio::operator<<(ui::border::Index idx)
{
    std::cout << ui::border()[idx];
    return *this;
}


conio& conio::operator<<(conio::movfn mv)
{
    switch (mv)
    {
        case conio::up:
            std::cout << "\x1b[1A";
            break;
        case conio::down:
            std::cout << "\x1b[1B";
            break;
        case conio::left:
            std::cout << "\x1b[1D";
            break;
        case conio::right:
            std::cout << "\x1b[1C";
            break;
        // case conio::home:
        //     std::cout << "\x1b[1~";
        //     break;
        // case conio::end:
        //     std::cout << "\x1b[4~";
        //     break;
        // case conio::page_up:
        //     std::cout << "\x1b[5~";
        //     break;
        // case conio::page_down:
        //     std::cout << "\x1b[6~";
        //     break;
        // case conio::insert:
        //     std::cout << "\x1b[2~";
        //     break;
        // case conio::delete_:
        //     std::cout << "\x1b[3~";
        //     break;
        // case conio::bol:
        //     std::cout << "\x1b[1G";
        //     break;
        // case conio::endl:
        //     std::cout << "\x1b[0K";
        //     break;
        // case conio::to_start_line:
        //     std::cout << "\x1b[1K";
        case conio::eol:
            std::cout << "\r\n";
            break;
    }
    return *this;
}


conio& conio::operator>>(int&i)
{
    io::console::poll_fd()();
    i = 42;
    return *this;
}


/**
 * @brief Renders a UI block within a specified rectangular area.
 *
 * This function calculates the intersection of the provided UI block geometry
 * and the current console geometry. If a rectangle is specified, it further
 * intersects it with the offset adjusted by the block's geometry. The rendering
 * is performed line-by-line within the determined area.
 *
 * @param ui_bloc Reference to the UI block (of type `ui::vchar::bloc`) that
 *        contains the content and color information for rendering.
 * @param rect Optional rectangle (of type `ui::rectangle`). If provided, it defines
 *        the clipping area for rendering relative to the block geometry.
 *
 * @return `rem::code::accepted` if the rendering succeeds within the calculated area.
 *         `rem::code::rejected` if the UI block or rectangle does not intersect
 *         with the console geometry.
 */
rem::code conio::render(ui::vchar::bloc& ui_bloc, const ui::rectangle& local_area)
{

    ui::rectangle ui_area = ui_bloc.geometry.to_local();

    if (local_area)
    {
        ui_area = ui_bloc.geometry.to_local() & local_area;
        if (!ui_area) return rem::code::rejected;
    }

    for (int y = 0; y < ui_area.height(); ++y)
    {
        con << ui_bloc.geometry.a+ui_area.a+ui::cxy{0,y}  << ui_bloc.render(ui_area.a+ui::cxy{0,y}, ui_area.width());
    }
    con << eol;
    return rem::code::accepted;

}


io::console::mk_event conio::wait()
{
    if (!!io::console::poll_fd()())
    {
        // swallow copy
        auto in = io::console::poll_fd();
        if (auto [r,ev] = io::kstroke::parse(in); !!r)
            return io::console::mk_event(ev);
        if (auto [r,ev] = io::mouse::parse(in); !!r)
            return io::console::mk_event(ev);
        // --- Else check for terminal resize signal

    }

    return {};
}
} // namespace cat
