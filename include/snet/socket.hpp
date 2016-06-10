/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_socket_070616234927_MADLIFE
#define MADLIFE_socket_070616234927_MADLIFE

#include <cassert>
#include <utility>
#include <snet/common.hpp>
#include <snet/protocol.hpp>
#include <snet/result.hpp>
#include <snet/exception.hpp>

namespace snet {

    class socket
    {
        public:
            socket(const socket&) = delete;
            socket& operator=(const socket&) = delete;

            socket(socket&& s);
            socket& operator=(socket&& s);

            socket(sock_t d = invalid_socket);
            ~socket();

            /// return true if socket is valid
            bool valid() const { return _sock != invalid_socket; }

            /// implied cast to bool
            operator bool() const { return valid(); }

            /// implement operator !(not)
            bool operator!() const { return !valid(); }

            /// return native socket handler
            sock_t get() { return _sock; }

            /// close the socket
            void close() noexcept;

            /// switch the socket non-blocking mode
            /// @return false in case of error
            bool set_nonblock(bool flag = true);

            /// switch the socket cloexec mode
            /// @return false in case of error
            bool set_cloexec(bool flag = true);

            /// switch naggles algorithm
            /// @return false in case of error
            bool set_tcpnodelay(bool flag = true);

            /// switch reuseaddr socket option
            /// @return false in case of error
            bool set_reuseaddr(bool flag = true);

            /// create socket
            /// @param[in] family is communication domain
            /// @param[in] socktype is communication semantic
            /// @param[in] protocol is communication protocol family
            /// @return socket object
            static socket create(int family, int socktype, int protocol);

            /// create socket
            /// @param[in] p is communication protocol definition (@see protocol.hpp)
            /// @return socket object
            static socket create(const protocol& p) { return create(p.domain, p.type, p.proto); }

            /// establish connection
            op_result connect(const sockaddr* addr, socklen_t addrlen) noexcept;

            /// bind socket
            /// @return true if success
            op_result bind(const sockaddr* addr, socklen_t addrlen) noexcept;

            /// place socket in a listen state
            /// @return true if success
            op_result listen(int backlog = 10) noexcept;

            /// accept incomming connection
            /// @return accepted socket
            /// the function actualy could return non valid socket in case of error
            socket accept(sockaddr* addr = nullptr, socklen_t* addrlen = nullptr);

            /// send data into socket
            io_result send(const void* buf, size_t len);

            /// send data into socket
            io_result sendto(const void* buf, size_t len,
                    const sockaddr* dest_addr, socklen_t addrlen);

            /// recv data from socket
            io_result recv(void* buf, size_t len);

            /// recv data from socket
            io_result recvfrom(void* buf, size_t len,
                    sockaddr* src_addr, socklen_t* addrlen);

        private:
            sock_t _sock{ invalid_socket };
    };

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
        int value = flag ? 1 : 0;
        return ::setsockopt(get(), IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value)) == 0;
    }

    inline bool socket::set_reuseaddr(bool flag)
    {
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

    inline socket socket::accept(sockaddr* addr, socklen_t* addrlen)
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

#endif /* MADLIFE_socket_070616234927_MADLIFE */
