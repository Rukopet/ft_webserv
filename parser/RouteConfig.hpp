//
// Created by Piper Leonel on 7/19/21.
//

#ifndef FT_WEBSERVER_ROUTECONFIG_HPP
#define FT_WEBSERVER_ROUTECONFIG_HPP


#include <set>
#include <string>
#include <map>

class RouteConfig {
public:
	RouteConfig(const std::set<std::string>& allowedMethods, const std::string &redirection, const std::string &root,
				bool autoindex, const std::string &defaultFile, const std::map<std::string, std::string> &cgi);
	RouteConfig();

	RouteConfig(const std::string &uploadFilesPath, const std::set<std::string> &allowedMethods,
				const std::string &redirection, const std::string &root, const std::string &defaultFile, bool autoindex,
				const std::map<std::string, std::string> &cgi);

	const std::set<std::string> &getAllowedMethods() const;

	const std::string &getRedirection() const;

	const std::string &getRoot() const;

	bool isAutoindex() const;

	const std::string &getDefaultFile() const;

	const std::string &getCgi(std::string &extension) const;

	const std::string &getUploadFilesPath() const;

private:
	std::string uploadFilesPath;
	std::set<std::string> allowedMethods;
	std::string redirection;
	std::string root;
	std::string defaultFile;
	bool autoindex;
	std::map<std::string, std::string> cgi;
};


#endif //FT_WEBSERVER_ROUTECONFIG_HPP
