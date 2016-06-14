/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_common_win_070616233132_MADLIFE
#define MADLIFE_common_win_070616233132_MADLIFE

#if ! defined( WIN32_LEAN_AND_MEAN )
#   define WIN32_LEAN_AND_MEAN
#endif /* ! defined( WIN32_LEAN_AND_MEAN ) */

#include <system_error>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace snet {

    /// native socket type
    typedef SOCKET sock_t;

    /// native socket invalid value
    static constexpr const sock_t invalid_socket = INVALID_SOCKET;

    /// winsock "special" initializer
    struct winsock_initializer final
    {
        winsock_initializer()
        {
            WSADATA data;
            auto rc = ::WSAStartup(MAKEWORD(2,2), &data);
            if (rc != 0) {
                throw std::system_error(::WSAGetLastError(), std::system_category(), "WSAStartup failed");
            }
        }

        ~winsock_initializer()
        {
            WSACleanup();
        }
    };

    /// init trick
    static const winsock_initializer winsock_initialized{};

    /// map some types
    typedef int ssize_t;

    /// return last socket error
    inline int last_socket_error() { return ::WSAGetLastError(); }

} // namespace snet

#endif /* MADLIFE_common_win_070616233132_MADLIFE */
