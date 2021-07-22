//
// Created by Piper Leonel on 7/18/21.
//

#ifndef FT_WEBSERVER_PARSER_HPP
#define FT_WEBSERVER_PARSER_HPP

#include "IParser.hpp"

class Parser : public IParser {
private:
	Parser();
	static Parser* instance;
	ServerConfig parseServer(std::ifstream &file);
	static std::pair<int, std::string> parseErrorParam(std::ifstream &file);
	static std::string parseHost(std::ifstream &file);
	static int parsePort(std::ifstream &file);
	static int parseClientMaxBodySize(std::ifstream &file);
	std::set<std::string> parseServerName(std::ifstream &file);
public:

	static Parser &getInstance();

	virtual Config parseConfig(const std::string &filename);

	std::pair<std::string, RouteConfig> parseRouteConfig(std::ifstream &file);

	std::string parseRedirection(std::ifstream &file);

	std::string parseRoot(std::ifstream &file);

	std::string parseDefaultFile(std::ifstream &file);

	bool parseAutoindex(std::ifstream &file);

	std::set<std::string> parseAllowedMethods(std::ifstream &file);

	std::pair<std::string, std::string> parseCgi(std::ifstream &file);

	std::string parseUploadFilesPath(std::ifstream &file);
};

#endif //FT_WEBSERVER_PARSER_HPP
