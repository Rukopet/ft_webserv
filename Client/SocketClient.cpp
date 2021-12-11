#include "SocketClient.hpp"

SocketClient::SocketClient(const std::string &ipAddress) : SocketBase(
		ipAddress, false, 0) {}

SocketClient::~SocketClient() {}

