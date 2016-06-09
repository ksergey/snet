/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_last_error_090616181100_MADLIFE
#define MADLIFE_last_error_090616181100_MADLIFE

#include <snet/common.hpp>

namespace snet {

    struct last_error
    {
        /// return last error code (OS native)
        static int code();

        static bool interrupted();
        static bool again();
    };

} // namespace snet

// include platform-depended code
#if defined( _WIN32 )
#   include "last_error_impl_win.inc"
#else /* defined( _WIN32 ) */
#   include "last_error_impl_posix.inc"
#endif /* defined( _WIN32 ) */

#endif /* MADLIFE_last_error_090616181100_MADLIFE */
