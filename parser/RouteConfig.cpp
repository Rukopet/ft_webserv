//
// Created by Piper Leonel on 7/19/21.
//

#include "RouteConfig.hpp"

#include <utility>

RouteConfig::RouteConfig(std::set<std::string> allowedMethods, const std::string &redirection,
						 const std::string &root, bool autoindex, const std::string &defaultFile,
						 const std::pair<std::string, std::string> &cgi) : allowedMethods(std::move(allowedMethods)),
																		   redirection(redirection), root(root),
																		   autoindex(autoindex),
																		   defaultFile(defaultFile), cgi(cgi) {}

const std::set<std::string> &RouteConfig::getAllowedMethods() const {
	return allowedMethods;
}

const std::string &RouteConfig::getRedirection() const {
	return redirection;
}

const std::string &RouteConfig::getRoot() const {
	return root;
}

bool RouteConfig::isAutoindex() const {
	return autoindex;
}

const std::string &RouteConfig::getDefaultFile() const {
	return defaultFile;
}

const std::pair<std::string, std::string> &RouteConfig::getCgi() const {
	return cgi;
}
