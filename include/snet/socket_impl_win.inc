/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

// socket implementation for windows environment

namespace snet {

    inline bool socket::close()
    {
        if (valid()) {
            ::closesocket(_sock); // check result
            _sock = invalid_socket;
        }
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

    inline io_result socket::send(const void* buf, size_t len)
    {
        auto rc = ::send(get(), reinterpret_cast< const char* >(buf), int(len), 0);
        return rc == SOCKET_ERROR ? -1 : rc;
    }

    inline io_result socket::sendto(const void* buf, size_t len,
        const sockaddr* dest_addr, socklen_t addrlen)
    {
        auto rc = ::sendto(get(), reinterpret_cast< const char* >(buf), int(len), 0, dest_addr, addrlen);
        return rc == SOCKET_ERROR ? -1 : rc;
    }

    inline io_result socket::recv(void* buf, size_t len)
    {
        auto rc = ::recv(get(), reinterpret_cast< char* >(buf), int(len), 0);
        return rc == SOCKET_ERROR ? -1 : rc;
    }

    inline io_result socket::recvfrom(void* buf, size_t len,
        sockaddr* src_addr, socklen_t* addrlen)
    {
        auto rc = ::recvfrom(get(), reinterpret_cast< char* >(buf), int(len), 0, src_addr, addrlen);
        return rc == SOCKET_ERROR ? -1 : rc;
    }

    template< typename OptionT >
    inline op_result socket::set_option(const OptionT& option)
    {
        return ::setsockopt(get(), option.level(), option.name(),
                reinterpret_cast< const char* >(option.data()), option.size());
    }

    template< typename OptionT >
    inline op_result socket::get_option(OptionT& option)
    {
        socklen_t size = option.size();
        op_result result = ::getsockopt(get(), option.level(), option.name(),
                option.data(), &size);
        if (result) {
            option.resize(size);
        }

        return result;
    }

} // namespace snet
