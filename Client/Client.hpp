#ifndef FT_WEBSERVER_CLIENT_HPP
#define FT_WEBSERVER_CLIENT_HPP

#include <iostream>
#include "ClientBase.hpp"


class Client : public ClientBase {
public:
	Client(struct kevent *event, const std::string &ipAddress);

	virtual ~Client();
};


#endif //FT_WEBSERVER_CLIENT_HPP
