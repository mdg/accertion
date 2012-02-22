#include "accertion.h"
#include <map>
#include <list>
#include <iostream>

using namespace std;
struct TestRunner;
struct TestResult;
TestResult *g_current = NULL;

AssertionResult & attach_result(const AssertionResult &);


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

void print_tests(ostream &out)
{
	map< string, TestRunner * >::const_iterator it(tests().begin());
	map< string, TestRunner * >::const_iterator end(tests().end());
	for (; it!=end; ++it) {
		out << it->first << endl;
	}
}

AssertionResult & attach_result(const AssertionResult &result)
{
	g_current->result.push_back(result);
	return g_current->result.back();
}

int accertion_main(int argc, const char **argv)
{
	int result(0);
	if (argc == 1) {
		print_tests(cout);
	} else if (argc == 2) {
		bool success(run_test(argv[1]));
		result = success ? 0 : 1;
	} else {
		cerr << "missing test\n";
		result = -1;
	}
	return result;
}
