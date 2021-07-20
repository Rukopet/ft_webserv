//
// Created by Piper Leonel on 7/18/21.
//

#include "Config.hpp"

#include <utility>

const std::vector<ServerConfig> &Config::getServers(int port) const {
	return servers.at(port);
}

Config::Config(std::map<int, std::vector<ServerConfig>> servers) : servers(std::move(servers)) {}
