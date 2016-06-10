/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#include <cstdio>
#include <cstdlib>
#include <snet/tcp.hpp>

int main(int argc, char* argv[])
{
    const char* address = "localhost:9999";
    if (argc > 1) {
        address = argv[1];
    }

    static std::string content = "aloha";

    try {
        std::printf("connect address: \"%s\"\n", address);

        snet::socket socket = snet::tcp::connect(address);
        if (!socket) {
            throw std::runtime_error("connect failed");
        }

        std::printf("connected!\n");

        const char* data = content.c_str();
        size_t size = content.size() + 1; // including '\0'

        int attempts = 0;
        while (size > 0) {
            ++attempts;
            auto res = socket.send(data, size);
            if (res) {
                data += res.bytes();
                size -= res.bytes();
            } else if (res.is_disconnected()) {
                throw std::runtime_error("unexpected disconnect");
            } else if (!res.is_again()) {
                throw std::runtime_error("socket send error <" +
                        std::to_string(res.code()) + ">");
            }
        }

        std::printf("message sent (attempts: %d)\n", attempts);

        char buffer[64];
        attempts = 0;
        while (true) {
            ++attempts;
            auto res = socket.recv(buffer, sizeof(buffer) - 1);
            if (res) {
                buffer[res.bytes()] = '\0';
                std::printf("%s", buffer);
            } else if (res.is_disconnected()) {
                std::printf("\n");
                std::printf("peer disconnected\n");
                break;
            } else if (!res.is_again()) {
                throw std::runtime_error("socket recv error <" +
                        std::to_string(res.code()) + ">");
            }
        }

        std::printf("done ( attempts = %d )\n", attempts);

    } catch (const std::exception& e) {
        std::fprintf(stderr, "error: %s\n", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
