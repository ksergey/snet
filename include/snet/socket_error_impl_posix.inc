/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

namespace snet {

    inline bool socket_error::is_interrupted() const
    {
        return _code == EINTR;
    }

    inline bool socket_error::is_again() const
    {
        return _code == EAGAIN || _code == EWOULDBLOCK;
    }

} // namespace snet
