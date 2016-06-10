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
            snet::socket nsock = socket.accept();
            if (nsock) {
                nsock.set_nonblock();
                nsock.set_cloexec();
                nsock.set_tcpnodelay();
                socket = std::move(nsock);
                break;
            }
            if (snet::last_error::interrupted()) {
                throw std::runtime_error("interrupted");
            }
            if (!snet::last_error::again()) {
                throw std::runtime_error("socket error happend <" +
                        std::to_string(snet::last_error::code()) + ">");
            }
        }

        std::printf("peer accepted!\n");

        char buffer[128];
        size_t offset = 0;
        while (true) {
            ssize_t res = socket.recv(buffer + offset, sizeof(buffer) - offset - 1);
            if (res > 0) {
                offset += res;
                buffer[offset] = '\0';
                if (std::strstr(buffer, "aloha")) {
                    break;
                }
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

        std::printf("keyword received\n");

        std::string reply = "jajajajajaa ahhah ah";
        const char* data = reply.c_str();
        size_t size = reply.size();

        while (size > 0) {
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

        socket.close();
        std::printf("done\n");

    } catch (const std::exception& e) {
        std::fprintf(stderr, "error: %s\n", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
