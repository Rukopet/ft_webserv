#ifndef FT_WEBSERVER_IREQUEST_HPP
#define FT_WEBSERVER_IREQUEST_HPP

#include <iostream>

class IRequest {
protected:
	std::string _request;

public:
	IRequest() {}

	const std::string &getRequest() const {
		return _request;
	}

	bool isEmpty() const {
		return _request.empty();
	}

	virtual void dropRequest() = 0;

	IRequest &operator+=(const IRequest &rhs) {
		this->_request += rhs._request;
		return *this;
	}
	IRequest &operator+=(const char *rhs) {
		this->_request += rhs;
		return *this;
	}
	IRequest &operator+=(const std::string &rhs) {
		this->_request += rhs;
		return *this;
	}
};


#endif //FT_WEBSERVER_IREQUEST_HPP
