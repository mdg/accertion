#include "test.h"


BoolAssertion accertion(bool actual, const AssertionResult &result)
{
	return BoolAssertion(attach_result(result), actual);
}

IntAssertion accertion(int actual, const AssertionResult &result)
{
	return IntAssertion(attach_result(result), actual);
}

IntAssertion accertion(int64_t actual, const AssertionResult &result)
{
	return IntAssertion(attach_result(result), actual);
}
