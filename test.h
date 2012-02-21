#ifndef ACCERTION_TEST_H
#define ACCERTION_TEST_H

#include <string>
#include "assertion.h"

typedef void (*AccertionTest)();

int add_test(const std::string &name, AccertionTest);
bool run_test(const std::string &name);
void run_tests();
AssertionResult & attach_result(const AssertionResult &);

#define CCTEST(test) \
	void test(); \
	int x_##test = add_test(#test, test); \
	void test()

#endif
