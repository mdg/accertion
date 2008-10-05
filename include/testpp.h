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


#include <string>
#include <list>
#include "testpp_assertion.h"
#include "testpp_id.h"


class testpp_output_i;


/**
 * Create the most simple testpp test without attaching it to a suite.
 */
#define TESTPP( test_class ) \
	class test_class : public testpp_c { public: void test(); }; \
	static testpp_runner_c< test_class > test_class##_runner( #test_class \
			, __FILE__, __LINE__ ); \
	void test_class::test()

/**
 * Create a testpp that belongs to the given suite.
 */
#define SUITE_TESTPP( test_class, suite_class ) \
	class test_class : public testpp_c { public: void test(); }; \
	static testpp_runner_c< test_class > test_class##_runner( #test_class \
			, suite_class, __FILE__, __LINE__ ); \
	void test_class::test()

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
	/**
	 * Set the result that this test should run with.
	 */
	void set_result( testpp_result_c & );

	/**
	 * Run the actual testing code.
	 */
	virtual void test() = 0;
	/**
	 * Set up this particular test.
	 */
	virtual void setup() {}
	/**
	 * teardown this particular test.
	 */
	virtual void teardown() {}

protected:
	/**
	 * Create an assertion object for this test.
	 */
	template < typename T >
	testpp_assertion_c< T > assertion( const T &actual_value
			, const std::string &actual_expression
			, const char *filename = NULL, int line = -1 )
	{
		return testpp_assertion_c< T >( *m_result, filename, line
				, actual_value, actual_expression );
	}
	/**
	 * Fail this test with the given message.
	 */
	void fail( const std::string &msg, const char *filename = NULL
			, int line = -1 );

private:
	testpp_result_c *m_result;
};


/**
 * Base interface for running tests
 */
class testpp_runner_i
{
public:
	virtual ~testpp_runner_i();
	virtual testpp_c * create_test() = 0;
	virtual void run_test( testpp_result_c & );

	const testpp_id_c & id() const { return m_id; }
	bool in_suite( const std::string &suite_name ) const
		{ return m_id.in_suite( suite_name ); }

	static void run_all( testpp_output_i & );
	static void run_some( testpp_output_i &
			, const std::string &suite_name );

protected:
	testpp_runner_i( const std::string &name
			, const char *filename = NULL, int line = -1 );
	testpp_runner_i( testpp_suite_c &, const std::string &name
			, const char *filename = NULL, int line = -1 );

private:
	testpp_id_c m_id;

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
};


#endif

