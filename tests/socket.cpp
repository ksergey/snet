/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#include <cstdlib>
#include <cstdio>
#include <snet/init.hpp>
#include <snet/socket.hpp>
#include <snet/resolver.hpp>
#include <snet/addrinfo_endpoint.hpp>

void print_socket(const snet::socket& s);

int main(int argc, char* argv[])
{
    if (!snet::init()) {
        std::printf("failed to init sockets\n");
        return EXIT_FAILURE;
    }

    snet::socket s0 = snet::socket::create(AF_INET, SOCK_STREAM, 0);
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
    s2 = snet::socket::create(snet::tcp_any);
    print_socket(s2);
    s2 = snet::socket::create(snet::tcp_v4);
    print_socket(s2);
    s2 = snet::socket::create(snet::tcp_v6);
    print_socket(s2);

    snet::resolver resolver = snet::resolver(snet::tcp_any, "google.ru:http");
    std::printf("google.ru resolved as:\n");
    for (auto& ep: resolver) {
        std::printf("   %s\n", ep.to_string().c_str());
    }

    resolver = snet::resolver(snet::tcp_any, "ya.ru:http");
    std::printf("ya.ru resolved as:\n");
    for (auto& ep: resolver) {
        std::printf("   %s\n", ep.to_string().c_str());
    }

    snet::shutdown();

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
