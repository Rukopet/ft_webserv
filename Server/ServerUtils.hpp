#ifndef FT_WEBSERVER_SERVERUTILS_HPP
#define FT_WEBSERVER_SERVERUTILS_HPP

#include <iostream>
#include <netinet/in.h>

class ServerUtils {
public:
	static std::string	_get_ip_address(const sockaddr_in &clientData);
	static void* 		_get_address(sockaddr *sa);
};


#endif //FT_WEBSERVER_SERVERUTILS_HPP
