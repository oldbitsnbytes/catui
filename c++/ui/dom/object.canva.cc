//
// Created by Serge Lussier on 2025-10-17.
//
#include <catui/ui/dom/object.h>




namespace cat::dom
{

object::canva::canva(object::shared _parent, ui::rectangle _geometry)
{
    parent = _parent;
    geometry = _geometry;
    colors= parent->_theme_colors;
}





}
