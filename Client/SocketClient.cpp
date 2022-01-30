#include "SocketClient.hpp"

SocketClient::SocketClient(const std::string &ipAddress, int fd) :
SocketBase(fd, ipAddress, false, 0) {}

SocketClient::~SocketClient() {}

void SocketClient::handleConnection() {
//	TODO fix this hardcode
	const int MAX_BODY_SIZE = 1;
	int len_buffer = 1048576 * MAX_BODY_SIZE;
	char buffer[len_buffer];
	memset(buffer, 0, len_buffer);

	size_t ret = recv(this->getFd(), buffer, len_buffer, 0);
	if (ret == -1) {
		throw Server_start_exception("IN CLIENT HANDLER: while recv:");
	}
	std::cout << 1111 << std::endl;
	buffer[ret] = '\0';

	std::cout << buffer << std::endl;
	std::string log = "\nCLIENT IP: ";
	log += this->getIpAddress();
	log += "\n\n";
	log += buffer;
	Logger::getInstance().add_line(log);

	std::string msg = "Count bytes received: ";
	msg += std::to_string(ret);
	ret = send(this->getFd(), msg.c_str(), msg.size(), 0);
	log = "message to ";
	log += this->getIpAddress();
	log += "with length ";
	log += std::to_string(ret);
	log += "\n\n";
	log += msg;
}
