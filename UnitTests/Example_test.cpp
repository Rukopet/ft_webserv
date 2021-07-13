#include <gtest/gtest.h>
int check();

TEST(CheckCheck, test_true) {
	assert(1 == 1);
}

TEST(CheckCheck, CheckCheck_new) {
	// simple check return value
	assert(check() == 1);
}

class SuiteName : public ::testing::Test {
	
};
