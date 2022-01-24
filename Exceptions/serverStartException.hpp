#ifndef FT_WEBSERVER_SERVERSTARTEXCEPTION_HPP
#define FT_WEBSERVER_SERVERSTARTEXCEPTION_HPP


//TODO need fix some feature

// Exception class
//----------------------------------------------------------------------------//

struct Server_start_exception : public std::exception {
	std::string error;
	Server_start_exception(const std::string& err) throw() {
		std::string errno_string = std::strerror(errno);
		error = err + "\t" + errno_string;
	};
	Server_start_exception() throw() {
		error = std::strerror(errno);
	};
	virtual ~Server_start_exception() throw() {};
	virtual const char* what() const throw() {
		return error.c_str();
	};
};

//----------------------------------------------------------------------------//


#endif //FT_WEBSERVER_SERVERSTARTEXCEPTION_HPP
