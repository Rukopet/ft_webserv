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
#include "ConnectionsSockets.hpp"



class ConnectionsSockets;

class Server {
public:
	Server(Config &conf);
	int start();

private:
	int _socket_init();
	int _core_loop();
	ConnectionsSockets _connections;

private:
	Config &_conf;
};

#endif //PROJECT_NAME_SERVER_HPP
