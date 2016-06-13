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

namespace snet {

    class op_result;
    class io_result;
    class accept_result;

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
            accept_result accept(sockaddr* addr = nullptr, socklen_t* addrlen = nullptr);

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

            /// set socket option
            template< typename OptionT >
            op_result set_option(const OptionT& option);

            /// get socket option
            template< typename OptionT >
            op_result get_option(OptionT& option);

        private:
            sock_t _sock{ invalid_socket };
    };

} // namespace snet

#include "socket_impl.inc"

#endif /* MADLIFE_socket_070616234927_MADLIFE */
