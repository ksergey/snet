/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_common_070616225738_MADLIFE
#define MADLIFE_common_070616225738_MADLIFE

// include platform-depended code
#if defined( _WIN32 )
#   include <snet/common_win.hpp>
#else /* defined( _WIN32 ) */
#   include <snet/common_posix.hpp>
#endif /* defined( _WIN32 ) */

namespace snet {

} // namespace snet

#endif /* MADLIFE_common_070616225738_MADLIFE */
