#ifndef PROJECT_NAME_SERVER_HPP
#define PROJECT_NAME_SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
// for kqueue
#include <sys/event.h>


// for sockaddr_in struct
#include <netinet/in.h>

// for errno and exceptions
#include <cerrno>

#include <set>

#define MAX_CLIENTS 1000

class Server {
public:
	int start();

private:
	int _socket_init();
	int _client_handler(int sock_client, std::string &ip_client);
	int _core_loop();
	int _accept_connection();

private:
	int _m_socket;
	std::set<int> _servers_sockets;
	std::set<int> _connections_sockets;
	struct kevent _monitoring_events;
};

//TODO need fix some features
struct Server_start_exception : public std::exception {
	char *error;
	bool flag_for_errno;
	Server_start_exception(char *err) throw() {
		error = err;
		flag_for_errno = false;
	};
	Server_start_exception(bool err) throw() {
		flag_for_errno = true;
	};
	virtual const char *what() const throw() {
		if (flag_for_errno)
			return std::strerror(errno);
		return error;
	};
};

#endif //PROJECT_NAME_SERVER_HPP
