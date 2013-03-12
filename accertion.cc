// Copyright (c) 2013 Matthew Graham
// See LICENSE.txt for copying permission

#include "accertion.h"
#include <map>
#include <list>
#include <iostream>
#include <cstdlib>

using namespace std;
struct TestRunner;
struct TestResult;
TestResult *g_current = NULL;

AssertionResult & attach_result(const AssertionResult &);

void AssertionResult::pass()
{
	if (!asserted) {
		passed = asserted = true;
	}
	// else it passed, then no change, or it failed and leave
	// the failure in place. either way, do nothing.
}

std::ostream & AssertionResult::fail()
{
	asserted = true;
	passed = false;
	return msg;
}

std::string AssertionResult::failure_msg() const
{
	ostringstream fmsg;
	fmsg << msg.str() << "\n@ " << file << ':' << line << endl;
	return fmsg.str();
}

void BoolAssertion::t()
{
	if (actual) {
		result.pass();
	} else {
		result.fail() << result.expr << " is unexpectedly false";
	}
}
void BoolAssertion::f()
{
	if (actual) {
		result.fail() << result.expr << " is unexpectedly true";
	} else {
		result.pass();
	}
}


void PtrAssertion::null()
{
	if (actual) {
		result.fail() << result.expr << " is unexpectedly not null";
	} else {
		result.pass();
	}
}
void PtrAssertion::not_null()
{
	if (actual) {
		result.pass();
	} else {
		result.fail() << result.expr << " is unexpectedly null";
	}
}

void VoidAssertion::still_alive()
{
	result.pass();
}


BoolAssertion & accertion(bool actual, const AssertionResult &result)
{
	return *(new BoolAssertion(attach_result(result), actual));
}

IntAssertion & accertion(int actual, const AssertionResult &result)
{
	return *(new IntAssertion(attach_result(result), actual));
}

IntAssertion & accertion(int64_t actual, const AssertionResult &result)
{
	return *(new IntAssertion(attach_result(result), actual));
}

DoubleAssertion & accertion(double actual, const AssertionResult &r)
{
	return *(new DoubleAssertion(attach_result(r), actual));
}

PtrAssertion & accertion(const void *actual, const AssertionResult &result)
{
	return *(new PtrAssertion(attach_result(result), actual));
}

StringAssertion & accertion(const string &actual, const AssertionResult &result)
{
	return *(new StringAssertion(attach_result(result), actual));
}

VoidAssertion & accertion(const AssertionResult &result)
{
	return *(new VoidAssertion(attach_result(result)));
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

/**
 * counts to summarize a given test run
 */
struct TestSummary
{
	int run() const { return passed + failed + incomplete; }
	int passed;
	int failed;
	int incomplete;
	int assertions;

	TestSummary()
	: passed(0)
	, failed(0)
	, incomplete(0)
	, assertions(0)
	{}

	void operator += (const TestSummary &o)
	{
		passed += o.passed;
		failed += o.failed;
		incomplete += o.incomplete;
		assertions += o.assertions;
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

	TestSummary summarize(ostream &out) const
	{
		TestSummary total;
		if (result.empty()) {
			total.failed = 1;
			out << "No assertions\n";
			return total;
		}
		total.assertions = result.size();
		list< AssertionResult >::const_iterator it(result.begin());
		for (; it!=result.end(); ++it) {
			if (! (bool) *it) {
				total.failed = 1;
				out << it->failure_msg();
				return total;
			}
		}
		total.passed = 1;
		return total;
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

/**
 */
TestSummary run_test(const string &name, ostream &out, ostream &err)
{
	TestRunner *runner = tests()[name];
	if (!runner) {
		cerr << "No test named: " << name << endl;
	}
	TestResult result(name);
	g_current = &result;
	runner->run();
	g_current = NULL;
	TestSummary test_result(result.summarize(err));
	if (test_result.passed) {
		out << "passed ";
	} else if (test_result.failed) {
		out << "failed ";
	} else if (test_result.incomplete) {
		out << "incomplete ";
	}
	out << test_result.assertions << endl;
	return test_result;
}

/**
 * return number of failures, 0 or 1
 */
TestSummary run_tests(istream &in, ostream &out, ostream &err)
{
	string line;
	TestSummary total;
	while (in) {
		getline(in, line);
		if (line.empty()) {
			continue;
		}
		total += run_test(line, out, err);
	}
	return total;
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

void exit_with_usage(ostream &out, const std::string &argv0)
{
	out << "\nUsage:\t" << argv0 << " (list|run|<test name>)\n\n";
	out << "\tlist\t\tshow all tests in this executable\n";
	out << "\trun\t\tread which tests to execute from stdout\n";
	out << "\t<test name>\trun a single test and exit\n";
	out << endl;
	exit(-1);
}

int accertion_main(int argc, const char **argv)
{
	int result(0);
	if (argc == 1) {
		exit_with_usage(cout, argv[0]);
	} else if (argc == 2) {
		string argv1(argv[1]);
		if (argv1 == "list") {
			print_tests(cout);
		} else if (argv1 == "run") {
			TestSummary summary(run_tests(cin, cout, cerr));
			result = summary.failed > 0 ? 1 : 0;
		} else {
			TestSummary singleResult(run_test(argv1, cout, cerr));
			result = singleResult.failed == 1 ? 1 : 0;
		}
	} else {
		exit_with_usage(cout, argv[0]);
	}
	return result;
}
