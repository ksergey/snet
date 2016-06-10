/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_result_100616135807_MADLIFE
#define MADLIFE_result_100616135807_MADLIFE

#include <snet/socket_error.hpp>
#include <snet/socket.hpp>

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
        : socket_error(value != 0 ? last_socket_error() : 0)
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
        : socket_error(value < 0 ? last_socket_error() : 0)
        , _value(value)
    {}

    class accept_result final
        : public socket_error
    {
        public:
            accept_result() = default;
            accept_result(sock_t s);

            bool success() const { return _sock.valid(); }
            operator bool() const { return success(); }
            bool operator!() const { return !success(); }

            socket&& get() { return std::move(_sock); }

        private:
            socket _sock;
    };

    inline accept_result::accept_result(sock_t s)
        : socket_error(s == invalid_socket ? last_socket_error() : 0)
        , _sock(s)
    {}

} // namespace snet

#endif /* MADLIFE_result_100616135807_MADLIFE */
