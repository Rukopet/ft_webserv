//
// Created by Piper Leonel on 7/19/21.
//

#include "ServerConfig.hpp"

int ServerConfig::getClientMaxBodySize() const {
	return clientMaxBodySize;
}

std::string ServerConfig::getErrorPage(int error) const {
	return errorPages.at(error);
}

RouteConfig ServerConfig::getRouteConfig(const std::string& route) const {
	return routeConfigs.at(route);
}

ServerConfig::ServerConfig(const std::map<int, std::string> &errorPages, int clientMaxBodySize,
						   const std::map<std::string, RouteConfig> &routeConfigs, int port, const std::string &host,
						   const std::set<std::string> &serverNames) : errorPages(errorPages),
																	   clientMaxBodySize(clientMaxBodySize),
																	   routeConfigs(routeConfigs), port(port),
																	   host(host), serverNames(serverNames) {}

int ServerConfig::getPort() const {
	return port;
}

const std::string &ServerConfig::getHost() const {
	return host;
}

bool ServerConfig::isServerName(const std::string &serverName) const {
	return (serverNames.count(serverName) > 0);
}
