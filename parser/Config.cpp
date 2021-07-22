//
// Created by Piper Leonel on 7/18/21.
//

#include "Config.hpp"

#include <utility>

const std::vector<ServerConfig> &Config::getServers(int port) const {
	return servers.at(port);
}

Config::Config(const std::map<int, std::vector<ServerConfig> >& servers,
			   const std::set<int>& ports) : servers(servers),
			   ports(ports) {}

const std::set<int> &Config::getPorts() const {
	return ports;
}
