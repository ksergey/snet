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

    inline bool socket::set_nonblock(bool value)
    {
        int flags = ::fcntl(get(), F_GETFL, 0);
        if (flags == -1) {
            flags = 0;
        }

        if (value) {
            flags |= O_NONBLOCK;
        } else {
            flags &= ~int(O_NONBLOCK);
        }

        int rc = ::fcntl(get(), F_SETFL, flags);
        return rc == 0;
    }

    inline bool socket::set_cloexec(bool value)
    {
        int flags = ::fcntl(get(), F_GETFL, 0);
        if (flags == -1) {
            flags = 0;
        }

        if (value) {
            flags |= FD_CLOEXEC;
        } else {
            flags &= ~int(FD_CLOEXEC);
        }

        int rc = ::fcntl(get(), F_SETFL, flags);
        return rc == 0;
    }

} // namespace snet
