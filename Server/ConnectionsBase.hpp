#ifndef FT_WEBSERVER_CONNECTIONSBASE_HPP
#define FT_WEBSERVER_CONNECTIONSBASE_HPP

#include <map>
#include "../Client/SocketClient.hpp"

class ConnectionsBase {
public:
	ConnectionsBase() {}


private:
	std::map<struct kevent, SocketClient>	_connections;
};


#endif //FT_WEBSERVER_CONNECTIONSBASE_HPP
