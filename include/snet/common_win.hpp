/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_common_win_070616233132_MADLIFE
#define MADLIFE_common_win_070616233132_MADLIFE

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

namespace snet {

    /// native socket type
    typedef SOCKET sock_t;

    /// native socket invalid value
    static constexpr const sock_t invalid_socket = INVALID_SOCKET;

} // namespace snet

#endif /* MADLIFE_common_win_070616233132_MADLIFE */
