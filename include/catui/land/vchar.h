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


#include <RemSys/Ui/Geometry.h>
#include <RemSys/Ui/Border.h>
#include <RemSys/Sys.h>
#include <RemSys/Ui/Glyphes.h>


namespace cat::ui
{


struct vchar
{
    U32 D{0x8003A020};

    using String = std::vector<vchar>;
    using Iterator = String::iterator;

    static constexpr u32 CharMask  = 0x800000FF;
    static constexpr u32 FGMask    = 0x0000FF00;
    static constexpr u32 BGMask    = 0x00FF0000;
    static constexpr u32 CMask     = 0x00FFFF00;
    static constexpr u32 ColorsMask= 0x00FFFF00;
    static constexpr u32 AttrMask  = 0xFF000000;
    static constexpr u32 UtfMask   = 0xB10000FF;
    static constexpr u32 StyleMask = 0x0E000000;
    // ==============u===attributes==========================
    static constexpr u32 UGlyph    = 0x01000000;
    static constexpr u32 Underline = 0x02000000;
    static constexpr u32 Stroke    = 0x04000000;
    static constexpr u32 Blink     = 0x08000000;
    static constexpr u32 Accent    = 0x10000000;
    static constexpr u32 Frame     = 0x20000000;
    static constexpr u32 TRGB      = 0x40000000;
    /// This will make use of true-color RGB command instead of the re-routed terminal GUI colors profile
    static constexpr u32 ASCII     = 0x80000000;
    static constexpr u32 UTFBITS   = Accent | Frame | UGlyph;
    // ==============Bit Shift ============================
    static constexpr int FGShift = 0x08;
    static constexpr int BGShift = 0x10;
    static constexpr int ATShift = 0x18;


    struct Pad
    {
        // --- CONFIGS AND INTERNAL DATA--------------
        Color::Pair     Colors{};
        CRect           Geometry{};
        vchar::String    Dc{};           ///< Using one-dimension array of vchar as a two-dimension pad bloc.
        Rem::Code       State{Rem::Code::Empty};
        vchar::Iterator  Cursor{};
        using Shared = std::shared_ptr<vchar::Pad>;

        ~Pad();

        // --- Ui STUFF ------------------------------

        [[nodiscard]] int       Width() const {return Geometry.S.X;}
        [[nodiscard]] int       Height() const {return Geometry.S.Y;}
        static Shared           Create(CPoint Dxy, Color::Pair aColors);
        void                    Clear();
        Rem::Code               Copy(vchar::Pad& PadDc, CRect InnerArea);
        vchar::Iterator          Home();
        void                    SetForegroundColor(Color::Code aFg);
        void                    SetBackgroundColor(Color::Code aBg);
        void                    SetColors(Color::Pair Cp);
        Color::Code             Fg() const;
        Color::Code             Bg() const;
        CRect                   operator&(const CRect &rhs) const;
        CRect                   operator/(const CRect &rhs) const;
        vchar::Iterator          operator[](CPoint P);
        vchar::Pad&              operator*();

        bool         operator ++();    ///< ++geometry (++geometry.cursor.x)
        bool         operator ++(int); ///< geometry++ (++geometry.cursor.y)
        bool         operator --();    ///< --geometry (--geometry.cursor.x)
        bool         operator --(int); ///< geometry-- (++geometry.cursor.x)
        vchar::Iterator SetPosition(CPoint P);
    };


    vchar() = default;
    explicit vchar(U32 Ch);
    explicit vchar(vchar* C);
    vchar(vchar& C){D = C.D;}
    vchar(const vchar& C){D = C.D;}
    vchar(Color::Pair Cp);
    ~vchar() = default;
    vchar& SetFg(Color::Code aFg);
    vchar& SetBg(Color::Code aBg);
    vchar& SetAttributes(U32 Ch);
    //vchar& set_colors(color::pair&&Ch);
    // vchar& ResetAttributes(vchar::value_type bits_);
    vchar& SetColors(const Color::Pair& Cp);
    vchar& operator=(U32 Ch);
    vchar& operator=(const vchar& Ch) = default;
    vchar& operator=(const U32* Ch);
    vchar& operator=(char Ch);
    vchar& operator=(int Ch)
    {
        D = Ch;
        return *this;
    };

    [[nodiscard]] std::string     GetUtfString() const;
    [[nodiscard]] Color::Code     Foreground() const;
    [[nodiscard]] Color::Code     Background() const;
    [[nodiscard]] Color::Pair     Colors() const;
    [[nodiscard]] Glyph::Type     IconIndex() const;
    [[nodiscard]] AccentFr::Type  AccentIndex() const;
    [[nodiscard]] Border::Index   BorderIndex() const;
    [[nodiscard]] char            Ascii() const;
    vchar&  operator*() { return *this; }
    [[nodiscard]] U16   Attributes() const;
    vchar& operator <<(Glyph::Type gl);
    vchar& operator <<(AccentFr::Type ac);
    vchar& operator << (Border::Index fr);
    vchar& operator <<(Color::Pair Cp);
    vchar& operator <<(vchar Ch)
    {
        D = Ch.D;
        return *this;
    }
    static std::string RenderLine(vchar::Iterator _It, std::size_t aCount);

    vchar&     operator <<(char Ch);
    [[nodiscard]] std::string RenderColors() const;
    explicit    operator std::string() const;
    [[nodiscard]] std::string Details() const;

};
} // namespace OBB::Ui
