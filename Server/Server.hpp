#ifndef PROJECT_NAME_SERVER_HPP
#define PROJECT_NAME_SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
// for kqueue
#include <sys/event.h>
#include <sys/fcntl.h>


// for sockaddr_in struct
#include <netinet/in.h>

// for errno and exceptions
#include <cerrno>

#include <set>
#include <vector>

#define MAX_CLIENTS 1000

class Server {
public:
	int start();

private:
	int _socket_init();
	int _client_handler(int sock_client, std::string &ip_client);
	int _core_loop();
	static int _accept_connection(const struct kevent &incoming_connection,
								  std::vector<struct kevent *> &monitor_events,
								  int kq_fd);

	static int
	_queue_fd_add(int new_fd, std::vector<struct kevent *> &monitor_events,
				  int kq_fd);
	int	_queue_fd_remove();
	int _queue_init_set_and_vectors_for_core(std::set<struct kevent *> &, std::vector<struct kevent *> &);
	static bool _queue_check_in(const struct kevent &event,
						 std::set<struct kevent *> &checked);

private:
	int _m_socket;
	std::vector<int> _servers_sockets;
};



//TODO need fix some features
struct Server_start_exception : public std::exception {
	std::string error;

	Server_start_exception(std::string err) throw() {
		std::string errno_string = std::strerror(errno);
		error = err + "\t" + errno_string;
	};
	Server_start_exception() throw() {
		error = std::strerror(errno);
	};
	virtual const char *what() const throw() {
		return error.c_str();
	};

};

#endif //PROJECT_NAME_SERVER_HPP
