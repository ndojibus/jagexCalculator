#include "gtest/gtest.h"
#include "../src/someHeader.h"
TEST(SomeTestSuite, SomeTest) {
	MyType obj = new MyType();
	obj->set_the_value(5);
	ASSERT_EQ(obj->get_the_value(), 5);
}