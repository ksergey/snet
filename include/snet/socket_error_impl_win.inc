/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

namespace snet {

    inline const char* socket_error::str() const
    {
        static char buffer[512];
        int rc = std::snprintf(buffer, sizeof(buffer), "%d: ", _code);
        ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, _code, 0, buffer + rc,
            sizeof(buffer) - rc - 1, nullptr);
        return buffer;
    }

    inline bool socket_result::is_interrupted() const
    {
        return _code == WSAEINTR;
    }

    inline bool socket_error::is_again() const
    {
        return _code == WSAEWOULDBLOCK;
    }

} // namespace snet
