//
// Created by Piper Leonel on 7/18/21.
//

#ifndef FT_WEBSERVER_CONFIG_HPP
#define FT_WEBSERVER_CONFIG_HPP


#include "ServerConfig.hpp"
#include <vector>
#include <map>

class Config {
private:
	std::map<int, std::vector<ServerConfig>> servers;
	std::vector<int> ports;
public:
	Config(std::map<int, std::vector<ServerConfig>> servers, std::vector<int> ports);
	const std::vector<int> &getPorts() const;
	const std::vector<ServerConfig> &getServers(int port) const;
};

#endif //FT_WEBSERVER_CONFIG_HPP
