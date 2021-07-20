#include "Server/Server.hpp"
#include "parser/IParser.hpp"
#include "parser/Parser.hpp"

int main() {
	IParser &ok = Parser::getInstance();
	ok.parseConfig();
	Server s;
	s.start();
}