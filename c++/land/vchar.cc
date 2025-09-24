
#include <RemSys/Ui/Char.h>

namespace Ui
{


#define _eol_ Color::Pair(Color::R, Color::R)()

//using Ui::Int;

[[maybe_unused]] vchar::vchar(U32 Ch) : D(Ch){}

vchar::vchar(vchar* C): D(C->D){}

vchar::vchar(Color::Pair cc)
{
    SetColors(cc);
    D |= ASCII | 0x20&0xFF;
}


///
/// @param fg forground color code.
/// @return ref to self.
vchar &vchar::SetFg(Color::Code fg) { D = D & ~FGMask | static_cast<U8>(fg) << FGShift; return *this; }

vchar &vchar::SetBg(Color::Code bg) { D = D & ~BGMask | static_cast<U8>(bg) << BGShift; return *this; }
[[maybe_unused]] vchar &vchar::SetAttributes(U32 ch) { D = (D & ~AttrMask) | ch; return *this; }
//[[maybe_unused]] vchar &vchar::set_colors(Color::Pair &&Ch) { return set_fg(Ch.fg).set_bg(Ch.bg); }

[[maybe_unused]] vchar &vchar::SetColors(const Color::Pair &CP)
{
    D = D & ~ColorsMask | static_cast<U8>(CP.Fg) << FGShift | static_cast<U8>(CP.Bg) << BGShift;
    return *this;
}

vchar &vchar::operator=(U32 Ch) { D = Ch; return *this; }
vchar &vchar::operator=(const U32* Ch) { D = *Ch; return *this; }



std::string vchar::GetUtfString() const
{
    if(D & UTFBITS)
    {
        switch(D & UTFBITS)
        {
        case UGlyph:
            return  Glyph::Data[IconIndex()];
        case Accent:
            return  AccentFr::Data[AccentIndex()];
        case Frame:
            return Border()[BorderIndex()];
        default: break;
            //throw //sys::exception() [//sys::fatal() << " Memory corruption error into vchar data!"];
        }
    }
    std::string s;
    s += Ascii();
    return s;
}


/**
 *
 */
vchar &vchar::operator=(char Ch)
{
    D = D & ~(CharMask|UGlyph|Accent|Frame) | D & (CMask|Underline|Stroke|Blink|TRGB)  | ASCII | Ch & 0xff;
    return *this;
}

Color::Code vchar::Foreground() const { return static_cast<Color::Code>((D & FGMask) >> FGShift); }
Color::Code vchar::Background() const { return static_cast<Color::Code>((D & BGMask) >> BGShift); }
[[maybe_unused]] Color::Pair vchar::Colors() const { return {Foreground(),Background()}; }

[[maybe_unused]] Glyph::Type vchar::IconIndex() const
{
    if (!(D & UGlyph))
        throw Sys::Exception() [ Sys::Except() << Rem::Code::Rejected << "attempt to use this vchar cell as a glyph which is not!"];

    auto Ic = D & CharMask;
    if (Ic > Glyph::book)
        throw Sys::Exception()[Sys::Except() <<  Rem::Code::Oob << ':' << Ic];
    return  Ic;
}


[[maybe_unused]] AccentFr::Type vchar::AccentIndex() const
{
    auto AID = D & CharMask;
    if (AID > AccentFr::Ucirc)
        throw Sys::Exception()[Sys::Fatal()  << Rem::Code::Oob << ':' << AID];

    return static_cast<AccentFr::Type>(AID);
}




Border::Index vchar::BorderIndex() const
{
    auto c = D & 0xff;
    if(c > 11)
        throw Sys::Exception() [Sys::Except() << Rem::Code::Oob  << " invalid frame index: " << Color::Red4 << c];

    return static_cast<Border::Index>(D & 0xFF);
}

char vchar::Ascii() const
{ return static_cast<char>(D & 0xff); }


/**
 *
 */
[[maybe_unused]] U16  vchar::Attributes() const
{ return (D & AttrMask) >> ATShift; }

vchar &vchar::operator<<(Glyph::Type gl)
{ D = (D & ~(UtfMask|CharMask))  | (D&ColorsMask)|UGlyph | (gl&0xFF); return *this; }

vchar &vchar::operator<<(AccentFr::Type ac)
{ D = (D & ~(AttrMask|CharMask)) | (D & (Underline|Stroke|Blink|ColorsMask)) | Accent | ac; return *this; }

vchar& vchar::operator<<(Border::Index fr)
{ D = (D & ~(UtfMask|CharMask))  | (D&ColorsMask)|(fr&0xFF) | Frame; return *this; }

vchar& vchar::operator<<(Color::Pair cp)
{ D = (D & ~ColorsMask)          | static_cast<U8>(cp.Fg) << FGShift | static_cast<U8>(cp.Bg) << BGShift; return *this; }

vchar& vchar::operator<<(char Ch)
{ D = (D & ~(UTFBITS|CharMask))  | (D & (Underline|Stroke|Blink|ColorsMask)) | ASCII | (Ch & 0xff); return *this; }


[[maybe_unused]] std::string vchar::RenderColors() const
{
    std::string str;
    str += Color::RenderRGB({Background(),Foreground()});
    return str;
}

vchar::operator std::string() const { return Details(); }



// std::string vchar::render_line(const vchar::string& _string)
// {
//     return "vchar::render_line(const vchar::string& _string) is not implemented";
// }



//////////////////////////////////////////////////////////////////////////////
/// \brief vchar::render_line
/// \param _it
/// \param count
/// \return string pad of the ansi codes and text
///
std::string vchar::RenderLine(vchar::Iterator _it, std::size_t count)
{
    Color::Pair current_colors = _it->Colors();
    auto l = Sys::Debug(1); l << "iterator details:" << _it->Details() << l;
    std::string _o = current_colors();
    std::cout << _o;
    auto c = _it;
    for(int x =0; x< count; x++)
    {
        vchar ch = *c++;

        auto  [fg, bg] = ch.Colors();
        if(current_colors.Bg != bg)
        {
            current_colors.Bg = bg;
            _o += Color::RenderBackgroundRGB(current_colors.Bg);
        }
        if(current_colors.Fg != fg)
        {
            current_colors.Fg = fg;
            _o += Color::RenderRGB(current_colors.Fg);
        }
        if(ch.D & UTFBITS)
        {
            if(ch.D & Frame)
                _o += Border()[ch.BorderIndex()];
            else
                if(ch.D & Accent)
                    _o += AccentFr::Data[ch.AccentIndex()];
                else
                    if(ch.D & UGlyph)
                    {
                        auto w = Glyph::Data[ch.IconIndex()];
                        _o += w;
                        _o += "\033[D";
                        l = Sys::Debug(1);
                        l << "sizeof " << Color::Yellow << w << Color::R << "=" << std::strlen(w) << l;
                    }
        }
        else
            _o += ch.Ascii();
    }
    _o += _eol_;
    return _o;
}




std::string vchar::Details() const
{

    CString infos;
    CString utf_info{};
    if(D & UTFBITS)
    {
        switch(D & UTFBITS)
        {
        case UGlyph:
            utf_info << "icon index:" << IconIndex();
            break;
        case Accent:
            utf_info << "accent (fr) index:" << AccentIndex();
            break;
        case Frame:
            utf_info << "frame index:" << BorderIndex();
            break;
        default:break;
            //throw rem::exception() [rem::fatal() << " Memory corruption into screen::vchar data!"];
        }
    }
    else
        utf_info << Ascii();
    infos << "| foreground color:" << Foreground() << Color::Name(Foreground()) << Color::R << "| background color:" << Background() << Color::Name(Background()) << Color::R;
    infos << " char:['" << Colors() << utf_info() << Color::R <<  "']";
    if(D & Underline) infos << "|Underline";
    if(D & Stroke) infos << "|Stroke";
    if(D & Blink) infos << "|Blink";

    return infos();
}




} // namespace OBB::Ui
