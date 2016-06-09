/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_resolver_endpoint_090616114717_MADLIFE
#define MADLIFE_resolver_endpoint_090616114717_MADLIFE

#include <cassert>
#include <string>
#include <cstdint>
#include <snet/common.hpp>

namespace snet {

    class resolver_endpoint final
    {
        public:
            resolver_endpoint() = default;
            ~resolver_endpoint() = default;
            resolver_endpoint(const resolver_endpoint&) = default;
            resolver_endpoint& operator=(const resolver_endpoint&) = default;
            resolver_endpoint(resolver_endpoint&&) = default;
            resolver_endpoint& operator=(resolver_endpoint&&) = default;

            explicit resolver_endpoint(const addrinfo* data);

            /// return true if endpoint is valid
            bool valid() const { return _data != nullptr; }

            /// same as valid()
            operator bool() const { return valid(); }

            /// same as !valid()
            bool operator!() const { return !valid(); }

            /// return socket protocol family
            int domain() const { return _data->ai_family; }

            /// return socket type
            int type() const { return _data->ai_socktype; }

            /// return socket protocol
            int proto() const { return _data->ai_protocol; }

            /// return native data
            const sockaddr* data() const { return _data->ai_addr; }

            /// return native data size
            size_t size() const { return _data->ai_addrlen; }

            /// return string representation of endpoint
            /// @param[in] delim is delimiter between host and port
            std::string str(char delim = ' ') const;

        private:
            const addrinfo* _data{ nullptr };

            friend class resolver_iterator;
    };

    inline resolver_endpoint::resolver_endpoint(const addrinfo* data)
        : _data(data)
    {}

    inline std::string resolver_endpoint::str(char delim) const
    {
        assert( _data );

        const struct in_addr* address;
        uint16_t port;

        if (_data->ai_family == AF_INET) {
            const sockaddr_in* ipv4 = reinterpret_cast< const sockaddr_in* >(data());
            address = &(ipv4->sin_addr);
            port = ipv4->sin_port;
        } else if (_data->ai_family == AF_INET6) {
            const sockaddr_in6* ipv6 = reinterpret_cast< const sockaddr_in6* >(data());
            address = reinterpret_cast< const in_addr* >(&(ipv6->sin6_addr));
            port = ipv6->sin6_port;
        } else {
            return std::string();
        }

        assert( INET6_ADDRSTRLEN >= INET_ADDRSTRLEN );

        char buffer[INET6_ADDRSTRLEN]{};

        inet_ntop(_data->ai_family, address, buffer, sizeof(buffer));
        if (port > 0) {
            return std::string(buffer) + delim + std::to_string(ntohs(port));
        } else {
            return buffer;
        }
    }

} // namespace snet

#endif /* MADLIFE_resolver_endpoint_090616114717_MADLIFE */
