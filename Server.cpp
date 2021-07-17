#include "Server.hpp"

int Server::start() {
	try {
		_socket_init();
	}
	catch (Server_start_exception &e) {
		std::cerr << "IN START METHOD, IN SERVER: " << e.what() << std::endl;
		return -1;
	}
	catch (std::exception &e) {
		std::cerr << "IN START METHOD, IN SERVER: " << e.what() << std::endl;
		return -1;
	}

	std::cout << "Bind sockets successful, server start" << std::endl;

	//TODO need read some shit about asynchronous, synchronous, nonsynchronous methods accepts
	while (true) {
		int sock_client;
		sockaddr_in sa_client;
		socklen_t client_len = sizeof(sa_client);

		if (sock_client = accept(_m_socket, (sockaddr*)&sa_client, &client_len) == -1) {
			std::cerr << "ERROR IN ACCEPT";
			continue;
		}
//		std::string ip =
	}
	return 0;
}

int Server::_client_handler(int sock_client, std::string &ip_client) {
	return 0;
}

//TODO need adding port for that, dont know how handle it, i think this after parsing config
#define SOME_PORT 10000

int Server::_socket_init() {
	_m_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (_m_socket == -1) {
		throw Server_start_exception(true);
	}

	sockaddr_in sa_server {0};
	sa_server.sin_addr.s_addr = INADDR_ANY;
	sa_server.sin_family = AF_INET;
	sa_server.sin_port = htons(SOME_PORT);


	// https://www.opennet.ru/docs/RUS/socket/node3.html
	// explain how and why cast sockaddr_in to sockaddr
	if (bind(_m_socket, (sockaddr*)&sa_server, sizeof(sa_server)) != 0) {
		throw Server_start_exception(true);
	}

	if (listen(_m_socket, MAX_CLIENTS) != 0) {
		throw Server_start_exception(true);
	}
	return 0;
}


