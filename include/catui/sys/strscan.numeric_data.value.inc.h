//
// Created by oldlonecoder on 25-04-26.
//

/******************************************************************************************
*   Copyright (C) ...,2024,... by Serge Lussier                                          *
 *   serge.Lussier@oldlonecoder.club                                                      *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (Serge Lussier).                                                       *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (Serge Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... apply to this project.                                *
 ******************************************************************************************/


#pragma once
#include <cmath>
#include <catui/sys/strscan.h>


namespace cat
{
// Testing 
template<typename T> T strscan::numeric_data::value()
{
    if constexpr ((std::is_same_v<T, bool>)
        || (std::is_same_v<T, i8>)
        || (std::is_same_v<T, i16>)
        || (std::is_same_v<T, i32>)
        || (std::is_same_v<T, i64>)
        || (std::is_same_v<T, u8>)
        || (std::is_same_v<T, u16>)
        || (std::is_same_v<T, u32>)
        || (std::is_same_v<T, u64>)
        || (std::is_same_v<T, int>))
    {
        return static_cast<T>( std::round(_value));
    }

    return static_cast<T>(_value);
}



}
