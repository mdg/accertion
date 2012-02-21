#include "test.h"
#include <map>
#include <list>

using namespace std;

struct TestRunner;
struct TestResult;
TestResult *g_current = NULL;


struct TestRunner
{
	virtual ~TestRunner() {}
	virtual void run() = 0;
};

struct StandardTestRunner
: public TestRunner
{
	AccertionTest test;

	StandardTestRunner(AccertionTest t)
		: test(t)
	{}
	virtual void run()
	{
		test();
	}
};

struct TestResult
{
	std::string name;
	std::list< AssertionResult > result;

	TestResult(const std::string &name)
		: name(name)
	{}

	operator bool () const
	{
		if (result.empty()) {
			return false;
		}
		list< AssertionResult >::const_iterator it(result.begin());
		for (; it!=result.end(); ++it) {
			if (! (bool) *it) {
				return false;
			}
		}
		return true;
	}
};


static map< string, TestRunner * > & tests()
{
	static map< string, TestRunner * > mytests;
	return mytests;
}

int add_test(const string &name, AccertionTest test)
{
	tests()[name] = new StandardTestRunner(test);
	return 0;
}

bool run_test(const string &name)
{
	TestRunner *runner = tests()[name];
	TestResult result(name);
	g_current = &result;
	runner->run();
	bool success(result);
	g_current = NULL;
	return success;
}

AssertionResult & attach_result(const AssertionResult &result)
{
	g_current->result.push_back(result);
	return g_current->result.back();
}
