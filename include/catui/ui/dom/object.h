//
// Created by Serge Lussier on 2025-10-02.
//

//#ifndef CATUI_OBJECT_H
//#define CATUI_OBJECT_H
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
#include <catui/ui/vchar.h>
namespace cat::dom
{

namespace type_enums
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

namespace dom_status_enums
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

class CATUI_LIB object
{
    CLASSNAME_START(object)

    std::string _id{"object"};


    #pragma region dom_element_private
    //----------------------------------------------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------------------------------------------
    #pragma endregion dom_element_private

public:

    using shared = std::shared_ptr<object>;
    using weak = std::weak_ptr<object>;

    using list = std::vector<object::shared>;
    using iterator = list::iterator;

    object();
    virtual ~object();

    object(std::string  a_id);
    object(const object::shared&parent_object, std::string  a_id);

    object& operator = (object&& rhs) noexcept;
    object& operator = (const object& rhs);

    object* parent() { return _parent.get(); }
    [[nodiscard]] object::iterator child(const std::string& id);
    // object* child(int index);
    object::iterator child(const object::shared& child);
    [[nodiscard]] const std::string& id() const { return _id; }
    object&  operator *() { return *this; }
    #pragma region public_dom_element
    //----------------------------------------------------------------------------------------------------------------------------

    rem::code set_theme(const std::string& theme_name);

    //object* operator ->() { return this; }
    ui::vchar::bloc::shared bloc_dc() { return _dc; }
    [[nodiscard]] ui::vchar::bloc& dc() const { return **_dc; }
    ui::vchar::iterator operator[](ui::cxy pos) const;
    rem::code set_geometry(const ui::rectangle& rect);

    template<typename T> object& write(const T& content);
    template<typename T> T* dom_parent();
    object&  dom_clear();
    object&  home();
    object&    operator << (const std::string& str);
    object&    operator << (const char* str);
    object&    operator << (const std::string_view& str);
    object&    operator << (const std::vector<std::string_view>& str);
    object&    operator << (const std::vector<std::string>& str);
    object&    operator << (const ui::rectangle& frame_dim);
    object&    operator << (color::pair clr);
    object&    operator << (color::value clr);
    object&    operator << (glyph::value f);
    object&    operator << (cat::string str);
    object&    operator << (cat::ui::cxy xy);
    object&    operator << (sys::fn f);
    object&    operator << (cat::ui::rectangle rect);
    object&    operator << (cat::ui::border::Index idx);


    void set_dom_status(dom_status_enums::value status);
    void set_dom_type(type_enums::value type);
    void set_dom_component(component::value component);
    void set_dom_anchor(anchor::value anchor);
    void set_dom_padding(padding padding);
    void set_dom_margin(margin margin);

    std::pair<std::string, dom_status_enums::value> dom_status() const;
    std::pair<std::string, type_enums::value> dom_type() const;
    std::pair<std::string, component::value> dom_component() const;
    std::pair<std::string, anchor::value> dom_anchor() const;
    padding& dom_padding();
    margin&  dom_margin();

    //----------------------------------------------------------------------------------------------------------------------------
    #pragma endregion public_dom_element

    struct canva
    {
        ui::vchar::bloc::shared dc{nullptr};
        ui::rectangle geometry{};
        ui::vchar::iterator cursor{};
        ui::vchar::iterator begin{};
        ui::vchar::iterator end{};
        ui::vchar::iterator home{};
        object::shared parent{nullptr};

        canva();
        canva(object::shared _parent, ui::rectangle _geometry={});

        ~canva();
        void clear();

        rem::code position(const ui::cxy& xy);

        
    };
protected:
    object::list _children{};

    #pragma region dom_element_protected
    //----------------------------------------------------------------------------------------------------------------------------

    //virtual rem::code   setup_ui(const std::string& _theme_name);
    ui::rectangle               _rect{};
    ui::rectangle               _dirty_area{};
    color::db::object_palette*  _palette{nullptr};
    color::pair                 _theme_colors{};
    std::string                 _theme_id{"default"};
    padding                     _padding{};
    margin                      _margin{};
    anchor::value               _anchor{anchor::none};
    dom_status_enums::value     _dom_status{dom_status_enums::normal};
    component::value            _component{component::none};
    type_enums::value           _dom_type{type_enums::none};


    rem::code               allocate_bloc_dc(ui::csz wxh);

    ui::vchar::bloc::shared _dc{nullptr};
    ui::rectangle           _geometry{};
    //ui::vchar::iterator     _home();
    //----------------------------------------------------------------------------------------------------------------------------
    #pragma endregion dom_element_protected

private:
    object::shared _parent{nullptr};
};
} // cat::dom

#include <catui/ui/dom/object-impl.h>
