#ifndef FT_WEBSERVER_SOCKETMAIN_HPP
#define FT_WEBSERVER_SOCKETMAIN_HPP

#include <iostream>
#include "SocketBase.hpp"

class SocketMain : public SocketBase {
public:
	SocketMain(int port, int fd);

private:
	int		_maxClients;
};


#endif //FT_WEBSERVER_SOCKETMAIN_HPP
