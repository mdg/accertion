#ifndef ACCERTION_H
#define ACCERTION_H
// Copyright (c) 2013 Matthew Graham
// See LICENSE.txt for copying permission

#include <string>
#include <stdint.h>


struct AssertionResult
{
	AssertionResult(const std::string &file, int line)
		: file(file)
		, line(line)
		, asserted(false)
		, pass(false)
	{}

	void set(bool p)
	{
		pass = p;
		asserted = true;
	}

	operator bool () const
	{
		return pass && asserted;
	}

	std::string file;
	int line;
	bool asserted;
	bool pass;
};

#define ASSERTION_RESULT (AssertionResult(__FILE__, __LINE__))
#define accert(actual) (accertion(actual, ASSERTION_RESULT))


struct Assertion
{
	AssertionResult &result;
	Assertion(AssertionResult &r)
		: result(r)
	{}
};

struct BoolAssertion
: public Assertion
{
	BoolAssertion(AssertionResult &r, bool b)
		: Assertion(r)
		, actual(b)
	{}
	bool actual;

	void t();
	void f();
};

struct IntAssertion
: public Assertion
{
	IntAssertion(AssertionResult &r, int64_t i)
		: Assertion(r)
		, actual(i)
	{}
	int64_t actual;

	void operator == (int64_t expected);
};

struct PtrAssertion
: public Assertion
{
	PtrAssertion(AssertionResult &r, const void *ptr)
		: Assertion(r)
		, actual(ptr)
	{}
	const void *actual;

	void null();
	void not_null();
};

struct StringAssertion
: public Assertion
{
	StringAssertion(AssertionResult &r, const std::string &s)
		: Assertion(r)
		, actual(s)
	{}
	std::string actual;

	void operator == (const std::string &expected);
};

BoolAssertion accertion(bool actual, const AssertionResult &);
IntAssertion accertion(int actual, const AssertionResult &);
IntAssertion accertion(int64_t actual, const AssertionResult &);
PtrAssertion accertion(const void *actual, const AssertionResult &);
StringAssertion accertion(const std::string &actual, const AssertionResult &);


typedef void (*AccertionTest)();

int add_test(const std::string &name, AccertionTest);
bool run_test(const std::string &name);
void run_tests();
void print_tests(std::ostream &);
int accertion_main(int, const char **);

#define CCTEST(test) \
	void test(); \
	int x_##test = add_test(#test, test); \
	void test()

#endif
