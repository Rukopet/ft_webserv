#include "../Server/Server.hpp"
#include <gtest/gtest.h>

//class ExceptionTest : public ::testing::Test {
//
//};

void do_throw() {
	//"CHECK: No such file or directory" error
	if (open("filenameasdasd", O_APPEND) == -1) {
		throw Server_start_exception("CHECK: ");
	}
}

void no_throw() {}

TEST(Server_exception_test, check_what) {
	ASSERT_ANY_THROW(do_throw());
}