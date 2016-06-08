/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_socket_070616234927_MADLIFE
#define MADLIFE_socket_070616234927_MADLIFE

#include <snet/common.hpp>

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
            /// @param[in] value is new value
            /// @return false in case of error
            bool set_nonblock(bool value = true);

            /// switch the socket cloexec mode
            /// @param[in] value is new value
            /// @return false in case of error
            bool set_cloexec(bool value = true);

            /// create socket
            /// @param[in] domain is communication domain
            /// @param[in] type is communication semantic
            /// @param[in] protocol is communication protocol family
            /// @return socket object
            static socket create(int domain, int type, int protocol);

        private:
            sock_t _sock{ invalid_socket };
    };

} // namespace snet

// include implementation
#include "socket_impl.inc"

#endif /* MADLIFE_socket_070616234927_MADLIFE */
