#include "Server.hpp"

//----------------------------------------------------------------------------//
			//for get clients ip addresses
void *Server::_get_address(sockaddr *sa) {
	if (sa->sa_family == AF_INET)
		return &(((sockaddr_in*)sa)->sin_addr);
	return &(((sockaddr_in6*)sa)->sin6_addr);
}

std::string Server::_get_ip_address(const sockaddr_in &clientData) {
	char ip[INET6_ADDRSTRLEN];
	memset(&ip, 0, INET6_ADDRSTRLEN);
	inet_ntop(clientData.sin_family, _get_address((sockaddr*)&clientData), ip,
			  sizeof(ip));
	return std::string(ip);
}
//----------------------------------------------------------------------------//

Server::Server(Config &conf) : _conf(conf) {}

int Server::_queue_init_set_and_vectors_for_core(
		std::set<struct kevent, SetCompare> &main_sockets,
		std::vector<struct kevent> &monitor_events) {

//	_servers_sockets.push_back(open("123", O_RDONLY));
	_servers_sockets.push_back(_m_socket);
	for (std::vector<int>::iterator it = _servers_sockets.begin(); it != _servers_sockets.end(); ++it) {
		monitor_events.resize(monitor_events.size() + 1);

		//TODO replace this block to the sock init
		// non checked flags on events
		if (fcntl(*it, F_SETFL, O_NONBLOCK) == -1)
			return -1;
		struct kevent *tmp = &monitor_events.back();
		//TODO be care with EV_EOF flag
		EV_SET(tmp, *it, EVFILT_READ, EV_ADD | EV_ENABLE | EV_EOF, NOTE_WRITE, 0,	NULL);
		main_sockets.insert(*tmp);
	}
	return 0;
}

int Server::_queue_fd_add(int new_fd, std::vector<struct kevent> &monitor_events,
						  int kq_fd) {
	EV_SET(&monitor_events.back(), new_fd, EVFILT_READ, EV_ADD | EV_ENABLE, NOTE_WRITE, 0,	NULL);

//	EV_SET(monitor_events.back(), new_fd, EVFILT_VNODE, EV_ADD | EV_CLEAR, NOTE_WRITE, 0,	NULL);

//	int ret = 0;
//	ret = kevent(kq_fd, *(monitor_events.data()), static_cast<int>(monitor_events.size()), NULL, 0, NULL);
//	if (ret == -1)
//		throw Server_start_exception("In _queue_fd_add:");
	return 0;
}

int Server::_accept_connection(const struct kevent &incoming_connection,
							   std::vector<struct kevent> &monitor_events,
							   int kq_fd, std::map<int, sockaddr_in> &clients) {
	sockaddr_in sa_client;
	socklen_t client_len = sizeof(sa_client);
	int client_socket = accept(static_cast<int>(incoming_connection.ident), (sockaddr *) &sa_client,
							   &client_len);
	if (client_socket == -1) {
		throw Server_start_exception("In _accept_connection, ACCEPT:");
	}
	if (fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1) {
		throw Server_start_exception("In _accept_connection, FCNTL:");
	}
	clients[client_socket] = sa_client;
//	TODO need some fixes with del new or replace it on stack values
	monitor_events.resize(monitor_events.size() + 1);
	return client_socket;
}

int Server::_core_loop() {

	//TODO need read some shit about asynchronous, synchronous, nonsynchronous methods accepts
	//TODO need understand where need add fcntl call for nonblock fd

	std::set<struct kevent, SetCompare> main_sockets;
	std::vector<struct kevent> monitor_events;
	std::map<int, sockaddr_in> client_address_for_sock;

	int kq = kqueue();

	if (_queue_init_set_and_vectors_for_core(main_sockets, monitor_events) == -1)
		throw Server_start_exception("In _core_loop, when events being initializing:");




	int ret = 0;

	// for not NULL pointer value in tmp_event_list
	struct kevent *tmp_event_list = &monitor_events[0];

	while (true) {
		ret = kevent(kq, monitor_events.data(), static_cast<int>(monitor_events.size()), NULL, 0, NULL);
		if (ret == -1) {
			throw Server_start_exception("In _core_loop, KEVENT before loop:");
		}

		ret = kevent(kq, NULL, 0, tmp_event_list, 1, NULL);
		if (ret == -1) {
			throw Server_start_exception();
		}

		Logger::getInstance().add_line("NUMBER OF EVENTS: " + std::to_string(ret));
		for (int i = 0; i < ret; ++i) {
			if (main_sockets.count(tmp_event_list[i]) > 0) {
				try {
					int client_socket = _accept_connection(tmp_event_list[i], monitor_events, kq,
									   client_address_for_sock);
					_queue_fd_add(client_socket, monitor_events, kq);
				}
				catch (std::exception &e) {
					std::cerr << e.what() << std::endl;
					continue;
				}
			}

			else {
				int client_socket_fd = static_cast<int>(tmp_event_list[i].ident);
				sockaddr_in sa_client = client_address_for_sock[client_socket_fd];
				std::string client_ip = Server::_get_ip_address(sa_client);
				_client_handler(client_socket_fd, client_ip);
			}

		}

	}
}

int Server::start() {
	try {
		_socket_init();
		std::cout << "Bind sockets successful, server start" << std::endl;
		//TODO this crutch need removed
//		_servers_sockets.push_back(_m_socket);
		_core_loop();
	}
	catch (std::exception &e) {
		std::cerr << "IN START METHOD, IN SERVER: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}


//TODO need replace that crutch for normal config value
#define MAX_BODY_SIZE 1
int Server::_client_handler(int sock_client, std::string &ip_client) {
	static int count_empty_shit = 0;
	int len_buffer = 1048576 * MAX_BODY_SIZE;
	char buffer[len_buffer];
	memset(&buffer, 0, len_buffer);

	int ret = read(sock_client, buffer, len_buffer);
	if (ret == -1) {
		throw Server_start_exception("IN CLIENT HANDLER: while read:");
	}
	buffer[ret] = '\0';

	if (ret != 0) {
		std::cout << buffer << std::endl;
		std::string log = "\nCLIENT IP: ";
		log += ip_client;
		log += "\n\n";
		log += buffer;
		Logger::getInstance().add_line(log);
	}
	else {
		count_empty_shit += 1;
	}
	std::cout << count_empty_shit << std::endl;
	char *asd = "HTTP/1.1 200 OK\n"
				"Content-Encoding: gzip\n"
				"Accept-Ranges: bytes\n"
				"Age: 523659\n"
				"Cache-Control: max-age=604800\n"
				"Content-Type: text/html; charset=UTF-8\n"
				"Date: Wed, 21 Jul 2021 15:14:19 GMT\n"
				"Etag: \"3147526947\"\n"
				"Expires: Wed, 28 Jul 2021 15:14:19 GMT\n"
				"Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT\n"
				"Server: ECS (nyb/1D13)\n"
				"Vary: Accept-Encoding\n"
				"X-Cache: HIT\n"
				"Content-Length: 648\n\n""<!doctype html>\n"
				"<html>\n"
				"<head>\n"
				"    <title>Example Domain</title>\n"
				"\n"
				"    <meta charset=\"utf-8\" />\n"
				"    <meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\" />\n"
				"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\n"
				"    <style type=\"text/css\">\n"
				"    body {\n"
				"        background-color: #f0f0f2;\n"
				"        margin: 0;\n"
				"        padding: 0;\n"
				"        font-family: -apple-system, system-ui, BlinkMacSystemFont, \"Segoe UI\", \"Open Sans\", \"Helvetica Neue\", Helvetica, Arial, sans-serif;\n"
				"        \n"
				"    }\n"
				"    div {\n"
				"        width: 600px;\n"
				"        margin: 5em auto;\n"
				"        padding: 2em;\n"
				"        background-color: #fdfdff;\n"
				"        border-radius: 0.5em;\n"
				"        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);\n"
				"    }\n"
				"    a:link, a:visited {\n"
				"        color: #38488f;\n"
				"        text-decoration: none;\n"
				"    }\n"
				"    @media (max-width: 700px) {\n"
				"        div {\n"
				"            margin: 0 auto;\n"
				"            width: auto;\n"
				"        }\n"
				"    }\n"
				"    </style>    \n"
				"</head>\n"
				"\n"
				"<body>\n"
				"<div>\n"
				"    <h1>Example Domain</h1>\n"
				"    <p>This domain is for use in illustrative examples in documents. You may use this\n"
				"    domain in literature without prior coordination or asking for permission.</p>\n"
				"    <p><a href=\"https://www.iana.org/domains/example\">More information...</a></p>\n"
				"</div>\n"
				"</body>\n"
				"</html>\n\n";
	std::cout << asd << std::endl;
	recv(sock_client, (void*)asd, strlen(asd), 0);
	return count_empty_shit;
}

//TODO need adding port for that, dont know how handle it, i think this after parsing config
#define SOME_PORT 10000

int Server::_socket_init() {
	for (std::set<int>::iterator it = _conf.getPorts().begin(); it != _conf.getPorts().end(); ++it) {

		int m_socket = 0;

		m_socket = socket(PF_INET, SOCK_STREAM, 0);
		if (m_socket == -1) {
			throw Server_start_exception("IN SOCKET INIT: in socket:");
		}
		int port = *it;

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
			_servers_sockets.push_back(m_socket);
		}
	}
		return 0;
}


// inet_adr examples: https://coderoad.ru/5328070/%D0%9A%D0%B0%D0%BA-%D0%BF%D1%80%D0%B5%D0%BE%D0%B1%D1%80%D0%B0%D0%B7%D0%BE%D0%B2%D0%B0%D1%82%D1%8C-%D1%81%D1%82%D1%80%D0%BE%D0%BA%D1%83-%D0%B2-%D0%B0%D0%B4%D1%80%D0%B5%D1%81-IP-%D0%B8-%D0%BD%D0%B0%D0%BE%D0%B1%D0%BE%D1%80%D0%BE%D1%82