/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_common_posix_070616233130_MADLIFE
#define MADLIFE_common_posix_070616233130_MADLIFE

#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>

namespace snet {

    /// native socket type
    typedef int sock_t;

    /// native socket invalid value
    static constexpr const sock_t invalid_socket = -1;

} // namespace snet

#endif /* MADLIFE_common_posix_070616233130_MADLIFE */
