/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_result_100616135807_MADLIFE
#define MADLIFE_result_100616135807_MADLIFE

#include <snet/socket_error.hpp>

namespace snet {

    class op_result final
        : public socket_error
    {
        public:
            op_result() = default;
            op_result(int value);

            bool success() const { return _value == 0; }
            operator bool() const { return success(); }
            bool operator!() const { return !success(); }

        private:
            int _value{ 0 };
    };

    inline op_result::op_result(int value)
#if defined( _WIN32 )
        : socket_error(value == SOCKET_ERROR ? WSAGetLastError() : 0)
#else /* defined( _WIN32 ) */
        : socket_error(value == -1 ? errno : 0)
#endif /* defined( _WIN32 ) */
        , _value(value)
    {}

    class io_result final
        : public socket_error
    {
        public:
            io_result() = default;
            io_result(ssize_t value);

            bool success() const { return _value > 0; }
            operator bool() const { return success(); }
            bool operator!() const { return !success(); }

            size_t bytes() const { return _value; }
            bool is_disconnected() const { return _value == 0; }

        private:
            ssize_t _value{ 0 };
    };

    inline io_result::io_result(ssize_t value)
#if defined( _WIN32 )
        : socket_error(value < 0 ? WSAGetLastError() : 0)
#else /* defined( _WIN32 ) */
        : socket_error(value < 0 ? errno : 0)
#endif /* defined( _WIN32 ) */
        , _value(value)
    {}

} // namespace snet

#endif /* MADLIFE_result_100616135807_MADLIFE */
