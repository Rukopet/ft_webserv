#include "SocketClient.hpp"

SocketClient::SocketClient(const std::string &ipAddress, bool isMainSocket) : SocketBase(
		ipAddress, isMainSocket) {}

SocketClient::~SocketClient() {}

