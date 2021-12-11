#ifndef FT_WEBSERVER_CLIENTBASE_HPP
#define FT_WEBSERVER_CLIENTBASE_HPP

#include "Request.hpp"

class ClientBase {
public:
	ClientBase() {this->current_request.dropRequest();};
	Request		current_request;

protected:
	std::string _ip_address;
};


#endif //FT_WEBSERVER_CLIENTBASE_HPP
