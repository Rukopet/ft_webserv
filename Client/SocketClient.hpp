#ifndef FT_WEBSERVER_SOCKETCLIENT_HPP
#define FT_WEBSERVER_SOCKETCLIENT_HPP

#include <iostream>
#include "SocketBase.hpp"


class SocketClient : public SocketBase {
public:

	SocketClient(const std::string &ipAddress, bool isMainSocket);

	virtual ~SocketClient();
};


#endif //FT_WEBSERVER_SOCKETCLIENT_HPP
