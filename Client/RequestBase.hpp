#ifndef FT_WEBSERVER_REQUESTBASE_HPP
#define FT_WEBSERVER_REQUESTBASE_HPP

#include <iostream>

class RequestBase {
protected:
	std::string _request;

public:
	RequestBase() {}

	const std::string &getRequest() const {
		return _request;
	}

	bool isEmpty() const {
		return _request.empty();
	}

	virtual void dropRequest() = 0;

	RequestBase &operator+=(const RequestBase &rhs) {
		this->_request += rhs._request;
		return *this;
	}
	RequestBase &operator+=(const char *rhs) {
		this->_request += rhs;
		return *this;
	}
	RequestBase &operator+=(const std::string &rhs) {
		this->_request += rhs;
		return *this;
	}
};


#endif //FT_WEBSERVER_REQUESTBASE_HPP
