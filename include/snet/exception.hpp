/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_exception_100616141942_MADLIFE
#define MADLIFE_exception_100616141942_MADLIFE

#include <stdexcept>
#include <snet/common.hpp>

namespace snet {

    struct exception
        : public std::runtime_error
    {
        exception(const std::string& what)
            : std::runtime_error(what)
        {}
    };

} // namespace snet

#endif /* MADLIFE_exception_100616141942_MADLIFE */
