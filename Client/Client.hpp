#ifndef FT_WEBSERVER_CLIENT_HPP
#define FT_WEBSERVER_CLIENT_HPP

#include <iostream>

class Client {
public:
	Client();
	virtual ~Client();

private:
	std::string _ip_address;
	std::string _current_request;
};


#endif //FT_WEBSERVER_CLIENT_HPP
