#include "Server.hpp"

int Server::_queue_init_set_and_vectors_for_core(std::set<struct kevent *> &main_sockets, std::vector<struct kevent *> &monitor_events) {
	for (std::vector<int>::iterator it = _servers_sockets.begin(); it != _servers_sockets.end(); ++it) {
		struct kevent *tmp = new struct kevent;
		main_sockets.insert(tmp);
		monitor_events.insert(monitor_events.begin(), tmp);
		// non checked flags on events
		EV_SET(monitor_events[0], *it, EVFILT_VNODE, EV_ADD | EV_CLEAR, NOTE_WRITE, 0,	NULL);
	}
	return 0;
}

int Server::_core_loop() {

	//TODO need read some shit about asynchronous, synchronous, nonsynchronous methods accepts
	//TODO need understand where need add fcntl call for nonblock fd

	//TODO replace to class member _monitoring_events
	struct kevent monitoring_events;
	struct kevent triggered_events;

	std::set<struct kevent *> main_sockets;
	std::vector<struct kevent *> monitor_events;
	_queue_init_set_and_vectors_for_core(main_sockets, monitor_events);


	while (true) {
		int sock_client;
		sockaddr_in sa_client;
		socklen_t client_len = sizeof(sa_client);

		//TODO before that need epoll event check, now that only prototype (

		// ...epoll code here...

		if (sock_client = accept(_m_socket, (sockaddr*)&sa_client, &client_len) == -1) {
			std::cerr << "ERROR IN ACCEPT";
			continue;
		}
		std::string ip_client = "0"; //some converts with ntohs()
		_client_handler(sock_client, ip_client);
	}
}

int Server::start() {
	try {
		_socket_init();
	}
	catch (std::exception &e) {
		std::cerr << "IN START METHOD, IN SERVER: " << e.what() << std::endl;
		return -1;
	}

	std::cout << "Bind sockets successful, server start" << std::endl;

	//TODO this crutch need removed
	_servers_sockets.push_back(_m_socket);
	_core_loop();

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


// inet_adr examples: https://coderoad.ru/5328070/%D0%9A%D0%B0%D0%BA-%D0%BF%D1%80%D0%B5%D0%BE%D0%B1%D1%80%D0%B0%D0%B7%D0%BE%D0%B2%D0%B0%D1%82%D1%8C-%D1%81%D1%82%D1%80%D0%BE%D0%BA%D1%83-%D0%B2-%D0%B0%D0%B4%D1%80%D0%B5%D1%81-IP-%D0%B8-%D0%BD%D0%B0%D0%BE%D0%B1%D0%BE%D1%80%D0%BE%D1%82