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
	static ServerConfig parseServer(std::ifstream &file);
	static std::pair<int, std::string> parseErrorParam(std::ifstream &file);
public:
	static Parser &getInstance();

	Config parseConfig(std::string filename) override;

	static int parseClientMaxBodySize(std::ifstream &file);
};

#endif //FT_WEBSERVER_PARSER_HPP
