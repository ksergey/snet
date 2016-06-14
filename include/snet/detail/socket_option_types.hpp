/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_socket_option_types_140616010309_MADLIFE
#define MADLIFE_socket_option_types_140616010309_MADLIFE

#include <snet/common.hpp>
#include <snet/exception.hpp>

namespace snet {
namespace detail {

    template< int Level, int Name >
    class boolean
    {
        public:
            boolean() = default;
            ~boolean() = default;
            boolean(const boolean&) = default;
            boolean& operator=(const boolean&) = default;

            explicit boolean(bool value)
                : _value(value ? 1 : 0)
            {}

            bool value() const { return !!_value; }
            operator bool() const { return !!_value; }
            int level() const { return Level; }
            int name() const { return Name; }
            int* data() { return &_value; }
            const int* data() const { return &_value; }
            size_t size() const { return sizeof(_value); }

            void resize(size_t size)
            {
                // windows workaround
                if (size == sizeof(char)) {
                    _value = *reinterpret_cast< char* >(&_value) ? 1 : 0;
                } else if (size != sizeof(_value)) {
                    throw exception("boolean socket option resize");
                }
            }

        private:
            int _value{ 0 };
    };

    template< int Level, int Name >
    class integer
    {
        public:
            integer() = default;
            ~integer() = default;
            integer(const integer&) = default;
            integer& operator=(const integer&) = default;

            explicit integer(int value)
                : _value(value)
            {}

            int value() const { return _value; }
            int level() const { return Level; }
            int name() const { return Name; }
            int* data() { return &_value; }
            const int* data() const { return &_value; }
            size_t size() const { return sizeof(_value); }

            void resize(size_t size)
            {
                if (size != sizeof(_value)) {
                    throw exception("boolean socket option resize");
                }
            }

        private:
            int _value{ 0 };
    };
} // namespace detail
} // namespace snet

#endif /* MADLIFE_socket_option_types_140616010309_MADLIFE */
