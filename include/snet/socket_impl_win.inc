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

    inline bool socket::set_nonblock(bool value)
    {
        unsigned int flags = value;
        int rc = ::ioctlsocket(get(), FIONBIO, &flags);
        return rc == 0;
    }

    inline bool socket::set_nonblock(bool value)
    {
        auto rc = SetHandleInformation(reinterpret_cast< HANDLE >(get()), HANDLE_FLAG_INHERIT, int(value));
        return rc != 0;
    }

} // namespace snet
