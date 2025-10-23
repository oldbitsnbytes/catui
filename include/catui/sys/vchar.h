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


// #include <catui/ui/geometry.h>
#include <catui/sys/border.h>
#include <catui/sys/rem.h>
#include <catui/sys/glyphes.h>
#include <catui/sys/geometry.h>

namespace cat::ui
{


struct vchar
{
    U32 D{0x8003A020};

    using string = std::vector<vchar>;
    using iterator = string::iterator;

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


   /**
    * @brief vchar::block is a block-dc on which objects draw. vchar::block is always relative to the console's absolute geometric offset.
    * The block's logical coordinates are visible or hidden. Each (child) object is clipped and confined to its top-level parent.
    * When rendering an object, its local coordinates are chained offsets from the chained parent objects to the top-level parent.
   */
    struct bloc
    {
        // --- CONFIGS AND INTERNAL DATA--------------
        color::pair     colors{};       ///< default and fallback colors.
        rectangle       geometry{};     ///< geometry
        vchar::string   dc{};           ///< (Display Context/Cell) Using one-dimension array of vchar as a two-dimension pad bloc.
        rem::code       state{rem::code::empty};
        vchar::iterator cursor{};      ///< iterator on the current character
        using shared = std::shared_ptr<vchar::bloc>;

        ~bloc();

        // --- Ui STUFF ------------------------------

        [[nodiscard]] int       width() const {return geometry.size.w;}
        [[nodiscard]] int       height() const {return geometry.size.h;}
        static shared           create(csz sz, color::pair a_colors);
        void                    clear(const rectangle& subarea={});
        rem::code               clear(ui::rectangle r, color::pair cp);
        rem::code               copy(vchar::bloc& PadDc, rectangle InnerArea);
        vchar::iterator         at(const cxy&offset={});
        rem::code               goto_xy(const cxy&offset={});
        void                    set_foreground_color(color::value aFg);
        void                    set_background_color(color::value aBg);
        void                    set_colors(color::pair Cp);


        rem::code               print(const std::string& str);
        //rem::code               print(const char* str);
        //rem::code               print(const std::string_view& str);
        //rem::code               print(const vchar& ch);



        [[nodiscard]] color::value            fg() const;
        [[nodiscard]] color::value            bg() const;
        rectangle               operator&(const rectangle &rhs) const;
        rectangle               operator/(const rectangle &rhs) const;
        vchar::iterator         operator[](cxy P);
        vchar::bloc&            operator*();

        bool         operator ++();    ///< ++geometry (++geometry.cursor.x)
        bool         operator ++(int); ///< geometry++ (++geometry.cursor.y)
        bool         operator --();    ///< --geometry (--geometry.cursor.x)
        bool         operator --(int); ///< geometry-- (++geometry.cursor.x)
        vchar::iterator set_position(cxy P);
        rem::code    move_to(cxy P);

        vchar::iterator peek(int l, int column=0);
        rem::code render(const rectangle& area);
        std::string render(cxy xy, int w);
    };


    vchar() = default;
    explicit vchar(U32 Ch);
    explicit vchar(vchar* C);
    vchar(vchar& C){D = C.D;}
    vchar(const vchar& C){D = C.D;}
    vchar(color::pair Cp);
    ~vchar() = default;
    vchar& set_fg(color::value aFg);
    vchar& set_bg(color::value aBg);
    vchar& set_attributes(U32 Ch);
    vchar& set_colors(const color::pair& Cp);
    vchar& operator=(U32 Ch);
    vchar& operator=(const vchar& Ch) = default;
    vchar& operator=(const U32* Ch);
    vchar& operator=(char Ch);
    vchar& operator=(int Ch) { D = Ch; return *this; };

    [[nodiscard]] std::string     get_utf_string() const;
    [[nodiscard]] color::value     foreground() const;
    [[nodiscard]] color::value    background() const;
    [[nodiscard]] color::pair     colors() const;
    [[nodiscard]] glyph::value    icon_index() const;
    [[nodiscard]] accent_fr::value  accent_index() const;
    [[nodiscard]] border::Index   border_index() const;
    [[nodiscard]] char            ascii() const;
    vchar&  operator*() { return *this; }
    [[nodiscard]] U16   attributes() const;
    vchar& operator <<(glyph::value gl);
    vchar& operator <<(accent_fr::value ac);
    vchar& operator << (border::Index fr);
    vchar& operator <<(color::pair cp);
    vchar& operator <<(vchar ch)
    {
        D = ch.D;
        return *this;
    }

    vchar&     operator <<(char ch);
    [[nodiscard]] std::string render_colors() const;
    explicit    operator std::string() const;
    [[nodiscard]] std::string details() const;

};
} // namespace OBB::Ui
