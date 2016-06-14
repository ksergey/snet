/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#include <snet/result.hpp>
#include <snet/exception.hpp>

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

    inline bool socket::set_tcpnodelay(bool flag)
    {
        // TODO: fix me (see set_option)
        int value = flag ? 1 : 0;
        return ::setsockopt(get(), IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value)) == 0;
    }

    inline bool socket::set_reuseaddr(bool flag)
    {
        // TODO: fix me (see set_option)
        int value = flag ? 1 : 0;
        return ::setsockopt(get(), SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) == 0;
    }

    inline socket socket::create(int family, int socktype, int protocol)
    {
        sock_t s = ::socket(family, socktype, protocol);
        if (s == invalid_socket) {
            throw exception("failed to create socket");
        }
        return s;
    }

    inline op_result socket::connect(const sockaddr* addr, socklen_t addrlen) noexcept
    {
        return ::connect(get(), addr, addrlen);
    }

    inline op_result socket::bind(const sockaddr* addr, socklen_t addrlen) noexcept
    {
        return ::bind(get(), addr, addrlen);
    }

    inline op_result socket::listen(int backlog) noexcept
    {
        return ::listen(get(), backlog);
    }

    inline accept_result socket::accept(sockaddr* addr, socklen_t* addrlen)
    {
        return ::accept(get(), addr, addrlen);
    }

} // namespace snet

// include platform-depended code
#if defined( _WIN32 )
#   include "socket_impl_win.inc"
#else /* defined( _WIN32 ) */
#   include "socket_impl_posix.inc"
#endif /* defined( _WIN32 ) */
