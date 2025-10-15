
#include <catui/ui/vchar.h>
#include <iostream>

#include <catui/sys/sys.h>

namespace cat::ui
{


#define _eol_ color::pair(color::r, color::r)()

//using Ui::Int;

[[maybe_unused]] vchar::vchar(U32 Ch) : D(Ch){}

vchar::vchar(vchar* C): D(C->D){}

vchar::vchar(color::pair cc)
{
    set_colors(cc);
    D |= ASCII | 0x20&0xFF;
}


///
/// @param fg forground color code.
/// @return ref to self.
vchar &vchar::set_fg(color::value fg) { D = D & ~FGMask | static_cast<U8>(fg) << FGShift; return *this; }

vchar &vchar::set_bg(color::value bg) { D = D & ~BGMask | static_cast<U8>(bg) << BGShift; return *this; }
[[maybe_unused]] vchar &vchar::set_attributes(U32 ch) { D = (D & ~AttrMask) | ch; return *this; }
//[[maybe_unused]] vchar &vchar::set_colors(color::pair &&Ch) { return set_fg(Ch.fg).set_bg(Ch.bg); }

[[maybe_unused]] vchar &vchar::set_colors(const color::pair &cp)
{
    D = D & ~ColorsMask | static_cast<U8>(cp.fg) << FGShift | static_cast<U8>(cp.bg) << BGShift;
    return *this;
}

vchar &vchar::operator=(U32 ch) { D = ch; return *this; }
vchar &vchar::operator=(const U32* ch) { D = *ch; return *this; }



std::string vchar::get_utf_string() const
{
    if(D & UTFBITS)
    {
        switch(D & UTFBITS)
        {
        case UGlyph:
            return  glyph::data[icon_index()];
        case Accent:
            return  accent_fr::data[accent_index()];
        case Frame:
            return border()[border_index()];
        default: break;
            //throw //sys::exception() [//sys::fatal() << " Memory corruption error into vchar data!"];
        }
    }
    std::string s;
    s += ascii();
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

color::value vchar::foreground() const { return static_cast<color::value>((D & FGMask) >> FGShift); }
color::value vchar::background() const { return static_cast<color::value>((D & BGMask) >> BGShift); }
[[maybe_unused]] color::pair vchar::colors() const { return {foreground(),background()}; }

[[maybe_unused]] glyph::value vchar::icon_index() const
{
    if (!(D & UGlyph))
        ;//throw sys::exception() [ sys::except() << rem::code::rejected << "attempt to use this vchar cell as a glyph which is not!"];

    auto Ic = D & CharMask;
    if (Ic > glyph::book)
        ;//throw sys::exception()[sys::except() <<  rem::code::oob << ':' << Ic];
    return  Ic;
}


[[maybe_unused]] accent_fr::value vchar::accent_index() const
{
    auto AID = D & CharMask;
    if (AID > accent_fr::Ucirc)
        ;//throw sys::exception()[sys::fatal()  << rem::code::oob << ':' << AID];

    return static_cast<accent_fr::value>(AID);
}




border::Index vchar::border_index() const
{
    if((D & 0xff) > 11)
        ;//throw Sys::Exception() [Sys::Except() << Rem::Code::Oob  << " invalid frame index: " << color::Red4 << c];

    return static_cast<border::Index>(D & 0xFF);
}

char vchar::ascii() const
{ return static_cast<char>(D & 0xff); }


[[maybe_unused]] U16  vchar::attributes() const
{ return (D & AttrMask) >> ATShift; }

vchar &vchar::operator<<(glyph::value gl)
{ D = (D & ~(UtfMask|CharMask))  | (D&ColorsMask)|UGlyph | (gl&0xFF); return *this; }

vchar &vchar::operator<<(accent_fr::value ac)
{ D = (D & ~(AttrMask|CharMask)) | (D & (Underline|Stroke|Blink|ColorsMask)) | Accent | ac; return *this; }

vchar& vchar::operator<<(border::Index fr)
{ D = (D & ~(UtfMask|CharMask))  | (D&ColorsMask)|(fr&0xFF) | Frame; return *this; }

vchar& vchar::operator<<(color::pair cp)
{ D = (D & ~ColorsMask)          | static_cast<U8>(cp.fg) << FGShift | static_cast<U8>(cp.bg) << BGShift; return *this; }

vchar& vchar::operator<<(char ch)
{ D = (D & ~(UTFBITS|CharMask))  | (D | ASCII | (ch & 0xff)); return *this; }
// { D = (D & ~(UTFBITS|CharMask))  | (D & (Underline|Stroke|Blink|ColorsMask)) | ASCII | (ch & 0xff); return *this; }



[[maybe_unused]] std::string vchar::render_colors() const
{
    std::string str;
    str += color::render_rgb({background(),foreground()});
    return str;
}

vchar::operator std::string() const { return details(); }



std::string vchar::details() const
{

    cat::string infos;
    infos << color::white << infos.hex(D) << "{";
    cat::string utf_info{};
    if(D & UTFBITS)
    {
        switch(D & UTFBITS)
        {
        case UGlyph:
            utf_info << "icon index:" << icon_index();
            break;
        case Accent:
            utf_info << "accent (fr) index:" << accent_index();
            break;
        case Frame:
            utf_info << "frame index:" << border_index();
            break;
        default:break;
            //throw rem::exception() [rem::fatal() << " Memory corruption into screen::vchar data!"];
        }
    }
    else
        utf_info << ascii();
    infos << "| " << colors().name() << color::r;
    infos << " char:['" << colors() << utf_info() << color::r <<  "']";
    if(D & Underline) infos << "|Underline";
    if(D & Stroke) infos << "|Stroke";
    if(D & Blink) infos << "|Blink";
    infos << "}";
    return infos();
}




} // namespace OBB::Ui
