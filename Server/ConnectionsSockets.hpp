#ifndef FT_WEBSERVER_CONNECTIONSSOCKETS_HPP
#define FT_WEBSERVER_CONNECTIONSSOCKETS_HPP

#include <map>
#include <vector>
#include "../Client/SocketBase.hpp"
#include "../Client/SocketClient.hpp"
#include "../Client/SocketMain.hpp"
#include "Server.hpp"

struct MapCompare {
	bool operator()(const struct kevent &a, const struct kevent &b) const {
		return a.ident < b.ident;
	};
};


class SocketBase;

class ConnectionsSockets {
public:
	ConnectionsSockets();
	virtual ~ConnectionsSockets();

	void bindSocket(int port);
	void acceptConnection(const struct kevent &current_event);
	void deleteConnection(const struct kevent &current_event);
	bool isMainSocket(const struct kevent &current_event);
	void unbindPorts();

	int getKq() const;
	const std::vector<struct kevent> &getEvents() const;

private:
	std::map<struct kevent, SocketBase, MapCompare>	_connections;
	std::vector<struct kevent>						_all_events;
	int 											_kq;
};



#endif //FT_WEBSERVER_CONNECTIONSSOCKETS_HPP
