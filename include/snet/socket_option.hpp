/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_socket_option_140616010327_MADLIFE
#define MADLIFE_socket_option_140616010327_MADLIFE

#include <snet/detail/socket_option_types.hpp>

namespace snet {

    typedef snet::detail::boolean< IPPROTO_TCP, TCP_NODELAY > tcp_nodelay;
    typedef snet::detail::boolean< SOL_SOCKET, SO_REUSEADDR > reuseaddr;
    typedef snet::detail::integer< SOL_SOCKET, SO_RCVBUF > rcvbuf;
    typedef snet::detail::integer< SOL_SOCKET, SO_SNDBUF > sndbuf;

} // namespace snet

#endif /* MADLIFE_socket_option_140616010327_MADLIFE */
