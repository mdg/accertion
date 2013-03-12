#ifndef ACCERTION_H
#define ACCERTION_H
// Copyright (c) 2013 Matthew Graham
// See LICENSE.txt for copying permission

#include <string>
#include <sstream>
#include <iostream>
#include <stdint.h>


struct AssertionResult;
struct BoolAssertion;
struct DoubleAssertion;
struct IntAssertion;
struct PtrAssertion;
struct StringAssertion;
struct VoidAssertion;

BoolAssertion & accertion(bool actual, const AssertionResult &);
IntAssertion & accertion(int actual, const AssertionResult &);
IntAssertion & accertion(int64_t actual, const AssertionResult &);
DoubleAssertion & accertion(double actual, const AssertionResult &);
PtrAssertion & accertion(const void *actual, const AssertionResult &);
StringAssertion & accertion(const std::string &actual, const AssertionResult &);
VoidAssertion & accertion(const AssertionResult &);

struct AssertionResult
{
private:
	std::ostringstream msg;

public:
	const char *expr;
	const char *file;
	int line;
	bool asserted;
	bool passed;

	AssertionResult(const char *expr, const char *file, int line)
		: expr(expr)
		, file(file)
		, line(line)
		, asserted(false)
		, passed(false)
		, msg()
	{}
	AssertionResult( const AssertionResult &r)
	: expr(r.expr)
	, file(r.file)
	, line(r.line)
	, asserted(r.asserted)
	, passed(r.passed)
	, msg(r.msg.str())
	{}

	void pass();
	std::ostream & fail();
	std::string failure_msg() const;

	bool failed() const { return asserted && !passed; }
	operator bool () const
	{
		return passed && asserted;
	}
};

#define ASSERTION_RESULT(expr) (AssertionResult(#expr, __FILE__, __LINE__))
#define accert(actual) (accertion(actual, ASSERTION_RESULT(actual)))
#define accert_still_alive() (accertion(ASSERTION_RESULT(void)).still_alive())


struct Assertion
{
	AssertionResult &result;
	Assertion(AssertionResult &r)
		: result(r)
	{}
};

template < typename T >
struct TypedAssertion
: public Assertion
{
	typedef T CType;
	T actual;

	TypedAssertion(AssertionResult &r, const T &v)
	: Assertion(r)
	, actual(v)
	{}
};

template < typename T >
void equal_assertion(T &a, const typename T::CType &expected)
{
	if (expected == a.actual) {
		a.result.pass();
	} else {
		if (a.result.failed()) {
			a.result.fail() << ", != " << expected;
		} else {
			a.result.fail() << a.result.expr << " = " << a.actual
				<< ", != " << expected;
		}
	}
}

template < typename T >
T & lessthan_assertion(T &a, const typename T::CType &expected)
{
	if (a.actual < expected) {
		a.result.pass();
	} else {
		if (a.result.failed()) {
			a.result.fail() << ", not < " << expected;
		} else {
			a.result.fail() << a.result.expr << " = " << a.actual
				<< ", not < " << expected;
		}
	}
	return a;
}

template < typename T >
T & greaterthanequal_assertion(T &a, const typename T::CType &expected)
{
	if (a.actual >= expected) {
		a.result.pass();
	} else {
		if (a.result.failed()) {
			a.result.fail() << ", not >= " << expected;
		} else {
			a.result.fail() << a.result.expr << " = " << a.actual
				<< ", not >= " << expected;
		}
	}
	return a;
}

struct BoolAssertion
: public TypedAssertion< bool >
{
	BoolAssertion(AssertionResult &r, bool b)
	: TypedAssertion(r, b)
	{}

	void t();
	void f();
};

struct IntAssertion
: public TypedAssertion< int64_t >
{
	IntAssertion(AssertionResult &r, int64_t i)
	: TypedAssertion(r, i)
	{}

	friend void operator == (IntAssertion a, int64_t i)
	{
		equal_assertion(a, i);
	}
};

struct DoubleAssertion
: public TypedAssertion< double >
{
	DoubleAssertion(AssertionResult &r, double d)
	: TypedAssertion< double >(r, d)
	{}

	friend void operator == (DoubleAssertion a, double d)
	{
		equal_assertion(a, d);
	}
	friend DoubleAssertion & operator < (DoubleAssertion a, double d)
	{
		return lessthan_assertion(a, d);
	}
	friend DoubleAssertion & operator < (double d, DoubleAssertion a)
	{
		return greaterthanequal_assertion(a, d);
	}
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
: public TypedAssertion< std::string >
{
	StringAssertion(AssertionResult &r, const std::string &s)
	: TypedAssertion(r, s)
	{}

	friend void operator == (StringAssertion a, const std::string &x)
	{
		return equal_assertion(a, x);
	}
};

struct VoidAssertion
: public Assertion
{
	VoidAssertion(AssertionResult &r)
	: Assertion(r)
	{}

	// Assert that the test did not crash
	void still_alive();
};


typedef void (*AccertionTest)();

int add_test(const char *name, AccertionTest
		, const char *file, int lineno);
int accertion_main(int, const char **);

#define CCTEST(test) \
	void test(); \
	int x_##test = add_test(#test, test, __FILE__, __LINE__); \
	void test()

#endif
