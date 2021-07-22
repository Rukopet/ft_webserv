#include "Server/Server.hpp"
#include "Logger/Logger.hpp"
#include "parser/IParser.hpp"
#include "parser/Parser.hpp"

int main(int argc, char **argv) {
	if (argc > 2) {
		std::cerr << "Invalid arguments count" << std::endl;
		return -1;
	}
	IParser &ok = Parser::getInstance();
	std::string configPath = "config_examples/test_config";
	if (argc == 2) {
		configPath = argv[1];
	}
	Config config = ok.parseConfig(configPath);
	Server b(config);
	b.start();
	return 0;
}