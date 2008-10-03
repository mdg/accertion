#ifndef TESTPP_H
#define TESTPP_H
/**
 * Copyright 2008 Matthew Graham
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <iostream>
#include <list>
#include "testpp_assertion.h"


/**
 * Create the most simple testpp test without attaching it to a suite.
 */
#define TESTPP( test_class ) \
	class test_class : public testpp_c { public: void run(); }; \
	static testpp_runner_c< test_class > test_class##_runner( #test_class \
			, __FILE__, __LINE__ ); \
	void test_class::run()

/**
 * Create a testpp that belongs to the given suite.
 */
#define SUITE_TESTPP( test_class, suite ) \
	class test_class : public testpp_c { public: void run(); }; \
	static testpp_runner_c< test_class > test_class##_runner( #test_class \
			, __FILE__, __LINE__ ); \
	void test_class::run()

/**
 * Register a testpp class to be run.
 */
#define REGISTER_TESTPP( test_class ) \
	static testpp_runner_c< test_class > test_class##_runner( #test_class \
			, __FILE__, __LINE__ )

/**
 * Register a testpp class to be run.
 */
#define REGISTER_SUITE_TESTPP( test_class, suite_class ) \
	static testpp_runner_c< test_class > test_class##_runner( #test_class \
			, suite_class, __FILE__, __LINE__ )


/**
 * A suite class for grouping tests together.
 */
class testpp_suite_c
{
public:
	/**
	 * Construct a suite that has no parent.
	 */
	testpp_suite_c( const std::string &name )
	: m_name( name )
	, m_parent( NULL )
	{}
	/**
	 * Construct a test suite with a parent.
	 */
	testpp_suite_c( const std::string &name, testpp_suite_c &parent )
	: m_name( name )
	, m_parent( &parent )
	{}

private:
	std::string m_name;
	testpp_suite_c *m_parent;
};


/**
 * The core unit test class.  This should be implemented.
 */
class testpp_c
{
public:
	/**
	 * Construct a testpp object
	 */
	testpp_c();

	void test( testpp_result_c & );
	virtual void run() = 0;

	virtual void setup() {}
	virtual void teardown() {}

protected:
	virtual void run_and_catch();

	template < typename T >
	testpp_assertion_c< T > assertion( const char *filename, int line
			, const T &actual_value
			, const std::string &actual_expression )
	{
		return testpp_assertion_c< T >( *m_result, filename, line
				, actual_value, actual_expression );
	}
	void fail( const char *filename, int line, const std::string &msg );

private:
	testpp_result_c *m_result;
	testpp_suite_c *m_suite;
};


/**
 * Base interface for running tests
 */
class testpp_runner_i
{
public:
	virtual ~testpp_runner_i() {}
	virtual testpp_c * create_test() = 0;
	virtual void run_test( testpp_c &, testpp_result_c & ) = 0;

	static void run_all();

protected:
	testpp_runner_i( const std::string &name
			, const char *filename = NULL, int line = -1 );
	testpp_runner_i( const std::string &name, testpp_suite_c &
			, const char *filename = NULL, int line = -1 );

private:
	std::string m_name;
	testpp_suite_c *m_suite;
	const char *m_filename;
	int m_line;

	static std::list< testpp_runner_i * > & runners();
};

/**
 * A class that takes a parameter as a testpp_func
 * and stores it to run later.
 */
template < class T >
class testpp_runner_c
: public testpp_runner_i
{
public:
	/**
	 * Construct a testpp_runner for a given name and no suite
	 */
	testpp_runner_c( const std::string &name
			, const char *filename = NULL, int line = -1 )
	: testpp_runner_i( name, filename, line )
	{}
	/**
	 * Construct a testpp_runner for a given name and suite
	 */
	testpp_runner_c( const std::string &name, testpp_suite_c &suite
			, const char *filename = NULL, int line = -1 )
	: testpp_runner_i( name, suite, filename, line )
	{}

	/**
	 * Create the test
	 */
	virtual testpp_c * create_test()
	{
		return new T();
	}

	/**
	 * Run the test.  Override this to do special exception handling
	 * if necessary.
	 */
	virtual void run_test( testpp_c &test, testpp_result_c &result )
	{
		test.test( result );
	}
};



/**
 * Assert something from within a testpp_c::run() implementation
 * The result of this call should be compared or evaluated to actually
 * complete the assertion.  See testpp_assertion_c.
 */
#define assertpp( actual_value ) \
	this->assertion( __FILE__, __LINE__, actual_value, #actual_value )

/**
 * Fail a test from within a testpp_c::run() implementation
 */
#define failpp( msg ) \
	this->fail( __FILE__, __LINE__, msg )


#if 0
TESTPP( sample_test )
{
	assertpp( x ).t();
	assertpp( x ).f();
	assertpp( x ) < 0;
	assertpp( x ) != NULL;
	failpp( "this didn't work" );
}
#endif


#endif

