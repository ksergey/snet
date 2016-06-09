/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

// socket implementation for windows environment

namespace snet {

    inline bool socket::close()
    {
        if (valid()) {
            if (::closesocket(_sock) == 0) {
                _sock = invalid_socket;
                return true;
            }
        }
        return false;
    }

    inline bool socket::set_nonblock(bool flag)
    {
        u_long flags = flag;
        int rc = ::ioctlsocket(get(), FIONBIO, &flags);
        return rc == 0;
    }

    inline bool socket::set_cloexec(bool flag)
    {
        auto rc = SetHandleInformation(reinterpret_cast< HANDLE >(get()), HANDLE_FLAG_INHERIT, int(flag));
        return rc != 0;
    }

    inline ssize_t socket::send(const void* buf, size_t len)
    {
        auto rc = ::send(get(), buf, len, 0);
        return rc == SOCKET_ERROR ? -1 : rc;
    }

    inline ssize_t socket::sendto(const void* buf, size_t len,
        const sockaddr* dest_addr, socklen_t addrlen)
    {
        auto rc = ::sendto(get(), buf, len, 0, dest_addr, addrlen);
        return rc == SOCKET_ERROR ? -1 : rc;
    }

    inline ssize_t socket::recv(void* buf, size_t len)
    {
        auto rc = ::recv(get(), buf, len, 0);
        return rc == SOCKET_ERROR ? -1 : rc;
    }

    inline ssize_t socket::recvfrom(void* buf, size_t len,
        sockaddr* src_addr, socklen_t* addrlen)
    {
        auto rc = ::recvfrom(get(), buf, len, 0, src_addr, addrlen);
        return rc == SOCKET_ERROR ? -1 : rc;
    }

} // namespace snet
