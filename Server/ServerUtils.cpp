#include <arpa/inet.h>
#include "ServerUtils.hpp"


//----------------------------------------------------------------------------//
//for get clients ip addresses
void *ServerUtils::_get_address(sockaddr *sa) {
	if (sa->sa_family == AF_INET)
		return &(((sockaddr_in*)sa)->sin_addr);
	return &(((sockaddr_in6*)sa)->sin6_addr);
}

std::string ServerUtils::_get_ip_address(const sockaddr_in &clientData) {
	char ip[INET6_ADDRSTRLEN];
	memset(&ip, 0, INET6_ADDRSTRLEN);
	inet_ntop(clientData.sin_family, _get_address((sockaddr*)&clientData), ip,
			  sizeof(ip));
	return std::string(ip);
}
//----------------------------------------------------------------------------//