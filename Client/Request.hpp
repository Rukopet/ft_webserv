#ifndef FT_WEBSERVER_REQUEST_HPP
#define FT_WEBSERVER_REQUEST_HPP

#include <iostream>
#include "RequestBase.hpp"

class Request : public RequestBase {
public:
	Request();

	void dropRequest();


};


#endif //FT_WEBSERVER_REQUEST_HPP
