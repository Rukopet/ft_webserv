#ifndef FT_WEBSERVER_CLIENTBASE_HPP
#define FT_WEBSERVER_CLIENTBASE_HPP

#include <sys/event.h>
#include "Request.hpp"

class ClientBase {
public:
	ClientBase(struct kevent *event, const std::string &ip_address) {
		this->_event = event;
		this->_ip_address = ip_address;
		this->current_request.dropRequest();
	};

	Request		current_request;

	const std::string &getIpAddress() const {
		return _ip_address;
	}

	struct kevent *getEvent() const {
		return _event;
	}

protected:
	std::string _ip_address;
	struct kevent *_event;
};


#endif //FT_WEBSERVER_CLIENTBASE_HPP
