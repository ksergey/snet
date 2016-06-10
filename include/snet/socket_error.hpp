/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_socket_error_100616135256_MADLIFE
#define MADLIFE_socket_error_100616135256_MADLIFE

#include <snet/common.hpp>

namespace snet {

    class socket_error
    {
        public:
            socket_error() = default;
            socket_error(int code);

            int code() const { return _code; }

            bool is_interrupted() const;
            bool is_again() const;

        private:
            int _code{ 0 };
    };

    inline socket_error::socket_error(int code)
        : _code(code)
    {}

} // namespace snet

// include platform-depended code
#if defined( _WIN32 )
#   include "socket_error_impl_win.inc"
#else /* defined( _WIN32 ) */
#   include "socket_error_impl_posix.inc"
#endif /* defined( _WIN32 ) */

#endif /* MADLIFE_socket_error_100616135256_MADLIFE */
