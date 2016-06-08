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
#include <snet/protocol.hpp>

namespace snet {

    class resolver
    {
        public:
            resolver(const resolver&) = delete;
            resolver& operator=(const resolver&) = delete;

            resolver(resolver&& r);
            resolver& operator=(resolver&& r);

            resolver() = default;

            resolver(const protocol& p, const std::string& node, const std::string& service, int flags = 0);
            resolver(const protocol& p, const std::string& node, int flags = 0);
            ~resolver();

            /// return true if address resolution done
            bool valid() const { return _addrinfo != nullptr; }

            /// same as valid()
            operator bool() const { return valid(); }

            /// same as !valid()
            bool operator!() const { return !valid(); }

        private:
            void resolv(const protocol& p, const char* node, const char* service, int flags);

            addrinfo* _addrinfo{ nullptr };
    };

    inline resolver::resolver(resolver&& r)
    {
        assert( !_addrinfo );
        std::swap(_addrinfo, r._addrinfo);
    }

    inline resolver& resolver::operator=(resolver&& r)
    {
        std::swap(_addrinfo, r._addrinfo);
        return *this;
    }

    inline resolver::resolver(const protocol& p, const std::string& node, const std::string& service, int flags)
    {
        resolv(p, node.c_str(), service.c_str(), flags);
    }

    inline resolver::resolver(const protocol& p, const std::string& node, int flags)
    {
        size_t found = node.find(':');
        if (found != std::string::npos) {
            resolv(p, node.substr(0, found).c_str(), node.c_str() + found + 1, flags);
        } else {
            resolv(p, node.c_str(), nullptr, flags);
        }
    }

    inline resolver::~resolver()
    {
        if (_addrinfo) {
            freeaddrinfo(_addrinfo);
        }
    }

    inline void resolver::resolv(const protocol& p, const char* node, const char* service, int flags)
    {
        assert( !_addrinfo );

        addrinfo hints = {};

        hints.ai_family = p.family;
        hints.ai_socktype = p.socktype;
        hints.ai_flags = flags;
        hints.ai_protocol = p.protocol;
        hints.ai_canonname = nullptr;
        hints.ai_addr = nullptr;
        hints.ai_next = nullptr;

        getaddrinfo(node, service, &hints, &_addrinfo);
    }

} // namespace snet

#endif /* MADLIFE_resolver_080616133016_MADLIFE */
