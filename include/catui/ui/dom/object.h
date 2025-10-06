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

namespace cat
{
class CATUI_LIB object
{
    CLASSNAME_START(object)

    std::string _id{"object"};
    object* _parent{nullptr};

public:
    using list = std::vector<object*>;
    using iterator = list::iterator;
    object();
    virtual ~object();

    object(std::string  a_id);
    object(object* parent_object, std::string  a_id);

    object& operator = (object&& rhs) noexcept;
    object& operator = (const object& rhs);

    object* parent() { return _parent; }
    [[nodiscard]] object::iterator child(const std::string& id);
    // object* child(int index);
    object::iterator child(object* child);
    [[nodiscard]] const std::string& id() const { return _id; }

protected:
    object::list _children{};


    template<typename T> T* dom_parent()
    {
        object* o = this;
        while (o->_parent)
        {
            T* p = dynamic_cast<T*>(o->_parent);
            if (p) return p;
        }
        return nullptr;
    }
};
} // cat

//#endif //CATUI_OBJECT_H
