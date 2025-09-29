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

#include <functional>
#include <sys/poll.h>
#include <catui/land/sys/sys.h>




namespace cat::io
{



struct CATUI_LIB pollin
{
    int timeout{-1};
    pollfd events[1]{};
    int revents{0};

    size_t max_bytes{1024};
    int    input_count{0};
    std::vector<byte> buffer{};

    std::function<rem::code(pollin&)> callback;

    pollin() = default;
    pollin(int fd, i16 poll_bits, std::function<rem::code(pollin&)> call_back);
    pollin(int fd, i16 poll_bits, size_t buffer_size, std::function<rem::code(pollin&)> call_back);
    pollin(pollfd& _events, size_t buffer_size, std::function<rem::code(pollin&)> call_back);
    ~pollin();

    rem::code operator()(int _timeout=-1);

};



} // namespace cat::io

//#endif //CATUI_POLL_H
