#include "Server/Server.hpp"
#include "Logger/Logger.hpp"

int main() {
//	IParser &ok = Parser::getInstance();
//	Server b(ok.parseConfig("123"));
	Server s;
	s.start();
}