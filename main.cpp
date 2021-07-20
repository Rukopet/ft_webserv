#include "Server/Server.hpp"
#include "parser/IParser.hpp"
#include "parser/Parser.hpp"

int main() {
	IParser &ok = Parser::getInstance();
	Server b(ok.parseConfig("123"));
	Server s;
	s.start();
}