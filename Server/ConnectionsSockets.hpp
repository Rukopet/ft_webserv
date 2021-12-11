#ifndef FT_WEBSERVER_CONNECTIONSSOCKETS_HPP
#define FT_WEBSERVER_CONNECTIONSSOCKETS_HPP

#include <map>
#include <vector>
#include "../Client/SocketBase.hpp"
#include "Server.hpp"

class SocketBase;
struct SetCompare;

class ConnectionsSockets {
public:
	ConnectionsSockets();
	virtual ~ConnectionsSockets();

	void bindSocket(int port);
	void acceptConnections();
	void deleteConnections();
	void unbindPorts();

private:
	std::map<struct kevent, SocketBase, SetCompare>	_connections;
	std::vector<struct kevent>			_all_events;
};


#endif //FT_WEBSERVER_CONNECTIONSSOCKETS_HPP
