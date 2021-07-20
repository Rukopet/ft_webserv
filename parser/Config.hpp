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
	std::map<int, std::vector<ServerConfig> > servers;
	std::set<int> ports;
public:
	Config(const std::map<int, std::vector<ServerConfig> >& servers, const std::set<int>& ports);
	const std::set<int> &getPorts() const;
	const std::vector<ServerConfig> &getServers(int port) const;
};

#endif //FT_WEBSERVER_CONFIG_HPP
