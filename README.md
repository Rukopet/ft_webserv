# ft_webserv

void ConnectionsSockets::acceptConnection(const struct kevent &current_event) {
sockaddr_in sa_client;
socklen_t client_len = sizeof(sa_client);

	int client_socket = accept(static_cast<int>(current_event.ident), (sockaddr *) &sa_client,
							   &client_len);
	if (client_socket == -1)
		throw Server_start_exception("In acceptConnection method:");
	std::string client_ip = ServerUtils::_get_ip_address(sa_client);

	SocketClient socket(client_ip, client_socket);

	try {
		socket.setNonBlock();
	}
	catch (std::exception &e) {
		throw Server_start_exception("In setting nonblock fd part\n" + std::string(e.what()));
	}
	this->_all_events.resize(this->_all_events.size() + 1);
	EV_SET(&this->_all_events.back(), client_socket, EVFILT_READ, EV_ADD | EV_ENABLE | EV_EOF, NOTE_WRITE, 0, NULL);
	auto add = std::pair<int, SocketBase>(client_socket, socket);
	this->_connections.insert(add);
}