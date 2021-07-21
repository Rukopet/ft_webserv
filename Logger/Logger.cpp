#include "Logger.hpp"

Logger::Logger() : _log_fd_fstream(Logger::getFilename(), std::fstream::in | std::fstream::out | std::fstream::trunc) {
	const time_t t = time(NULL);
	_log_fd_fstream << std::endl << "\t\t\t\t\t\t" << ctime(&t);
	_log_fd_fstream << "//----------------------------------------------------------------------------//" << std::endl;
}
Logger Logger::instance;

std::string Logger::getFilename() {
	const time_t t = time(NULL);
	std::string folder_name = "logs/";
	std::string filename(folder_name + ctime(&t));
	std::replace(filename.begin(), filename.end(), ' ', '_');
	std::replace(filename.begin(), filename.end(), '\n', '\0');
	return filename;
}

Logger &Logger::getInstance() {
	return instance;
}

Logger::~Logger() {_log_fd_fstream.close(); std::cout << "logger destructor called" << std::endl;}

void Logger::add_line(const std::string &log) {
	_log_fd_fstream << log << std::endl;
	_log_fd_fstream << "//----------------------------------------------------------------------------//" << std::endl;
}