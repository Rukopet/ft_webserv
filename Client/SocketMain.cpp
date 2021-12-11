#include "SocketMain.hpp"

SocketMain::SocketMain(int port) :	SocketBase("0.0.0.0", true, port),
									_maxClients(1000) {}
