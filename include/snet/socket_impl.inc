/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#include <cassert>
#include <utility>

namespace snet {

    inline socket::socket(sock_t d)
        : _sock(d)
    {}

    inline socket::socket(socket&& s)
    {
        assert( _sock == invalid_socket );
        std::swap(_sock, s._sock);
    }

    inline socket& socket::operator=(socket&& s)
    {
        std::swap(_sock, s._sock);
        return *this;
    }

    inline socket::~socket()
    {
        close();
    }

    inline socket socket::create(int family, int socktype, int protocol)
    {
        return ::socket(family, socktype, protocol);
    }

} // namespace snet

// include platform-depended code
#if defined( _WIN32 )
#   include "socket_impl_win.inc"
#else /* defined( _WIN32 ) */
#   include "socket_impl_posix.inc"
#endif /* defined( _WIN32 ) */
