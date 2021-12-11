#include "ConnectionsSockets.hpp"
#include "Server.hpp"

ConnectionsSockets::ConnectionsSockets() {}

ConnectionsSockets::~ConnectionsSockets() {
}

void ConnectionsSockets::bindSocket(int port) {
	int m_socket = 0;

	m_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (m_socket == -1) {
		throw Server_start_exception("IN SOCKET INIT: in socket:");
	}

	sockaddr_in sa_server;
	memset(&sa_server, 0, sizeof(sa_server));
	sa_server.sin_addr.s_addr = INADDR_ANY;
	sa_server.sin_family = AF_INET;
	sa_server.sin_port = htons(port);


	// https://www.opennet.ru/docs/RUS/socket/node3.html
	// explain how and why cast sockaddr_in to sockaddr
	if (bind(m_socket, (sockaddr*)&sa_server, sizeof(sa_server)) != 0) {
		throw Server_start_exception("IN SOCKET INIT: in bind func:");
	}

	if (listen(m_socket, MAX_CLIENTS) != 0) {
		throw Server_start_exception("IN SOCKET INIT: in listen func:");
	}
	this->_all_events
	_servers_sockets.push_back(m_socket);

}
