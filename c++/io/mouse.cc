
////////////////////////////////////////////////////////////////////////////////////////////
//   copyright (c) ...,2025,... by serge lussier
//   serge.lussier@oldbitsnbytes.club / lussier.serge@gmail.com
//   ----------------------------------------------------------------------------------
//   unless otherwise specified, all codes and files in this project is written
//   by the author and owned by the author (serge lussier), unless otherwise specified.
//   ----------------------------------------------------------------------------------
//   copyrights from authors other than serge lussier also apply here.
//   open source free licences also apply to the code from the author (serge lussier)
//   ----------------------------------------------------------------------------------
//   usual gnu free gpl-1,2, mit... or whatever -  apply to this project.
//   ----------------------------------------------------------------------------------
//   note : all source code that i am the only author, i reserve for myself, the rights to
//   make it to restricted private license.
////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------

#include <catui/io/mouse.h>


namespace cat::io
{

/////////////////////////////////////////////////////////////////////////
/// \brief mouse::mev
///
mouse mouse::smev{};


mouse::mouse(const mouse& amouse)
{
    state = amouse.state;
    button = amouse.button;
    dxy = amouse.dxy;
    pos = amouse.pos;
    pressed = amouse.pressed;

}


mouse::mouse(mouse&& amouse) noexcept
{
    state = amouse.state;
    button = amouse.button;
    dxy = amouse.dxy;
    pos = amouse.pos;
    pressed = amouse.pressed;
}


mouse& mouse::operator=(mouse&&amouse) noexcept
{
    state = amouse.state;
    button = amouse.button;
    dxy = amouse.dxy;
    pos = amouse.pos;
    pressed = amouse.pressed;
    return *this;
}


mouse &mouse::operator=(const mouse &cpy)
{
    pos = cpy.pos;
    dxy = cpy.dxy;
    button = cpy.button;
    state = cpy.state;
    pressed = cpy.pressed;
    return *this;
}




glyph::value direction_arrows[3][3]={
    {glyph::arrow_up_left, glyph::arrow_up,   glyph::arrow_up_right},
    {glyph::arrow_left,    glyph::stop,       glyph::arrowright},
    {glyph::arrow_down_left, glyph::arrow_down,   glyph::arrow_down_right}
};

// cxy indexes[3][3]={
//     {{-1,-1},{0,-1},{1,-1}},
//     {{-1, 0},{0, 0},{1, 0}},
//     {{-1, 1},{0, 1},{1, 1}}
// };


///////////////////////////////////////////////////////////////////
/// \brief mouse::parse
/// \param _fd
/// \return
/// \note requires that the first byte in _fd must be 0x1b and consumed.
///
std::pair<rem::code,mouse>  mouse::parse(pollin &_fd)
{
    auto byte = _fd.buffer.begin();
    u8 b{0};
    int arg{0};
    std::vector<int> args{};

    if(b = *byte++; b != 27){
        auto l = sys::error(); l << rem::code::expected << color::r << " escape start sequence - got '" << color::hotpink4 << static_cast<int>(b) << color::r << " instead." << l;
        return {rem::code::rejected,{}};
    }
    b = *byte++;

    if(b != '['){
        auto l = sys::error(); l << rem::code::expected << color::r << " csi sequence - got '" << color::hotpink4 << static_cast<int>(b) << color::r << " instead." << l;
        return {rem::code::rejected,{}};
    }

    do{
        b = *byte++;
        //l << "next:['" << color::yellow << (int)b << color::z << "']" << l;
        if(b == '<'){
            //l << "altered [ ignored as of now ]" << l;
            //...
            continue;
        }

        if(std::isdigit(b)){
            arg *=10; // shift 10'th slide
            arg += b - '0';
            continue;
        }

        if(b ==';'){
            args.push_back(arg);
            arg = 0;
            continue;
        }

        // csi is terminated by a character in the range 0x40–0x7e
        // (ascii @a–z[\]^_`a–z{|}~),
        // note: i don't remember why we exclude '<'
        // to handle f1-f4, we exclude '['.
        if ((b >= '@') && (b <= '~') && (b != '<') && (b != '[')){
            args.push_back(arg);
            //sys::status() << "end csi sequence on '" << color::yellow << (int)b << color::z << "' :\n";
            switch(b){
                case 'M' :
                {
                    //auto l = sys::debug(); l << "end of sequence :'" << color::yellow << (char)b << color::r << "' args = [" << color::hotpink4 << tux::string::bytes(args) << color::r << "]" << l;
                    if (auto [r,mev] = parse(true,args); r == rem::code::ready)
                    {
                        _fd.buffer.clear();
                        return {rem::code::ready, mev};
                    }
                    return {rem::code::rejected,{}};
                }
                case 'm':
                {
                    //auto l = sys::debug(); l << "end of sequence :'" << color::yellow << (char)b << color::r << "' args = [" << color::hotpink4 << tux::string::bytes(args) << color::r << "]" << l;
                    if (auto [r,mev] = parse(false,args); r == rem::code::ready)
                    {
                        _fd.buffer.clear();
                        return {rem::code::ready, mev};
                    }
                    return {rem::code::rejected,{}};
                }
                case 'r':
                    sys::warning() <<" r :caret reports are unhandled from here - ignored" << rem::fn::eol;
                    break;
                default:
                    sys::error() << " unhandled csi sequence. " << rem::fn::eol;
                    break;
            }
            return {rem::code::rejected,{}};
        }

    }while( byte != _fd.buffer.end());
    return {rem::code::rejected,{}};
}

mouse::operator bool()
{
    return true;
}


std::pair<rem::code,mouse>  mouse::parse(bool bpressed, std::vector<int> args_)
{


    // pressed 'flag' ignored. relying on the xterm button and meta state byte which reports buttons on the lasts two bits:
    auto l = sys::debug();
    l << "parsing sequence : " << color::lightskyblue4 << args_.size() << color::r << " arguments [" << color::yellow << cat::string::bytes(args_) << "]" << l;
    mouse mev{};
    static mouse prev_mev{};
    if (args_.size() != 3){
        //sys::error() << " missing or extra arguments : expected 3, got " << color::yellow << args_.size() << //sys::eol;
        return {rem::code::rejected,{}};
    }

    //////////////////////////////////////////////////////////////////////
    /// assign the current buttons state, adjust the button event by the previous mouse data
    l = sys::status(); l << "button: " << (args_[0] & 3) << l;
    mev.button.left   = (args_[0] & 3) == 0 ? 1 :0;
    mev.button.mid    = (args_[0] & 3) == 1 ? 1 :0;
    mev.button.right  = (args_[0] & 3) == 2 ? 1 :0;
    if((args_[0] & 3)==3){
        sys::debug() << "no button pressed" << sys::eol;

        mev.button = {0};
    }
    ///@todo handle the other buttons...
    /// ...

    mev.state.shift     = (args_[0] & 4   ) != 0;
    mev.state.alt       = (args_[0] & 8   ) != 0;
    mev.state.win       = (args_[0] & 0x10) != 0;
    mev.pressed = bpressed;
    // subtract 1 from the coords. because the terminal starts at 1,1 and our ui system starts 0,0
    mev.pos.x = args_[1] - 1; //l << " x coord: " << color::yellow << mev.pos.x << color::r << "|" << args_[1] << l;
    mev.pos.y = args_[2] - 1; //l << " y coord: " << color::yellow << mev.pos.y << color::r << "|" << args_[2] << l;
    mev.dxy = mev.pos - prev_mev.pos;
    prev_mev.pos = mev.pos;
    //mev = mev & prev_mev;

    return {rem::code::ready,mev};
}
//if(dxy.x < 0) dir << glyph::arrow_left;
// else if(dxy.x > 0) dir << glyph::data[glyph::arrowright];
// else if(dxy.y < 0) dir << glyph::data[glyph::arrow_up];
// else if(dxy.y > 0) dir << glyph::data[glyph::arrow_down];
// else
//     dir << glyph::data[glyph::big_dot];


/////////////////////////////////////////////////////////////////////
/// \brief mouse::get_direction_arrow
///    just for fun when "stringify" the mouse states in a string: obtain the arrow glyph to illuxtrate the direction of the mouse move...lol
/// \param dxy
/// \return
///
std::string mouse::direction_arrow(ui::cxy dxy)
{
    cat::string arrow{};
    bool m[3][3]={
        {dxy.x < 0 && dxy.y < 0,  dxy.x == 0 && dxy.y < 0,  dxy.x > 0 && dxy.y < 0},
        {dxy.x < 0 && dxy.y == 0, dxy.x == 0 && dxy.y == 0, dxy.x > 0 && dxy.y == 0},
        {dxy.x < 0 && dxy.y > 0,  dxy.x == 0 && dxy.y > 0,  dxy.x > 0 && dxy.y > 0}
    };
    // there can be only one true value:
    for(int y = 0; y < 3; y++)
        for(int x=0; x < 3; x++)
            if(m[y][x]){
                arrow << direction_arrows[y][x];
                return arrow();
            }
    return " ";
}

//////////////////////////////////////////////////////////////////////
/// \brief mouse::operator () - put current state in a std::string.
/// \return std::string representing current mouse state values.
///
std::string mouse::operator()() const
{
    cat::string text{};
    cat::string dir{};
    text << "["
         << color::orangered1 << std::format("{:>3d}", pos.x)
         << color::reset << ','
         << color::orangered1 << std::format("{:<3d}", pos.y)
         << color::reset << "]";
    if(button.left)
        text << color::lime << (pressed ? 'L' : 'l') << color::r;
    else
        text << "l";
    text << '|';
    if(button.mid)
        text << color::yellow << (pressed ? 'M' : 'm') << color::r;
    else
        text << "m";
    text << '|';
    if(button.right)
        text << color::hotpink4 << (pressed ? 'R' : 'r') << color::r;
    else
        text << "r";
    text << '|'
         << (dxy != ui::cxy{0,0}          ? color::yellow : color::r) << direction_arrow(dxy)
         << color::reset << "["
         << color::orangered1 << std::format("{:>3d}",dxy.x)
         << color::reset << ','
         << color::orangered1 << std::format("{:<3d}",dxy.y) << color::r << "]";

    return text();
}

////////////////////////////////////////////////////////////////////////
/// \brief mouse::operator &
/// \param mev
/// \return
/// \note disabled. will be removed.
mouse& mouse::operator &(const mouse &mev)
{

    return *this;
}

} // namespace cat::io
