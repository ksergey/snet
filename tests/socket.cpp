/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#include <cstdlib>
#include <cstdio>
#include <snet/socket.hpp>
#include <snet/resolver.hpp>
#include <snet/endpoint.hpp>

void print_socket(const snet::socket& s);

int main(int argc, char* argv[])
{
    snet::socket s0 = snet::socket::create(AF_INET, SOCK_STREAM, 0);
    print_socket(s0);
    snet::socket s1 = std::move(s0);
    s1.set_cloexec();
    s1.set_nonblock();
    print_socket(s0);
    print_socket(s0);
    s1.close();
    print_socket(s1);
    snet::socket s2 = std::move(s1);
    print_socket(s2);
    try {
        s2 = snet::socket::create(snet::tcp_any);
    } catch (const std::exception& e) {
        std::printf("expected error: %s\n", e.what());
    }
    s2 = snet::socket::create(snet::tcp_v4);
    print_socket(s2);
    s2 = snet::socket::create(snet::tcp_v6);
    print_socket(s2);

    snet::resolver resolver = snet::resolver(snet::tcp_any, "google.ru:http");
    std::printf("google.ru resolved as:\n");
    for (auto& ep: resolver) {
        std::printf("   %s\n", ep.str().c_str());
    }

    resolver = snet::resolver(snet::tcp_any, "ya.ru:http");
    std::printf("ya.ru resolved as:\n");
    for (auto& ep: resolver) {
        std::printf("   %s\n", ep.str().c_str());
    }

    snet::endpoint ep("127.0.0.1", 444);
    std::printf("endpoint: %s\n", ep.str().c_str());

    ep = snet::endpoint("2001:0DB8:AA10:0001:0000:0000:0000:00FB", 4446);
    std::printf("endpoint: %s\n", ep.str().c_str());

    auto res = s2.send("1234", 4);
    if (!res) {
        if (res.is_disconnected()) {
            std::printf("disconnected\n");
        } else {
            std::printf("failed to send, err: %d\n", res.code());
        }
    } else {
        std::printf("sent %d bytes\n", int(res.bytes()));
    }

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
