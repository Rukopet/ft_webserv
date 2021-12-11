#include "SocketMain.hpp"

SocketMain::SocketMain(int port, int fd) :
SocketBase(fd, "0.0.0.0", true, port), _maxClients(1000) {}
