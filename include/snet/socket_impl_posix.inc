/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

// socket implementation for posix environment

namespace snet {

    inline void socket::close() noexcept
    {
        if (valid()) {
            ::close(_sock); // todo check errors
            _sock = invalid_socket;
        }
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

    inline io_result socket::send(const void* buf, size_t len) noexcept
    {
        return ::send(get(), buf, len, MSG_NOSIGNAL);
    }

    inline io_result socket::sendto(const void* buf, size_t len,
        const sockaddr* dest_addr, socklen_t addrlen) noexcept
    {
        return ::sendto(get(), buf, len, MSG_NOSIGNAL, dest_addr, addrlen);
    }

    inline io_result socket::recv(void* buf, size_t len) noexcept
    {
        return ::recv(get(), buf, len, MSG_NOSIGNAL);
    }

    inline io_result socket::recvfrom(void* buf, size_t len,
        sockaddr* src_addr, socklen_t* addrlen) noexcept
    {
        return ::recvfrom(get(), buf, len, MSG_NOSIGNAL, src_addr, addrlen);
    }

    template< typename OptionT >
    inline op_result socket::set_option(const OptionT& option) noexcept
    {
        return ::setsockopt(get(), option.level(), option.name(),
                option.data(), option.size());
    }

    template< typename OptionT >
    inline op_result socket::get_option(OptionT& option) noexcept
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
