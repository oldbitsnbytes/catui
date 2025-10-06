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
#include <catui/io/console.h>
#include <catui/ui/dom/element.h>

namespace cat
{


class CATUI_LIB application
{
    CLASSNAME_START(application)
    cat::string::view_list _arguments{};

public:
    application();
    application(const std::string& app_name,cat::string::view_list&& arguments);
    virtual ~application();
    virtual rem::code setup();
    virtual rem::code run();
    virtual rem::code end();


};
} // cat

//#endif //CATUI_APPLICATION_H
