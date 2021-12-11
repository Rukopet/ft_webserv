#include <gtest/gtest.h>
#include <netinet/in.h>
#include "../Client/Request.hpp"
#include "../Client/Client.hpp"
#include "../Server/Server.hpp"

class ClientRequestFixture : public ::testing::Test {

protected:
	virtual void TearDown() {
		delete testRequest;
		delete equality;
		delete equality2;
	}

	virtual void SetUp() {
		event = new (struct kevent){
			.ident = 6,
			.filter = -1,
			.flags = 5,
			.fflags = 0,
			.data = 771,
			.udata = NULL
			};
//		ident = {uintptr_t} 6
//		filter = {int16_t} -1
//		flags = {uint16_t} 5
//		fflags = {uint32_t} 0
//		data = {intptr_t} 711
//		udata = {void * | 0x0} NULL


		sa_client = new (sockaddr_in) {
			.sin_len = 16,
			.sin_family = 2,
			.sin_port = 9983,
			.sin_addr = {16777343},
			.sin_zero = {0,0,0,0,0,0,0,0},
			};
//		sa_client = {sockaddr_in}
//		sin_len = {__uint8_t} 16 '\x10'
//		sin_family = {sa_family_t} 2 '\x02'
//		sin_port = {in_port_t} 9983
//		sin_addr = {in_addr}
//		s_addr = {in_addr_t} 16777343
//		sin_zero = {char [8]} ""
//		[0] = {char} 0 '\0'
//		[1] = {char} 0 '\0'
//		[2] = {char} 0 '\0'
//		[3] = {char} 0 '\0'
//		[4] = {char} 0 '\0'
//		[5] = {char} 0 '\0'
//		[6] = {char} 0 '\0'
//		[7] = {char} 0 '\0'

		testClient = new Client(event, "127.0.0.1");
		testRequest = new Request;
		equality = new std::string("Check drop method");
		equality2 = new std::string("Another text");
	}
	struct kevent	*event;
	sockaddr_in		*sa_client;
	Client	*testClient;
	Request *testRequest;
	std::string *equality;
	std::string *equality2;
};

TEST_F(ClientRequestFixture, CheckDropMethod) {
	ASSERT_TRUE(testRequest->isEmpty());
	*testRequest += *equality;
	ASSERT_TRUE(testRequest->getRequest() == *equality);
	testRequest->dropRequest();
	ASSERT_TRUE(testRequest->isEmpty());
}


TEST_F(ClientRequestFixture, CheckOperatorsWithCharString) {
	*testRequest += equality2->c_str();
	ASSERT_TRUE(testRequest->getRequest() == *equality2);
	testRequest->dropRequest();
	ASSERT_TRUE(testRequest->isEmpty());
}


TEST_F(ClientRequestFixture, TestGetIpAddressFromSaClient) {
	ASSERT_TRUE(ServerUtils::_get_ip_address(*sa_client) == "127.0.0.1");
}
