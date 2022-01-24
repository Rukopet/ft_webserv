#include "SocketClient.hpp"

SocketClient::SocketClient(const std::string &ipAddress, int fd) :
SocketBase(fd, ipAddress, false, 0) {}

SocketClient::~SocketClient() {}

void SocketClient::handleConnection() {

}
