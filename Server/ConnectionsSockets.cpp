#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ServerUtils.hpp"
#include "ConnectionsSockets.hpp"

ConnectionsSockets::ConnectionsSockets() : _kq(kqueue()) {}

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

	this->_all_events.resize(this->_all_events.size() + 1);
	struct kevent *tmp_event = &this->_all_events.back();
	EV_SET(tmp_event, m_socket, EVFILT_READ, EV_ADD | EV_ENABLE | EV_EOF, NOTE_WRITE, 0, NULL);

	SocketMain	socket(port, m_socket);
	socket.setNonBlock();

	this->_connections.insert(this->_connections.begin(),
			std::pair<struct kevent, SocketBase>(
					*tmp_event, socket));
	this->_all_events.push_back(*tmp_event);
}


void ConnectionsSockets::acceptConnection(const struct kevent &current_event) {
	sockaddr_in sa_client;
	socklen_t client_len = sizeof(sa_client);

	int client_socket = accept(static_cast<int>(current_event.ident), (sockaddr *) &sa_client,
							   &client_len);
	if (client_socket == -1)
		throw Server_start_exception("In acceptConnection method:");
	std::string client_ip = ServerUtils::_get_ip_address(sa_client);
	SocketClient socket(client_ip, client_socket);

	try {
		socket.setNonBlock();
	}
	catch (std::exception &e) {
		throw Server_start_exception("In setting nonblock fd part\n" + std::string(e.what()));
	}
	this->_all_events.resize(this->_all_events.size() + 1);
	this->_all_events.push_back(current_event);
	this->_connections.insert(std::pair<struct kevent, SocketBase>(current_event, socket));
}


void ConnectionsSockets::deleteConnection(const struct kevent &current_event) {
	std::vector<struct kevent>::iterator search_result_vector;
	try {
		search_result_vector = std::find(this->_all_events.begin(), this->_all_events.end(), current_event);
	}
	catch (std::exception &e) {
		throw e;
	}

	if (search_result_vector == this->_all_events.end()) {
		throw Server_start_exception("Not found kevent in deleteConnection");
	}
	this->_all_events.erase(search_result_vector);

	std::map<struct kevent, SocketBase, MapCompare>::iterator search_result_map;
	try {
		search_result_map = this->_connections.find(current_event);
	}
	catch (std::exception &e) {
		throw e;
	}

	this->_connections.erase(search_result_map);
	close(search_result_map->second.getFd());
}

int ConnectionsSockets::getKq() const {
	return _kq;
}

const std::vector<struct kevent> &ConnectionsSockets::getEvents() const {
	return _all_events;
}

bool ConnectionsSockets::isMainSocket(const struct kevent &current_event) {

	std::map<struct kevent, SocketBase, MapCompare>::iterator search_result_map;
	search_result_map = this->_connections.find(current_event);
	return search_result_map->second.isIsMainSocket();
}

//const SocketClient &
//ConnectionsSockets::getConnection(const struct kevent &current_event) {
//	this->_connections[current_event]
//}
