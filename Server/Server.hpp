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
	int _core_loop();
	ConnectionsSockets _connections;

private:
	std::vector<int> _servers_sockets;
	Config &_conf;
};


// Comparator for Set
//----------------------------------------------------------------------------//
struct SetCompare {
	bool operator()(const struct kevent &a, const struct kevent &b) const {
		return a.ident < b.ident;
	}


//----------------------------------------------------------------------------//

};

#endif //PROJECT_NAME_SERVER_HPP
