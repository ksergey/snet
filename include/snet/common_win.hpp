/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_common_win_070616233132_MADLIFE
#define MADLIFE_common_win_070616233132_MADLIFE

#include <winsock2.h>

namespace snet {

    /// native socket type
    typedef SOCKET socket_t;

    /// native socket invalid value
    static const socket_t invalid_socket = INVALID_SOCKET;

} // namespace snet

#endif /* MADLIFE_common_win_070616233132_MADLIFE */
