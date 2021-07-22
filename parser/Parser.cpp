
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
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

std::string Parser::parseHost(std::ifstream &file) {
	std::string host;

	if (!(file >> host)) {
		std::cerr << "can't parse host" << std::endl;
		exit(-1);
	}
	return (host);
}

int Parser::parsePort(std::ifstream &file) {
	int port;

	if (!(file >> port)) {
		std::cerr << "can't parse port" << std::endl;
		exit(-1);
	}
	if (port <= 0 || port > 65535) {
		std::cerr << "invalid port range" << std::endl;
		exit(-1);
	}
	return (port);
}

std::set<std::string> Parser::parseServerName(std::ifstream &file) {
	std::set<std::string> serverNames;
	std::string inData;
	std::getline(file, inData);
	std::stringstream inDataStream(inData);
	while (inDataStream >> inData) {
		if (serverNames.count(inData)) {
			std::cerr << "repeated server_name in server_names" << std::endl;
			exit(-1);
		}
		serverNames.insert(inData);
	}
	if (serverNames.empty()) {
		std::cerr << "Empty server_name" << std::endl;
		exit(-1);
	}
	return (serverNames);
}

std::string Parser::parseRedirection(std::ifstream &file) {
	std::string redirection;

	if (!(file >> redirection)) {
		std::cerr << "can't parse redirection" << std::endl;
		exit(-1);
	}
	return (redirection);
}

std::string Parser::parseRoot(std::ifstream &file) {
	std::string root;

	if (!(file >> root)) {
		std::cerr << "can't parse root" << std::endl;
		exit(-1);
	}
	return (root);
}

std::string Parser::parseDefaultFile(std::ifstream &file) {
	std::string defaultFile;

	if (!(file >> defaultFile)) {
		std::cerr << "can't parse default_file" << std::endl;
		exit(-1);
	}
	return (defaultFile);
}

bool Parser::parseAutoindex(std::ifstream &file) {
	std::string inData;

	if (!(file >> inData) || (inData != "on" && inData != "off")) {
		std::cerr << "can't parse autoindex" << std::endl;
		exit(-1);
	}
	return inData == "on";
}

std::set<std::string> Parser::parseAllowedMethods(std::ifstream &file) {
	std::set<std::string> allowedMethods;
	std::string inData;
	std::getline(file, inData);
	std::stringstream inDataStream(inData);
	while (inDataStream >> inData) {
		if (allowedMethods.count(inData)) {
			std::cerr << "repeated method in methods" << std::endl;
			exit(-1);
		}
		std::string tmp[] = {"get", "GET", "post", "POST", "DELETE", "delete", "PUT", "put"};
		std::set<std::string> supportedMethods(tmp, tmp + sizeof(tmp) / sizeof (tmp[0]));
		if (supportedMethods.count(inData) == 0) {
			std::cerr << "not supported method in methods" << std::endl;
			exit(-1);
		}
		allowedMethods.insert(inData);
	}
	if (allowedMethods.empty()) {
		std::cerr << "Empty methods" << std::endl;
		exit(-1);
	}
	return (allowedMethods);
}

std::pair<std::string, std::string> Parser::parseCgi(std::ifstream &file) {
	std::pair<std::string, std::string> cgi;
	std::string inData;

	if (!(file >> cgi.first) || !(file >> cgi.second)) {
		std::cerr << "can't parse error_page" << std::endl;
		exit(-1);
	}
	return (cgi);
}

std::string Parser::parseUploadFilesPath(std::ifstream &file) {
	std::string path;

	if (!(file >> path)) {
		std::cerr << "can't parse upload_files_path" << std::endl;
		exit(-1);
	}
	return (path);
}

std::pair<std::string, RouteConfig> Parser::parseRouteConfig(std::ifstream &file) {
	std::string location;
	std::string redirection;
	std::string root;
	bool autoindex = false;
	std::string defaultFile;
	std::string uploadFilesPath;
	std::set<std::string> allowedMethods;
	std::map<std::string, std::string> cgi;

	std::string inData;
	if (!(file >> inData)) {
		std::cerr << "excepted location for location block" << std::endl;
		exit(-1);
	}
	location = inData;
	if (!(file >> inData) || inData != "{") {
		std::cerr << "excepted { for location block" << std::endl;
		exit(-1);
	}
	while (!(file >> inData) || inData != "}") {
		if (inData == "redirection") {
			if (!redirection.empty()) {
				std::cerr << "redirection repeat" << std::endl;
				exit(-1);
			}
			redirection = parseRedirection(file);
		} else if (inData == "root") {
			if (!root.empty()) {
				std::cerr << "root repeat" << std::endl;
				exit(-1);
			}
			root = parseRoot(file);
		} else if (inData == "default_file") {
			if (!defaultFile.empty()) {
				std::cerr << "default_file repeat" << std::endl;
				exit(-1);
			}
			defaultFile = parseDefaultFile(file);
		} else if (inData == "autoindex") {
			autoindex = parseAutoindex(file);
		} else if (inData == "methods") {
			if (!allowedMethods.empty()) {
				std::cerr << "methods repeat" << std::endl;
				exit(-1);
			}
			allowedMethods = parseAllowedMethods(file);
		} else if (inData == "cgi") {
			std::pair<std::string, std::string> cgiPair = parseCgi(file);
			if (cgi.find(cgiPair.first) != cgi.end()) {
				std::cerr << "error_page with " << cgiPair.first << " code repeated" << std::endl;
				exit(-1);
			}
			cgi[cgiPair.first] = cgiPair.second;
		} else if (inData == "upload_files_path") {
			if (!uploadFilesPath.empty()) {
				std::cerr << "upload_files_path repeat" << std::endl;
				exit(-1);
			}
			uploadFilesPath = parseUploadFilesPath(file);
		}
	}
	if (file.eof() || inData != "}") {
		std::cout << "excepted } for location block" << std::endl;
		exit(-1);
	}
	return (std::pair<std::string, RouteConfig>(location, RouteConfig(uploadFilesPath, allowedMethods, redirection, root, defaultFile, autoindex, cgi)));
}

ServerConfig Parser::parseServer(std::ifstream &file) {
	std::map<int, std::string> errorPages;
	int clientMaxBodySize = -1;
	std::map<std::string, RouteConfig> routeConfigs;
	int port = -1;
	std::string host;
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
		while (!(file >> inData) || inData != "}") {
			if (inData == "error_page") {
				std::pair<int, std::string> errorPage = parseErrorParam(file);
				if (errorPages.find(errorPage.first) != errorPages.end()) {
					std::cerr << "error_page with " << errorPage.first << " code repeated" << std::endl;
					exit(-1);
				}
				errorPages[errorPage.first] = errorPage.second;
			} else if (inData == "client_max_body_size") {
				if (clientMaxBodySize != -1) {
					std::cerr << "client_max_body_size repeated" << std::endl;
					exit(-1);
				}
				clientMaxBodySize = parseClientMaxBodySize(file);
			} else if (inData == "host") {
				if (!host.empty()) {
					std::cerr << "host repeated" << std::endl;
					exit(-1);
				}
				host = parseHost(file);
			} else if (inData == "listen") {
				if (port != -1) {
					std::cerr << "port repeated" << std::endl;
					exit(-1);
				}
				port = parsePort(file);
			} else if (inData == "location") {
				std::pair<std::string, RouteConfig> routeConfig = parseRouteConfig(file);
				if (routeConfigs.find(routeConfig.first) != routeConfigs.end()) {
					std::cerr << "repeated location " + routeConfig.first << " rule for the one server" << std::endl;
					exit(-1);
				}
				routeConfigs[routeConfig.first] = routeConfig.second;
			} else if (inData == "server_name") {
				if (!serverNames.empty()) {
					std::cerr << "repeated server_name in the one server" << std::endl;
					exit(-1);
				}
				serverNames = parseServerName(file);
			}
			else {
				std::cerr << "Wrong data inside server block" << std::endl;
				exit(-1);
			}
		}
	}
	if (port == -1 || host.empty()) {
		std::cout << "haven't port or host for server config" << std::endl;
		exit(-1);
	} else if (file.eof() && inData != "}") {
		std::cout << "excepted } for server block" << std::endl;
		exit(-1);
	}
	return ServerConfig(errorPages,
						clientMaxBodySize == -1 ? 1 : clientMaxBodySize,
						routeConfigs, port, host, serverNames);
}

Config Parser::parseConfig(const std::string &filename) {
	std::ifstream file(filename);
	std::map<int, std::vector<ServerConfig> > servers;
	std::set<int> ports;

	while (!file.eof()) {
		ServerConfig serverConfig = parseServer(file);
		servers[serverConfig.getPort()].push_back(serverConfig);
		ports.insert(serverConfig.getPort());
	}
	file.close();
	return Config(servers, ports);
}

Parser &Parser::getInstance() {
	return *instance;
}

Parser::Parser() {}

