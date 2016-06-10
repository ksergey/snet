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
            ssize_t res = socket.send(data, size);
            if (res > 0) {
                data += res;
                size -= res;
            } else if (res < 0) {
                if (snet::last_error::interrupted()) {
                    throw std::runtime_error("interrupted");
                }
                if (!snet::last_error::again()) {
                    throw std::runtime_error("socket error happend <" +
                            std::to_string(snet::last_error::code()) + ">");
                }
            } else {
                throw std::runtime_error("unexpected peer disconnect");
            }
        }

        std::printf("message sent (attempts: %d)\n", attempts);

        char buffer[64];
        attempts = 0;
        while (true) {
            ++attempts;
            ssize_t res = socket.recv(buffer, sizeof(buffer) - 1);
            if (res > 0) {
                buffer[res] = '\0';
                std::printf("%s", buffer);
            } else if (res < 0) {
                if (snet::last_error::interrupted()) {
                    throw std::runtime_error("interrupted");
                }
                if (!snet::last_error::again()) {
                    throw std::runtime_error("socket error happend <" +
                            std::to_string(snet::last_error::code()) + ">");
                }
            } else {
                std::printf("\n");
                std::printf("peer disconnected\n");
                break;
            }
        }

        std::printf("done ( attempts = %d )\n", attempts);

    } catch (const std::exception& e) {
        std::fprintf(stderr, "error: %s\n", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
