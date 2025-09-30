//
// Created by oldlonecoder on 2025-09-29.
//

#include <catui/io/polling.h>

#include <cstring>
#include <functional>
#include <utility>
#include <sys/ioctl.h>

#include "catui/io/console.h"


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


namespace cat::io
{

pollin::pollin(int fd, i16 poll_bits, std::function<rem::code(pollin&)> call_back): callback(std::move(call_back))
{
    events[0].fd = fd;
    events[0].events = poll_bits;
    events[0].revents = 0;
}


pollin::pollin(int fd, i16 poll_bits, size_t buffer_size, std::function<rem::code(pollin&)> call_back): callback(std::move(call_back))
{
    events[0].fd = fd;
    events[0].events = poll_bits;
    events[0].revents = 0;

    buffer.resize(buffer_size,0);
}


pollin::pollin(pollfd&_events, size_t buffer_size, std::function<rem::code(pollin&)> call_back): callback(std::move(call_back))
{
    events[0] = _events;
    buffer.resize(buffer_size,0);
}


pollin::~pollin()
{
    buffer.clear();
}


rem::code pollin::operator()(int _timeout)
{
    auto log = sys::debug(); log << " _timeout: " << _timeout << log;

    auto n = ::poll(events, 1, _timeout);
    if (n == 0) return rem::code::timeout;
    if ((n == -1) || (events[0].revents & (POLLERR|POLLHUP)))
    {
        sys::error() << strerror(errno) << log;
        return rem::code::failed;
    }

    if (events[0].revents & POLLIN)
    {
        buffer.clear();

        if (auto iost = ::ioctl(events[0].fd, FIONREAD, &input_count); iost==-1)
        {
            sys::error() << strerror(errno) << log;
            buffer.clear();
            return rem::code::failed;
        }
        buffer.resize(input_count,0);
        auto sz = std::min(static_cast<size_t>(input_count), buffer.size());
        if (const auto r = ::read(events[0].fd, buffer.data(),sz); r == -1)
        {
            sys::error() << strerror(errno) << log;
            buffer.clear();
            return rem::code::failed;
        }
        //if (callback)
        //    return callback(*this);
        //else
        //{
            sys::write() << "bytes: [" << color::r << utxt::bytes(buffer) << "]" << log;
            return rem::code::accepted;
        //}
    }

    return rem::code::accepted;
}




} // namespace cat::io
