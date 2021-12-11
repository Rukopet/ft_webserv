//
// Created by Piper Leonel on 7/18/21.
//

#ifndef FT_WEBSERVER_IPARSER_HPP
#define FT_WEBSERVER_IPARSER_HPP


#include "Config.hpp"

class IParser {
public:
	virtual Config parseConfig(const std::string &filename) = 0;
};


#endif //FT_WEBSERVER_IPARSER_HPP