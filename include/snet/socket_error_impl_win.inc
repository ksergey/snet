/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

namespace snet {

    inline bool socket_result::is_interrupted() const
    {
        return _code == WSAEINTR;
    }

    inline bool socket_error::is_again() const
    {
        return _code == WSAEWOULDBLOCK;
    }

} // namespace snet
