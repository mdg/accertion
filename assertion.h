#ifndef ACCERT_ASSERTION_H
#define ACCERT_ASSERTION_H

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

	void t()
	{
		result.set(actual);
	}
	void f()
	{
		result.set(!actual);
	}
};

struct IntAssertion
: public Assertion
{
	IntAssertion(AssertionResult &r, int64_t i)
		: Assertion(r)
		, actual(i)
	{}
	int64_t actual;

	void operator == (int64_t exp)
	{
		result.set(actual == exp);
	}
};

BoolAssertion accertion(bool actual, const AssertionResult &);
IntAssertion accertion(int actual, const AssertionResult &);
IntAssertion accertion(int64_t actual, const AssertionResult &);

#endif
