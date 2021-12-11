#include "Client.hpp"

Client::Client(struct kevent *event, const std::string &ipAddress) :
		ClientBase(event,
		ipAddress) {};

Client::~Client() {}

