#ifndef PROJECT_NAME_SERVER_HPP
#define PROJECT_NAME_SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

// for kqueue
#include <sys/event.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>

// for sockaddr_in struct
#include <netinet/in.h>

// for errno and exceptions
#include <cerrno>

#include <set>
#include <vector>
#include <map>
#include "../parser/Config.hpp"
#include "../Logger/Logger.hpp"
#include "ServerUtils.hpp"
#include "ConnectionsSockets.hpp"

struct SetCompare;

#define MAX_CLIENTS 1000

class Server {
public:
	Server(Config &conf);
	int start();

private:
	int _socket_init();
	int _client_handler(int sock_client, std::string &ip_client);
	int _core_loop();

	ConnectionsSockets _connections;
	static int _accept_connection(const struct kevent &incoming_connection,
								  std::vector<struct kevent> &monitor_events,
								  int kq_fd,
								  std::map<int, sockaddr_in> &clients);

	static int _queue_fd_add(int new_fd,
							 std::vector<struct kevent> &monitor_events,
							 int kq_fd);
	int	_queue_fd_remove();
	int _queue_init_set_and_vectors_for_core(
			std::set<struct kevent, SetCompare> &main_sockets, std::vector<struct kevent> &monitor_events);

private:
	std::vector<int> _servers_sockets;
	Config &_conf;
};



//TODO need fix some feature

// Exception class
//----------------------------------------------------------------------------//
struct Server_start_exception : public std::exception {
	std::string error;
	Server_start_exception(const std::string& err) throw() {
		std::string errno_string = std::strerror(errno);
		error = err + "\t" + errno_string;
	};
	Server_start_exception() throw() {
		error = std::strerror(errno);
	};
	virtual ~Server_start_exception() throw() {};
	virtual const char* what() const throw() {
		return error.c_str();
	};
};
//----------------------------------------------------------------------------//



// Comparator for Set
//----------------------------------------------------------------------------//
struct SetCompare {
	bool operator()(const struct kevent &a, const struct kevent &b) const {
		return a.ident < b.ident;
	}


//----------------------------------------------------------------------------//

};

#endif //PROJECT_NAME_SERVER_HPP
