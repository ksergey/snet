/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

namespace snet {

} // namespace snet


// include platform-depended code
#if defined( _WIN32 )
#   include "socket_impl_win.inc"
#else /* defined( _WIN32 ) */
#   include "socket_impl_posix.inc"
#endif /* defined( _WIN32 ) */
