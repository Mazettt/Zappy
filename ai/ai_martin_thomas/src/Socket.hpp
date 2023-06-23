#pragma once

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "MyError.hpp"

namespace my {
    class Socket {
        public:
            class Error: public MyError {
                public:
                    Error(const std::string &message, const std::string &className = "Socket"): MyError(className, message, true, "ERROR") {}
            };
            class Warning: public MyError {
                public:
                    Warning(const std::string &message, const std::string &className = "Socket"): MyError(className, message, true, "WARN") {}
            };
            class Info: public MyError {
                public:
                    Info(const std::string &message, const std::string &className = "Socket"): MyError(className, message, false, "INFO") {}
            };

            Socket();
            Socket(const std::string &ip, uint16_t port);
            Socket(const Socket &other) = delete;
            Socket(Socket &&other);
            ~Socket();

            Socket &operator=(const Socket &other) = delete;
            Socket &operator=(Socket &&other);

            Socket &operator<<(const std::string &str);
            Socket &operator>>(std::string &str);

            void connect(const std::string &ip, uint16_t port);
            void close();
            void write(const std::string &str);
            std::string read();
            bool tryRead(std::string &res) const;

        private:
            int _socket;
    };
}
