/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

// socket implementation for posix environment

namespace snet {

    inline bool socket::close()
    {
        if (valid()) {
            if (::close(_sock) == 0) {
                _sock = invalid_socket;
                return true;
            }
        }
        return false;
    }

    inline bool socket::set_nonblock(bool flag)
    {
        int flags = ::fcntl(get(), F_GETFL, 0);
        if (flags == -1) {
            flags = 0;
        }

        if (flag) {
            flags |= O_NONBLOCK;
        } else {
            flags &= ~int(O_NONBLOCK);
        }

        int rc = ::fcntl(get(), F_SETFL, flags);
        return rc == 0;
    }

    inline bool socket::set_cloexec(bool flag)
    {
        int flags = ::fcntl(get(), F_GETFL, 0);
        if (flags == -1) {
            flags = 0;
        }

        if (flag) {
            flags |= FD_CLOEXEC;
        } else {
            flags &= ~int(FD_CLOEXEC);
        }

        int rc = ::fcntl(get(), F_SETFL, flags);
        return rc == 0;
    }

    inline ssize_t socket::send(const void* buf, size_t len)
    {
        return ::send(get(), buf, len, MSG_NOSIGNAL);
    }

    inline ssize_t socket::sendto(const void* buf, size_t len,
        const sockaddr* dest_addr, socklen_t addrlen)
    {
        return ::sendto(get(), buf, len, MSG_NOSIGNAL, dest_addr, addrlen);
    }

    inline ssize_t socket::recv(void* buf, size_t len)
    {
        return ::recv(get(), buf, len, MSG_NOSIGNAL);
    }

    inline ssize_t socket::recvfrom(void* buf, size_t len,
        sockaddr* src_addr, socklen_t* addrlen)
    {
        return ::recvfrom(get(), buf, len, MSG_NOSIGNAL, src_addr, addrlen);
    }

} // namespace snet
