
#include <string>
#include <fstream>
#include <iostream>
#include "Config.hpp"
#include "Parser.hpp"

Parser *Parser::instance = new Parser();

ServerConfig Parser::parseServer(std::ifstream &file) {
	std::map<int, std::string> errorPages;
	int clientMaxBodySize = 1;
	std::map<std::string, RouteConfig> routeConfigs;
	int port = 80;
	std::string host;
	std::set<std::string> serverNames;

	std::string inData;
	file >> inData;
	if (inData != "server") {
		std::cout << "Wrong data outside server blocks" << std::endl;
		exit(-1);
	} else {
		file >> inData;
		if (inData != "{") {
			std::cout << "{ excepted" << std::endl;
			exit(-1);
		}
		//TODO: parse params while inData != "}", if EOF or haven't host/port - exit(-1)
	}
	return ServerConfig(errorPages, clientMaxBodySize, routeConfigs, port, host, serverNames);
}

Config Parser::parseConfig(std::string filename) {
	std::ifstream file(filename);
	std::map<int, std::vector<ServerConfig>> servers;
	while (!file.eof()) {
		ServerConfig serverConfig = parseServer(file);
		servers[serverConfig.getPort()].push_back(serverConfig);
	}
	file.close();
	return Config(servers);
}

Parser &Parser::getInstance() {
	return *instance;
}

Parser::Parser() = default;
