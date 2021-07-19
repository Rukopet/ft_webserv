//
// Created by Piper Leonel on 7/19/21.
//

#ifndef FT_WEBSERVER_SERVERCONFIG_HPP
#define FT_WEBSERVER_SERVERCONFIG_HPP


#include <map>
#include <string>
#include "RouteConfig.hpp"

class ServerConfig {
private:
	std::map<int, std::string> errorPages;
	int clientMaxBodySize = 1;
	std::map<std::string, RouteConfig> routeConfigs;
	int port;
	std::string host;
	std::set<std::string> serverNames;
public:
	ServerConfig(const std::map<int, std::string> &errorPages, int clientMaxBodySize,
				 const std::map<std::string, RouteConfig> &routeConfigs, int port, const std::string &host,
				 const std::set<std::string> &serverNames);

	std::string getErrorPage(int) const;
	int getClientMaxBodySize() const;
	RouteConfig getRouteConfig(const std::string&) const;
	int getPort() const;
	const std::string &getHost() const;
	bool isServerName(const std::string&) const;
};


#endif //FT_WEBSERVER_SERVERCONFIG_HPP
