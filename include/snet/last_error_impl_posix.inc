/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

namespace snet {

    inline int last_error::code()
    {
        return errno;
    }

    inline bool last_error::interrupted()
    {
        return code() == EINTR;
    }

    inline bool last_error::again()
    {
        return code() == EAGAIN || code() == EWOULDBLOCK;
    }

} // namespace snet
