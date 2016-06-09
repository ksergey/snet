/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

namespace snet {

    inline int last_error::code()
    {
        return WSAGetLastError();
    }

    inline bool last_error::interrupted()
    {
        return code() == WSAEINTR;
    }

    inline bool last_error::again()
    {
        return code() == WSAEWOULDBLOCK;
    }

} // namespace snet
