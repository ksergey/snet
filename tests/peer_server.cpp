/*
 * The MIT License (MIT)
 * Copyright (c) 2016 Sergey Kovalevich <inndie@gmail.com>
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <snet/tcp.hpp>

int main(int argc, char* argv[])
{
    const char* address = "localhost:9999";
    if (argc > 1) {
        address = argv[1];
    }

    try {
        std::printf("bind address: \"%s\"\n", address);

        snet::socket socket = snet::tcp::bind(address);
        if (!socket) {
            throw std::runtime_error("bind failed");
        }

        while (true) {
            auto res = socket.accept();
            if (res) {
                socket = res.get();
                socket.set_nonblock();
                socket.set_cloexec();
                socket.set_tcpnodelay();
                break;
            }
            if (res.is_interrupted()) {
                throw std::runtime_error("interrupted");
            }
            if (!res.is_again()) {
                throw std::runtime_error("socket error happend <" +
                        std::string(res.str()) + ">");
            }
        }

        std::printf("peer accepted!\n");

        char buffer[128];
        size_t offset = 0;
        while (true) {
            auto res = socket.recv(buffer + offset, sizeof(buffer) - offset - 1);
            if (res) {
                offset += res.bytes();
                buffer[offset] = '\0';
                if (std::strstr(buffer, "aloha")) {
                    break;
                }
            } else if (res.is_disconnected()) {
                throw std::runtime_error("unexpected disconnect");
            } else if (!res.is_again()) {
                throw std::runtime_error("socket recv error <" +
                        std::string(res.str()) + ">");
            }
        }

        std::printf("keyword received\n");

        std::string reply = "jajajajajaa ahhah ah";
        const char* data = reply.c_str();
        size_t size = reply.size();

        while (size > 0) {
            auto res = socket.send(data, size);
            if (res) {
                data += res.bytes();
                size -= res.bytes();
            } else if (res.is_disconnected()) {
                throw std::runtime_error("unexpected disconnect");
            } else if (!res.is_again()) {
                throw std::runtime_error("socket send error <" +
                        std::string(res.str()) + ">");
            }
        }

        socket.close();
        std::printf("done\n");

    } catch (const std::exception& e) {
        std::fprintf(stderr, "error: %s\n", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
