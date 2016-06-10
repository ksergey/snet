/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_tcp_100616095037_MADLIFE
#define MADLIFE_tcp_100616095037_MADLIFE

#include <string>
#include <stdexcept>
#include <snet/resolver.hpp>
#include <snet/socket.hpp>

namespace snet {

    class tcp
    {
        public:
            static socket connect(const std::string& node);
            static socket connect(const std::string& node, const std::string& service);
            static socket bind(const std::string& node);
            static socket bind(const std::string& node, const std::string& service);

        private:
            static socket connect(const resolver& r);
            static socket bind(const resolver& r);
    };

    inline socket tcp::connect(const std::string& node)
    {
        return connect(resolver(tcp_any, node));
    }

    inline socket tcp::connect(const std::string& node, const std::string& service)
    {
        return connect(resolver(tcp_any, node, service));
    }

    inline socket tcp::bind(const std::string& node)
    {
        return bind(resolver(tcp_any, node, AI_PASSIVE));
    }

    inline socket tcp::bind(const std::string& node, const std::string& service)
    {
        return bind(resolver(tcp_any, node, service, AI_PASSIVE));
    }

    inline socket tcp::connect(const resolver& r)
    {
        for (auto& ep: r) {
            socket s = socket::create(ep.domain(), ep.type(), ep.proto());
            if (!s) {
                throw std::runtime_error("failed to create socket");
            }

            if (s.connect(ep.data(), ep.size())) {
                s.set_nonblock();
                s.set_cloexec();
                s.set_tcpnodelay();
                return s;
            }
        }

        return socket();
    }

    inline socket tcp::bind(const resolver& r)
    {
        for (auto& ep: r) {
            socket s = socket::create(ep.domain(), ep.type(), ep.proto());
            if (!s) {
                throw std::runtime_error("failed to create socket");
            }

            s.set_reuseaddr();
            if (s.bind(ep.data(), ep.size())) {
                s.set_nonblock();
                s.set_cloexec();
                if (!s.listen()) {
                    throw std::runtime_error("failed to listen");
                }
                return s;
            }
        }

        return socket();
    }

} // namespace snet

#endif /* MADLIFE_tcp_100616095037_MADLIFE */
