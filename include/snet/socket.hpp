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
#include <snet/last_error.hpp>

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
            /// @return false in case of error
            bool close();

            /// switch the socket non-blocking mode
            /// @return false in case of error
            bool set_nonblock(bool flag = true);

            /// switch the socket cloexec mode
            /// @return false in case of error
            bool set_cloexec(bool flag = true);

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
            /// @return true if success
            bool connect(const sockaddr* addr, socklen_t addrlen);

            /// bind socket
            /// @return true if success
            bool bind(const sockaddr* addr, socklen_t addrlen);

            /// place socket in a listen state
            /// @return true if success
            bool listen(int backlog = 10);

            /// accept incomming connection
            /// @return accepted socket
            /// the function actualy could return non valid socket in case of error
            socket accept(sockaddr* addr = nullptr, socklen_t* addrlen = nullptr);

            /// send data into socket
            ssize_t send(const void* buf, size_t len);

            /// send data into socket
            ssize_t sendto(const void* buf, size_t len,
                    const sockaddr* dest_addr, socklen_t addrlen);

            /// recv data from socket
            ssize_t recv(void* buf, size_t len);

            /// recv data from socket
            ssize_t recvfrom(void* buf, size_t len,
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

    inline socket socket::create(int family, int socktype, int protocol)
    {
        return ::socket(family, socktype, protocol);
    }

    inline bool socket::connect(const sockaddr* addr, socklen_t addrlen)
    {
        return ::connect(get(), addr, addrlen) == 0;
    }

    inline bool socket::bind(const sockaddr* addr, socklen_t addrlen)
    {
        return ::bind(get(), addr, addrlen) == 0;
    }

    inline bool socket::listen(int backlog)
    {
        return ::listen(get(), backlog) == 0;
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
