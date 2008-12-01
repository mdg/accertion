#ifndef TESTPP_TEST_H
#define TESTPP_TEST_H
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


#include <testpp/assertion.h>
#include <testpp/id.h>
#include <string>
#include <list>
#include <set>


class testpp_output_i;


/**
 * Create the most simple testpp test without attaching it to a suite.
 */
#define TESTPP( test_class ) \
	class test_class : public testpp_c { public: void test(); }; \
	int test_class##_value = testpp_tests().add< test_class >( \
		#test_class, __FILE__, __LINE__ ); \
	void test_class::test()

/**
 * Create a testpp that belongs to the given suite.
 */
#define SUITE_TESTPP( test_class, suite_class ) \
	class test_class : public testpp_c { public: void test(); }; \
	int test_class##_value = testpp_tests().add< test_class >( \
		suite_class, #test_class, __FILE__, __LINE__ ); \
	void test_class::test()

/**
 * Register a testpp class to be run.
 */
#define REGISTER_TESTPP( test_class ) \
	int test_class##_value = testpp_tests().add< test_class >( \
		#test_class, __FILE__, __LINE__ )

/**
 * Register a testpp class to be run.
 */
#define REGISTER_SUITE_TESTPP( test_class, suite_class ) \
	int test_class##_value = testpp_tests().add< test_class >( \
		suite_class, #test_class, __FILE__, __LINE__ )


/**
 * Assert something from within a testpp_c::run() implementation
 * The result of this call should be compared or evaluated to actually
 * complete the assertion.  See testpp_assertion_c.
 */
#define assertpp( actual_value ) \
	this->assertion( actual_value, #actual_value, __FILE__, __LINE__ )

/**
 * Fail a test from within a testpp_c::run() implementation
 */
#define failpp( msg ) \
	this->fail( msg, __FILE__, __LINE__ )


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
		return testpp_assertion_c< T >( *m_result
				, actual_value, actual_expression
				, filename, line );
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
	testpp_runner_c( testpp_suite_c &suite, const std::string &name
			, const char *filename = NULL, int line = -1 )
	: testpp_runner_i( suite, name, filename, line )
	{}

	/**
	 * Create the test
	 */
	virtual testpp_c * create_test()
	{
		return new T();
	}
};


/**
 * Interface for matching a test ID to an implemented testpp class.
 */
class testpp_type_i
{
public:
	testpp_id_c id() const { return m_id; }
	virtual testpp_c * create_test() const = 0;
protected:
	testpp_type_i( const testpp_id_c &id )
	: m_id( id )
	{}
private:
	testpp_id_c m_id;
};

/**
 * An object to match a test ID to an implemented test class.
 */
template < typename T >
class testpp_type_c
: public testpp_type_i
{
public:
	/**
	 * Construct a testpp object to match a test ID to an implemented
	 * test class.
	 */
	testpp_type_c( const testpp_id_c &id )
	: testpp_type_i( id )
	{}

	/**
	 * Create an instance of the test class.
	 */
	virtual testpp_c * create_test() const { return new T(); }
};

/**
 * A storage class for holding all the tests & test runners.
 */
class testpp_set_c
{
public:
	/**
	 * Destructor.
	 */
	~testpp_set_c();

	/**
	 * Add a test to this test set.
	 */
	template < typename T >
	int add( const std::string &test_name
			, const std::string &file_name = std::string()
			, int line_num = 0 )
	{
		testpp_id_c id( test_name, file_name, line_num );
		m_files.insert( file_name );
		m_tests.push_back( new testpp_type_c< T >( id ) );
		return m_tests.size();
	}
	/**
	 * Add a test in a suite to this test set.
	 */
	template < typename T >
	int add( testpp_suite_c &suite, const std::string &test_name
			, const std::string &file_name = std::string()
			, int line_num = 0 )
	{
		testpp_id_c id( suite, test_name, file_name, line_num );
		m_files.insert( file_name );
		m_suites.insert( suite.name() );
		m_tests.push_back( new testpp_type_c< T >( id ) );
		return m_tests.size();
	}

	/**
	 * Run all tests with this output type.
	 */
	void run( testpp_output_i & );
	/**
	 * Run some tests as identified by the test name
	 */
	void run( testpp_output_i &, const std::string &test_name );

	/**
	 * Get the set of files included in these tests.
	 */
	const std::set< std::string > & test_files() const { return m_files; }
	/**
	 * Get the set of tests available.
	 */
	const std::set< std::string > & test_suites() const { return m_suites; }

protected:
	void run_test( testpp_c &, testpp_result_c & );

private:
	std::list< testpp_type_i * > m_tests;
	std::set< std::string > m_files;
	std::set< std::string > m_suites;
};

/**
 * Get the static testpp_set for adding
 */
testpp_set_c & testpp_tests();


#endif

