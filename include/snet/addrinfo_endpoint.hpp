/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_addrinfo_endpoint_080616160047_MADLIFE
#define MADLIFE_addrinfo_endpoint_080616160047_MADLIFE

#include <cassert>
#include <string>
#include <cstdint>
#include <snet/common.hpp>
#include <snet/protocol.hpp>

namespace snet {

    class addrinfo_endpoint final
    {
        public:
            addrinfo_endpoint() = default;
            ~addrinfo_endpoint() = default;
            addrinfo_endpoint(const addrinfo_endpoint&) = default;
            addrinfo_endpoint& operator=(const addrinfo_endpoint&) = default;
            addrinfo_endpoint(addrinfo_endpoint&&) = default;
            addrinfo_endpoint& operator=(addrinfo_endpoint&&) = default;

            explicit addrinfo_endpoint(const addrinfo* data);

            /// return true if endpoint is valid
            bool valid() const { return _data != nullptr; }

            /// same as valid()
            operator bool() const { return valid(); }

            /// same as !valid()
            bool operator!() const { return !valid(); }

            /// return endpoint protocol
            snet::protocol protocol() const;

            /// return native data
            const sockaddr* data() const { return _data->ai_addr; }

            /// return native data size
            socklen_t size() const { return _data->ai_addrlen; }

            /// return string representation of endpoint
            /// @param[in] delim is delimiter between host and port
            std::string to_string(char delim = ' ') const;

        private:
            const addrinfo* _data{ nullptr };

            friend class resolver_iterator;
    };

    inline addrinfo_endpoint::addrinfo_endpoint(const addrinfo* data)
        : _data(data)
    {}

    inline snet::protocol addrinfo_endpoint::protocol() const
    {
        return snet::protocol{ _data->ai_family, _data->ai_socktype, _data->ai_protocol };
    }

    inline std::string addrinfo_endpoint::to_string(char delim) const
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
        return std::string();
    }

} // namespace snet

#endif /* MADLIFE_addrinfo_endpoint_080616160047_MADLIFE */