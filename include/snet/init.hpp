/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_init_080616182514_MADLIFE
#define MADLIFE_init_080616182514_MADLIFE

#include <snet/common.hpp>

namespace snet {

    static inline bool init()
    {
#if defined( _WIN32 )
        WSADATA data;
        return ::WSAStartup(MAKEWORD(2,2), &data) == 0;
#else /* defined( _WIN32 ) */
        return true;
#endif /* defined( _WIN32 ) */
    }

    static inline bool shutdown()
    {
#if defined( _WIN32 )
        return ::WSACleanup() == 0;
#else /* defined( _WIN32 ) */
        return true;
#endif /* defined( _WIN32 ) */
    }

} // namespace snet

#endif /* MADLIFE_init_080616182514_MADLIFE */
