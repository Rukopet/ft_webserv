//
// Created by Piper Leonel on 7/18/21.
//

#ifndef FT_WEBSERVER_PARSER_HPP
#define FT_WEBSERVER_PARSER_HPP

#include "IParser.hpp"

class Parser : IParser {
private:
	Parser();
	static Parser* instance;
public:
	static Parser &getInstance();
	Config parseConfig(std::string filename) override;

	ServerConfig parseServer(std::ifstream &file);
};

#endif //FT_WEBSERVER_PARSER_HPP
