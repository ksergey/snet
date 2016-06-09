/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_socket_070616234927_MADLIFE
#define MADLIFE_socket_070616234927_MADLIFE

#include <snet/common.hpp>
#include <snet/protocol.hpp>

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

} // namespace snet

// include implementation
#include "socket_impl.inc"

#endif /* MADLIFE_socket_070616234927_MADLIFE */
