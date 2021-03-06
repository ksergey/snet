/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_protocol_080616141539_MADLIFE
#define MADLIFE_protocol_080616141539_MADLIFE

#include <snet/common.hpp>

namespace snet {

    struct protocol
    {
        /// protocol domain (i.e. AF_INET, AF_INET6)
        int domain;
        /// protocol type (i.e. SOCK_STREAM)
        int type;
        /// protocol (almost always 0)
        int proto;
    };

    static constexpr const protocol tcp_any = protocol{ AF_UNSPEC,  SOCK_STREAM, 0 };
    static constexpr const protocol tcp_v4  = protocol{ AF_INET,    SOCK_STREAM, 0 };
    static constexpr const protocol tcp_v6  = protocol{ AF_INET6,   SOCK_STREAM, 0 };
    static constexpr const protocol udp_any = protocol{ AF_UNSPEC,  SOCK_DGRAM, 0 };
    static constexpr const protocol udp_v4  = protocol{ AF_INET,    SOCK_DGRAM, 0 };
    static constexpr const protocol udp_v6  = protocol{ AF_INET6,   SOCK_DGRAM, 0 };

} // namespace snet

#endif /* MADLIFE_protocol_080616141539_MADLIFE */
