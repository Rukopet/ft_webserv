#ifndef FT_WEBSERVER_SOCKETBASE_HPP
#define FT_WEBSERVER_SOCKETBASE_HPP

#include <sys/event.h>
#include "Request.hpp"

class SocketBase {
public:
	SocketBase(
			int		fd,
			const	std::string &ip_address,
			bool	isMainSocket,
			int		port
			) {

		this->_ip_address = ip_address;
		this->current_request.dropRequest();
		this->_isMainSocket = isMainSocket;
		this->_port = port;
		this->setFd(fd);

	};


	const std::string &getIpAddress() const {
		return _ip_address;
	}

	int getFd() const {
		return _fd;
	}

	void setFd(int fd) {
		_fd = fd;
	}

	void setNonBlockFile();

public:
	Request		current_request;

protected:
	std::string		_ip_address;
	int				_fd;
	int				_port;
	bool 			_isMainSocket;
};


#endif //FT_WEBSERVER_SOCKETBASE_HPP
