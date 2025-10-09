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


class CATUI_LIB element : public object
{
    CLASSNAME_DERIVED(element)
public:
    element();
    element(element* parent_element, const std::string& a_id, u16 cls_bits);

    ~element() override;

    auto dc() -> vchar::bloc::shared { return _dc; }
    virtual rem::code draw();
    rem::code update(rectangle r={});
    rem::code set_geometry(const rectangle& a_geometry);
    rem::code set_theme(const std::string& a_theme_name);
    [[nodiscard]] rectangle geometry() const { return _rect; }
    [[nodiscard]] int   width() const { return _rect.width(); }
    [[nodiscard]] int   height() const { return _rect.height(); }
    void      set_padding(padding a_padding);
    void      set_margin(margin a_margin);
    void      set_anchor(anchor::value a_anchor);
    void      set_status(estatus::value a_status);
    void      set_component(component::value a_component);
    void      set_type(e_type::value a_type);



protected:
    virtual rem::code   setup_ui(const std::string& _theme_name);
    vchar::bloc::shared  _dc{nullptr};
    rectangle               _rect{};
    rectangle               _dirty_area{};
    color::db::item     _palette{};
    color::pair         _theme_colors{};
    std::string         _theme_id{"default"};
    padding             _padding{};
    margin              _margin{};
    anchor::value       _anchor{anchor::none};
    estatus::value      _status{estatus::normal};
    component::value    _component{component::none};
    e_type::value       _type{e_type::none};

    rem::code           _alloc_dc(csz wxh);


};

} // namespace cat::ui

//#endif //CATUI_ELEMENT_H
