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

            socket() = default;

        private:
            sock_t _sock{ invalid_socket };
    };

} // namespace snet

// include implementation
#include "socket_impl.inc"

#endif /* MADLIFE_socket_070616234927_MADLIFE */
