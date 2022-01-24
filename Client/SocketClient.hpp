#ifndef FT_WEBSERVER_SOCKETCLIENT_HPP
#define FT_WEBSERVER_SOCKETCLIENT_HPP

#include <iostream>
#include <sys/socket.h>



#include "SocketBase.hpp"
#include "../Logger/Logger.hpp"




class SocketClient : public SocketBase {
public:

	SocketClient(const std::string &ipAddress, int fd);
	void handleConnection();

	virtual ~SocketClient();
};


#endif //FT_WEBSERVER_SOCKETCLIENT_HPP
