#ifndef FT_WEBSERVER_LOGGER_HPP
#define FT_WEBSERVER_LOGGER_HPP

#include <fstream>
#include <iostream>
#include <ctime>

class Logger {
private:
	Logger();
	static Logger *instance;
	std::fstream _log_fd_fstream;
	static std::string getFilename();

public:
	void add_line(const std::string &) ;
	static Logger &getInstance();
	virtual ~Logger();
};


#endif //FT_WEBSERVER_LOGGER_HPP
