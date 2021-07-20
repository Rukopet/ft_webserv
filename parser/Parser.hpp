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
public:
	static Parser &getInstance();
	virtual Config parseConfig(std::string &filename);

	ServerConfig parseServer(std::ifstream &file);
};

#endif //FT_WEBSERVER_PARSER_HPP
