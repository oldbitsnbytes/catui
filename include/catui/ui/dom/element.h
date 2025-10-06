//
// Created by Serge Lussier on 2025-10-02.
//

//#ifndef CATUI_ELEMENT_H
//#define CATUI_ELEMENT_H
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
#include <catui/ui/vchar.h>
#include <catui/ui/dom/object.h>

namespace cat::ui
{
namespace e_type
{
    using value = u32;
    static constexpr value none      = 0x0000;
    static constexpr value floating  = 0x0001;
    static constexpr value dialog    = 0x0002;
    static constexpr value menu      = 0x0004;
    static constexpr value toolbar   = 0x0008;
    static constexpr value toplevel  = 0x0010;
}

namespace component
{
using value = u32;
static constexpr value none      = 0x0000;
static constexpr value frame     = 0x0001;
static constexpr value caption   = 0x0002;
static constexpr value statusbar = 0x0004;
static constexpr value input     = 0x0008;
static constexpr value button    = 0x0010;
static constexpr value scroll    = 0x0020;
static constexpr value suffix_glyph    = 0x0040;
static constexpr value prefix_glyph    = 0x0080;
static constexpr value menubar       = 0x0100;
static constexpr value menu          = 0x0200;
//...
}


namespace buttons
{
using value = u32;
static constexpr value button_none   = 0x0000;
static constexpr value button_cancel = 0x0010;
static constexpr value button_ok     = 0x0020;
static constexpr value button_yes    = 0x0040;
static constexpr value button_no     = 0x0080;
static constexpr value button_help   = 0x0100;
static constexpr value button_close  = 0x0200;
static constexpr value button_save   = 0x0400;
static constexpr value button_load   = 0x0800;
static constexpr value button_new    = 0x1000;
static constexpr value button_open   = 0x2000;
static constexpr value button_edit   = 0x4000;
static constexpr value button_delete = 0x8000;
static constexpr value button_run    = 0x10000;
static constexpr value button_stop   = 0x20000;
static constexpr value button_pause  = 0x40000;
static constexpr value button_resume = 0x80000;
static constexpr value button_done   = 0x100000;
static constexpr value button_abort  = 0x200000;
static constexpr value button_retry  = 0x400000;
static constexpr value button_ignore = 0x800000;
static constexpr value button_quit   = 0x1000000;
static constexpr value button_about  = 0x4000000;
static constexpr value button_exit   = 0x8000000;
static constexpr value button_reset  = 0x10000000;
static constexpr value button_apply  = 0x20000000;

//...

}

namespace estatus
{
using value = u32;
static constexpr value none      = 0x0000;
static constexpr value normal    = 0x0001;
static constexpr value warning   = 0x0002;
static constexpr value error     = 0x0004;
static constexpr value success   = 0x0008;
static constexpr value focussed  = 0x0010;
static constexpr value disabled  = 0x0020;
static constexpr value selected  = 0x0040;
static constexpr value checked   = 0x0080;
static constexpr value unchecked = 0x0100;
static constexpr value inactive  = 0x0200;
static constexpr value active    = 0x0400;
static constexpr value hidden    = 0x0800;
static constexpr value visible   = 0x1000;
static constexpr value locked    = 0x2000;
static constexpr value unlocked  = 0x4000;

}




namespace anchor
{
using value = U16;
static constexpr anchor::value none     = 0x0000; ///< free fixed xy placement
static constexpr anchor::value fixed    = 0x0001; ///< free fixed xy placement
static constexpr anchor::value width    = 0x0002; ///< fits the entire width size
static constexpr anchor::value height   = 0x0004; ///< fits the entire height size
static constexpr anchor::value frame    = 0x0008; ///< overlaps if wh size > 1, or sits on the frame.
static constexpr anchor::value right    = 0x0010;
static constexpr anchor::value left     = 0x0020;
static constexpr anchor::value top      = 0x0040;
static constexpr anchor::value bottom   = 0x0080;
static constexpr anchor::value center   = 0x0100; ///< both fit_h&vcenter ...
static constexpr anchor::value hcenter  = 0x0200;
static constexpr anchor::value vcenter  = 0x0400;

//...
}


/*!
 *  Spacing within.
 */
struct padding
{
    i8 top{0};
    i8 left{0};
    i8 bottom{0};
    i8 right{0};
};


/**
 *  \brief Spacing from parent.
 */
struct margin
{
    i8 top{0};
    i8 left{0};
    i8 bottom{0};
    i8 right{0};
};



class CATUI_LIB element : public object
{
    CLASSNAME_DERIVED(element)
public:
    element();
    element(element* parent_element, const std::string& a_id, u16 cls_bits);

    ~element() override;

    auto dc() -> vchar::pad::shared { return _dc; }
    virtual rem::code draw();
    rem::code update(crect r={});
    rem::code set_geometry(const crect& a_geometry);
    rem::code set_theme(const std::string& a_theme_name);
    [[nodiscard]] crect geometry() const { return _rect; }
    [[nodiscard]] int   width() const { return _rect.Width(); }
    [[nodiscard]] int   height() const { return _rect.Height(); }
    void      set_padding(padding a_padding);
    void      set_margin(margin a_margin);
    void      set_anchor(anchor::value a_anchor);
    void      set_status(estatus::value a_status);
    void      set_component(component::value a_component);
    void      set_type(e_type::value a_type);



protected:
    virtual rem::code   setup_ui(const std::string& _theme_name);
    vchar::pad::shared  _dc{nullptr};
    crect               _rect{};
    crect               _dirty_area{};
    color::db::item     _palette{};
    color::pair         _theme_colors{};
    std::string         _theme_id{"default"};
    padding             _padding{};
    margin              _margin{};
    anchor::value       _anchor{anchor::none};
    estatus::value      _status{estatus::none};
    component::value    _component{component::none};
    e_type::value       _type{e_type::none};

    rem::code           _alloc_dc(cpoint wxh);


};

} // namespace cat::ui

//#endif //CATUI_ELEMENT_H
