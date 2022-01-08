#ifndef FT_WEBSERVER_SOCKETBASE_HPP
#define FT_WEBSERVER_SOCKETBASE_HPP

#include <sys/event.h>
#include <sys/fcntl.h>
#include "Request.hpp"
#include "../Server/Server.hpp"

class SocketBase {
public:
	SocketBase(int		fd,
			const	std::string &ip_address,
			bool	isMainSocket,
			int		port)
			{

		this->_ip_address = ip_address;
		this->current_request.dropRequest();
		this->_isMainSocket = isMainSocket;
		this->_port = port;
		this->_fd = fd;
	};


	const std::string &getIpAddress() const {
		return _ip_address;
	}

	int getFd() const {
		return _fd;
	}

	void setNonBlock() {
		if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
			throw Server_start_exception("IN SOCKET INIT: in fcntl func:");
	};

public:
	Request		current_request;

protected:
	std::string		_ip_address;
	int				_fd;
	bool 			_isMainSocket;
	int				_port;
};


#endif //FT_WEBSERVER_SOCKETBASE_HPP
