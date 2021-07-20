
#include <string>
#include <fstream>
#include <iostream>
#include "Config.hpp"
#include "Parser.hpp"

Parser *Parser::instance = new Parser();

std::pair<int, std::string> Parser::parseErrorParam(std::ifstream &file) {
	std::pair<int, std::string> errorPage;
	std::string inData;

	if (!(file >> errorPage.first) || !(file >> errorPage.second)) {
		std::cerr << "can't parse error_page" << std::endl;
		exit(-1);
	}
	return (errorPage);
}

int Parser::parseClientMaxBodySize(std::ifstream &file) {
	int clientMaxBodySize;

	if (!(file >> clientMaxBodySize)) {
		std::cerr << "can't parse client_max_body_size" << std::endl;
		exit(-1);
	}
	return (clientMaxBodySize);
}

ServerConfig Parser::parseServer(std::ifstream &file) {
	std::map<int, std::string> errorPages;
	int clientMaxBodySize = 1;
	std::map<std::string, RouteConfig> routeConfigs;
	int port = -1;
	std::string host = "";
	std::set<std::string> serverNames;

	std::string inData;
	file >> inData;
	if (inData != "server" || file.eof()) {
		std::cout << "Wrong data outside server blocks" << std::endl;
		exit(-1);
	} else {
		file >> inData;
		if (inData != "{") {
			std::cout << "{ excepted" << std::endl;
			exit(-1);
		}
		while (!(file >> inData) && inData != "}") {
			if (inData == "error_page") {
				std::pair<int, std::string> errorPage = parseErrorParam(file);
				errorPages[errorPage.first] = errorPage.second;
			} else if (inData == "client_max_body_size") {

			}
			//TODO: parse params
		}
	}
	if (port == -1 || host == "") {
		std::cout << "haven't port or host for server config" << std::endl;
		exit(-1);
	} else if (file.eof()) {
		std::cout << "excepted } for server block" << std::endl;
		exit(-1);
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
