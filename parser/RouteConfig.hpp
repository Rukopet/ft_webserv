//
// Created by Piper Leonel on 7/19/21.
//

#ifndef FT_WEBSERVER_ROUTECONFIG_HPP
#define FT_WEBSERVER_ROUTECONFIG_HPP


#include <set>
#include <string>

class RouteConfig {
public:
	RouteConfig(std::set<std::string> allowedMethods, const std::string &redirection, const std::string &root,
				bool autoindex, const std::string &defaultFile, const std::pair<std::string, std::string> &cgi);

	const std::set<std::string> &getAllowedMethods() const;

	const std::string &getRedirection() const;

	const std::string &getRoot() const;

	bool isAutoindex() const;

	const std::string &getDefaultFile() const;

	const std::pair<std::string, std::string> &getCgi() const;

private:
	std::set<std::string> allowedMethods;
	std::string redirection;
	std::string root;
	bool autoindex;
	std::string defaultFile;
	std::pair<std::string, std::string> cgi;
};


#endif //FT_WEBSERVER_ROUTECONFIG_HPP
