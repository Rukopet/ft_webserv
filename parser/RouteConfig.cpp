//
// Created by Piper Leonel on 7/19/21.
//

#include "RouteConfig.hpp"

#include <utility>

RouteConfig::RouteConfig(const std::set<std::string>& allowedMethods, const std::string &redirection,
						 const std::string &root, bool autoindex, const std::string &defaultFile,
						 const std::map<std::string, std::string> &cgi) : allowedMethods(allowedMethods),
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

RouteConfig::RouteConfig() {

}

const std::string &RouteConfig::getCgi(std::string &extension) const {
	return cgi.at(extension);
}

const std::string &RouteConfig::getUploadFilesPath() const {
	return uploadFilesPath;
}

RouteConfig::RouteConfig(const std::string &uploadFilesPath, const std::set<std::string> &allowedMethods,
						 const std::string &redirection, const std::string &root, const std::string &defaultFile,
						 bool autoindex, const std::map<std::string, std::string> &cgi) : uploadFilesPath(
		uploadFilesPath), allowedMethods(allowedMethods), redirection(redirection), root(root),
																						  defaultFile(defaultFile),
																						  autoindex(autoindex),
																						  cgi(cgi) {}
