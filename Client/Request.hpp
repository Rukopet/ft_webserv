#ifndef FT_WEBSERVER_REQUEST_HPP
#define FT_WEBSERVER_REQUEST_HPP

#include <iostream>
#include "IRequest.hpp"

class Request : public IRequest {
public:
	Request();

	void dropRequest();


};


#endif //FT_WEBSERVER_REQUEST_HPP
