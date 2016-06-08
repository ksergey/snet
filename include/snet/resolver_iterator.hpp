/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#ifndef MADLIFE_resolver_iterator_080616161153_MADLIFE
#define MADLIFE_resolver_iterator_080616161153_MADLIFE

#include <iterator>
#include <snet/addrinfo_endpoint.hpp>

namespace snet {

    class resolver_iterator final
        : std::iterator< std::forward_iterator_tag, addrinfo_endpoint >
    {
        public:
            resolver_iterator() = default;
            ~resolver_iterator() = default;

            explicit resolver_iterator(const addrinfo* data);

            resolver_iterator& operator++();
            bool operator==(const resolver_iterator& it) const { return _ep._data == it._ep._data; }
            bool operator!=(const resolver_iterator& it) const { return _ep._data != it._ep._data; }
            const addrinfo_endpoint& operator*() const { return _ep; }
            const addrinfo_endpoint* operator->() const { return &_ep; }

        private:
            addrinfo_endpoint _ep;
    };

    inline resolver_iterator::resolver_iterator(const addrinfo* data)
        : _ep(data)
    {}

    inline resolver_iterator& resolver_iterator::operator++()
    {
        if (_ep._data != nullptr) {
            _ep._data = _ep._data->ai_next;
        }
        return *this;
    }

} // namespace snet

#endif /* MADLIFE_resolver_iterator_080616161153_MADLIFE */
