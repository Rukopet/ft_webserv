#ifndef FT_WEBSERVER_CONNECTIONSBASE_HPP
#define FT_WEBSERVER_CONNECTIONSBASE_HPP

#include <map>
#include "../Client/Client.hpp"

class ConnectionsBase {
public:
	ConnectionsBase() {}


private:
	std::map<struct kevent, Client>	_connections;
};


#endif //FT_WEBSERVER_CONNECTIONSBASE_HPP
