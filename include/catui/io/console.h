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

#include <catui/sys/sys.h>
#include <catui/io/polling.h>
#include <unistd.h>

#include <catui/io/kstroke.h>
#include <catui/io/mouse.h>

namespace cat::io::console
{
static constexpr auto set_caret_pos="\x1b[{};{}H";

static int ignore{0};

static constexpr u8 ST_SAVED         = 1;
static constexpr u8 ST_MOUSE_ENABLED = 2;
static constexpr u8 ST_ACTIVATED     = 4;
static constexpr u8 ST_RAW_SET       = 8;
static constexpr u8 ST_POLL_STARTED  = 0x10;
static constexpr u8 ST_POLL_CLOSED   = 0x20;
static constexpr u8 ST_CARET_ON      = 0x40;
inline bool  CONSOLE_RESIZE_FLAG{false};





static constexpr u8 USE_MOUSE               = 1;
static constexpr u8 REPORT_MOUSE_POSITION   = 2;
static constexpr u8 REPORT_MOUSE_BUTTONS    = 4;
static constexpr u8 USE_DOUBLE_BUFFER       = 8;    ///< Also tells console to save and clear the initial screen then restore it at exit.
static constexpr u8 AUTO_HIDE_CARET         = 0x10; ///< Hide the caret when not on keyboard input prompt.


enum class CaretShapes: u8
{
    Default,
    BlocBlink,
    BlockSteady,
    UnderBlink,
    UnderSteady,
    VBarBlink,
    VBarSteady
};


static constexpr auto LINE_WRAP                 = "7";
static constexpr auto CRS_SHAPE                 = "25";
static constexpr auto MOUSE_X10                 = "9 ";
static constexpr auto SET                       = 'h';
static constexpr auto RESET                     = 'l';
static constexpr auto MOUSE_VT200               = "\x1b[?1000";
static constexpr auto MOUSE_VT200_HL            = "\x1b[?1001";
static constexpr auto MOUSE_REPORT_BUTTONS      = "\x1b[?1002";
static constexpr auto MOUSE_REPORT_ANY          = "\x1b[?1003";
static constexpr auto MOUSE_UTF8                = "\x1b[?1005";
static constexpr auto MOUSE_SGR_EXT_MODE        = "\x1b[?1006";
static constexpr auto MOUSE_URXVT_MODE          = "\x1b[?1015";
static constexpr auto MOUSE_SGR_PIXEL_MODE      = "\x1b[?1016";
static constexpr auto ALTERNATE_SCREEN          = "\x1b[?1049";
static constexpr auto CSI                       = "\x1b[";
static constexpr auto CSI_BOLD                  = "\x1b[1m";
static constexpr auto CSI_UNDERLINE             = "\x1b[4m";
static constexpr auto CSI_REVERSE               = "\x1b[7m";
static constexpr auto CSI_STRIKETHROUGH         = "\x1b[35m";
static constexpr auto CSI_UNDERLINE_PREVIOUS    = "\x1b[90m";
static constexpr auto CSI_UNDERLINE_NEXT        = "\x1b[92m";
static constexpr auto CSI_UNDERLINE_INCREMENT   = "\x1b[93m";
static constexpr auto CSI_UNDERLINE_DECREMENT   = "\x1b[94m";






rem::code start();
void      caret_off();
void      caret_on();
void      clear();
void      clear_line();
void      clear_to_bottom();
void      clear_to_top();
void      clear_to_end_line();
void      clear_to_start_line();
void      move_cursor_down();
void      move_cursor_left();
void      move_cursor_right();
void      move_cursor_up();

rem::code get_geometry();
rem::code start_mouse();
rem::code stop_mouse();
rem::code end();
void save_screen();
void restore_screen();
ui::rectangle geometry();

cat::io::pollin& poll_fd();

struct CATUI_LIB mk_event
{
    union
    {
        kstroke k{};
        mouse   m;
    };

    enum type :u8
    {
        KEY_EVENT,
        MOUSE_EVENT,
        UNSET
    }event_type{mk_event::UNSET};

    mk_event(){};
    explicit mk_event(const kstroke& k);
    explicit mk_event(const mouse& m);
    ~mk_event();

    //mk_event& operator=(mk_event&&) noexcept = default;
    mk_event& operator=(const mk_event&);

    template<typename T> [[nodiscard]] bool is() const
    {
        if (std::is_same_v<T, kstroke> && event_type == mk_event::KEY_EVENT) return true;
        if (std::is_same_v<T, mouse> && event_type == mk_event::MOUSE_EVENT) return true;
        return false;
    }
};

} // namespace cat::io::console;

namespace cat
{



class CATUI_LIB conio
{

public:
    enum movfn : u8
    {
        up,
        down,
        left,
        right,
        eol
    };

    conio& operator << (const char* str);
    conio& operator << (color::value clr);
    conio& operator << (color::pair  clr);
    conio& operator << (rem::code c);
    conio& operator << (rem::type ty);
    conio& operator << (ui::cxy xy);
    conio& operator << (glyph::value f);
    conio& operator << (ui::vchar::bloc& ui_bloc);
    conio& operator << (ui::rectangle rect);
    conio& operator << (ui::border::Index idx);
    conio& operator << (conio::movfn mv);

    conio& operator >> (int& i);

    rem::code render(ui::vchar::bloc& ui_bloc, const ui::rectangle& local_area={});

    static io::console::mk_event wait();
    template<typename T> conio& operator << (T&& val)
    {
        cat::string s;
        s << std::forward<T>(val);
        std::cout << s();
        return *this;
    }

}inline con{};



// ...
// con << "Hello!\n";
// con >> a_number;
// con >> one_event;
// con >> mouse_event;
// con >> keystroke_event;
// ...etc


} // namespace cat::io


// .. .
// using con cat::io::con;
