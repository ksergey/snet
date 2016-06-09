/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_endpoint_090616115018_MADLIFE
#define MADLIFE_endpoint_090616115018_MADLIFE

#include <snet/common.hpp>
#include <cassert>
#include <string>
#include <cstdint>

namespace snet {

    class endpoint final
    {
        public:
            endpoint(const endpoint&) = default;
            endpoint& operator=(const endpoint&) = default;
            endpoint(endpoint&&) = default;
            endpoint& operator=(endpoint&&) = default;

            endpoint() = default;
            ~endpoint() = default;

            endpoint(const std::string& addr, uint16_t port);

            /// return true if endpoint is valid
            bool valid() const;

            /// same as valid()
            operator bool() const { return valid(); }

            /// same as !valid()
            bool operator!() const { return !valid(); }

            /// return endpoint domain
            int domain() const { return _data.in.sa_family; }

            /// return native data
            const sockaddr* data() const { return &_data.in; }

            /// return native data size
            size_t size() const;

            /// return string representation of endpoint
            /// @param[in] delim is delimiter between host and port
            std::string str(char delim = ' ') const;

        private:
            union {
                sockaddr in;
                sockaddr_in in4;
                sockaddr_in6 in6;
            } _data = {};
    };

    inline endpoint::endpoint(const std::string& addr, uint16_t port)
    {
        if (::inet_pton(AF_INET6, addr.c_str(), &_data.in6.sin6_addr) == 1) {
            _data.in6.sin6_family = AF_INET6;
            _data.in6.sin6_port = htons(port);
        } else if (::inet_pton(AF_INET, addr.c_str(), &_data.in4.sin_addr)) {
            _data.in4.sin_family = AF_INET;
            _data.in4.sin_port = htons(port);
        } else {
            _data.in.sa_family = AF_UNSPEC;
        }
    }

    inline bool endpoint::valid() const
    {
        return domain() == AF_INET || domain() == AF_INET6;
    }

    inline size_t endpoint::size() const
    {
        if (domain() == AF_INET) {
            return sizeof(_data.in4);
        }

        if (domain() == AF_INET6) {
            return sizeof(_data.in6);
        }

        return 0;
    }

    inline std::string endpoint::str(char delim) const
    {
        if (_data.in.sa_family == AF_INET) {
            char buffer[INET_ADDRSTRLEN]{};
            inet_ntop(AF_INET, &_data.in4.sin_addr, buffer, sizeof(buffer));
            return std::string(buffer) + delim + std::to_string(ntohs(_data.in4.sin_port));
        } else if (_data.in.sa_family == AF_INET6) {
            char buffer[INET6_ADDRSTRLEN]{};
            inet_ntop(AF_INET6, &_data.in6.sin6_addr, buffer, sizeof(buffer));
            return std::string(buffer) + delim + std::to_string(ntohs(_data.in6.sin6_port));
        } else {
            return std::string();
        }
    }

} // namespace snet

#endif /* MADLIFE_endpoint_090616115018_MADLIFE */
