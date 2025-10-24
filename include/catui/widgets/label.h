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

#include <catui/widgets/object.h>


namespace cat::ui
{
class CATUI_LIB label : public object
{
    CLASSNAME_DERIVED(label)
    std::string _text{};
public:

    label();
    ~label() override;

    explicit label(std::string lbl_text);
    label(object*  parent_object, std::string lbl_text);
    void      draw() override;
    rem::code update(ui::rectangle rect) override;
    rem::code resize(ui::rectangle rect) override;
};


} // namespace cat::ui
