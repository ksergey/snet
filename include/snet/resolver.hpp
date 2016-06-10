/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_resolver_080616133016_MADLIFE
#define MADLIFE_resolver_080616133016_MADLIFE

#include <cassert>
#include <utility>
#include <string>
#include <snet/common.hpp>
#include <snet/resolver_iterator.hpp>
#include <snet/protocol.hpp>

namespace snet {

    class resolver
    {
        public:
            /// resolver iterator type
            typedef resolver_iterator const_iterator;

            resolver(const resolver&) = delete;
            resolver& operator=(const resolver&) = delete;

            resolver(resolver&& r);
            resolver& operator=(resolver&& r);

            resolver() = default;

            resolver(const protocol& p, const std::string& node, const std::string& service, int flags = 0);
            resolver(const protocol& p, const std::string& node, int flags = 0);
            ~resolver();

            /// return true if address resolution done
            bool valid() const { return _data != nullptr; }

            /// same as valid()
            operator bool() const { return valid(); }

            /// same as !valid()
            bool operator!() const { return !valid(); }

            /// return iterator to begin
            const_iterator begin() const { return const_iterator(_data); }

            /// return iterator to end
            const_iterator end() const { return const_iterator(); }

        private:
            void resolv(const protocol& p, const char* node, const char* service, int flags);

            addrinfo* _data{ nullptr };
    };

    inline resolver::resolver(resolver&& r)
    {
        assert( !_data );
        std::swap(_data, r._data);
    }

    inline resolver& resolver::operator=(resolver&& r)
    {
        std::swap(_data, r._data);
        return *this;
    }

    inline resolver::resolver(const protocol& p, const std::string& node, const std::string& service, int flags)
    {
        resolv(p, node.c_str(), service.c_str(), flags);
    }

    inline resolver::resolver(const protocol& p, const std::string& node, int flags)
    {
        size_t found = node.rfind(':');
        if (found != std::string::npos) {
            resolv(p, node.substr(0, found).c_str(), node.c_str() + found + 1, flags);
        } else {
            resolv(p, node.c_str(), nullptr, flags);
        }
    }

    inline resolver::~resolver()
    {
        if (_data) {
            freeaddrinfo(_data);
        }
    }

    inline void resolver::resolv(const protocol& p, const char* node, const char* service, int flags)
    {
        assert( !_data );

        addrinfo hints = {};

        hints.ai_family = p.domain;
        hints.ai_socktype = p.type;
        hints.ai_flags = flags;
        hints.ai_protocol = p.proto;
        hints.ai_canonname = nullptr;
        hints.ai_addr = nullptr;
        hints.ai_next = nullptr;

        getaddrinfo(node, service, &hints, &_data);
    }

} // namespace snet

#endif /* MADLIFE_resolver_080616133016_MADLIFE */
