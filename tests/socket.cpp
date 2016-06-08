/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#include <cstdlib>
#include <cstdio>
#include <snet/socket.hpp>

void print_socket(const snet::socket& s);

int main(int argc, char* argv[])
{
    snet::socket s0= snet::socket::create(AF_INET, SOCK_STREAM, 0);
    print_socket(s0);
    snet::socket s1 = std::move(s0);
    s1.set_cloexec();
    s1.set_nonblock();
    print_socket(s0);
    print_socket(s1);
    s1.close();
    print_socket(s1);
    snet::socket s2 = std::move(s1);
    print_socket(s2);

    return EXIT_SUCCESS;
}

void print_socket(const snet::socket& s)
{
    if (s) {
        std::printf("socket is valid\n");
    } else {
        std::printf("socket is not valid\n");
    }
}
