#include <gtest/gtest.h>
#include "../Client/Request.hpp"
#include "../Client/Client.hpp"

class ClientRequestFixture : public ::testing::Test {

protected:
	virtual void TearDown() {
		delete testRequest;
		delete equality;
		delete equality2;
	}

	virtual void SetUp() {
		testRequest = new Request;
		equality = new std::string("Check drop method");
		equality2 = new std::string("Check drop method");
	}

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


TEST_F(ClientRequestFixture, TestName) {

}
