#include "../../includes/Server/Socket.hpp"

using namespace ZappyGui;

Socket::Socket(): _socket(-1) {}

Socket::Socket(const std::string &ip, uint16_t port): _socket(-1) {
    connect(ip, port);
}

Socket::Socket(Socket &&other): _socket(other._socket) {
    other._socket = -1;
}

Socket::~Socket() {
    close();
}

Socket &Socket::operator=(Socket &&other)
{
    _socket = other._socket;
    other._socket = -1;
    return *this;
}

Socket &Socket::operator<<(const std::string &str)
{
    write(str);
    return *this;
}

Socket &Socket::operator>>(std::string &str)
{
    str = read();
    return *this;
}

void Socket::connect(const std::string &ip, uint16_t port)
{
    if (_socket == -1)
        close();
    _socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
        throw Error("Socket creation failed.");

    struct sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port);
    myaddr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (::connect(_socket, (struct sockaddr *)&myaddr, sizeof(struct sockaddr_in)) < 0)
        throw Error("Socket connection failed: " + std::string(strerror(errno)));
}

void Socket::close()
{
    ::close(_socket);
    _socket = -1;
}

void Socket::write(const std::string &str)
{
    if (_socket == -1)
        throw Error("Socket is not open.", "Socket::write");
    if (::write(_socket, str.c_str(), str.size()) == -1)
        throw Error("Socket write failed: " + std::string(strerror(errno)), "Socket::write");
}

std::string Socket::read()
{
    if (_socket == -1)
        throw Error("Socket is not open.", "Socket::read");
    char buffer[4096];
    ssize_t size = ::read(_socket, buffer, 4096);
    if (size == 0)
        throw Info("Socket closed.", "Socket::read");
    if (size == -1)
        throw Error("Socket read failed: " + std::string(strerror(errno)), "Socket::read");
    return std::string(buffer, size);
}

bool Socket::tryRead(std::string &res) const
{
    if (_socket == -1)
        throw Error("Socket is not open.", "Socket::read");
    fd_set readfds;
    struct timeval tv = {0, 0};
    FD_ZERO(&readfds);
    FD_SET(_socket, &readfds);
    if (::select(_socket + 1, &readfds, NULL, NULL, &tv) == -1)
        throw Error("Socket select failed: " + std::string(strerror(errno)), "Socket::read");
    if (!FD_ISSET(_socket, &readfds))
        return false;
    char buffer[4096];
    ssize_t size = ::read(_socket, buffer, 4096);
    if (size == 0)
        throw Info("Socket closed.", "Socket::read");
    if (size == -1)
        throw Error("Socket read failed: " + std::string(strerror(errno)), "Socket::read");
    res = std::string(buffer, size);
    return true;
}
