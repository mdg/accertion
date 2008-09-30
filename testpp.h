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
 * Create a testpp test function.
 */
#define OLD_TESTPP( test_func ) \
static void test_func(); \
static testpp_runner test_func##_runner( test_func, #test_func \
		, __FILE__, __LINE__ ); \
void test_func()

#define TESTPP( test_class ) \
class test_class : public testpp_c { void run(); }; \
static testpp_runner test_class##_runner( new test_class(), #test_class \
		, __FILE__, __LINE__ ); \
void test_class##_test::run()



/**
 * Unit test class
 */
class testpp_c
{
public:
	testpp_c();

	void test( testpp_result_c & );
	virtual void run() = 0;

	virtual void setup() {}
	virtual void teardown() {}

protected:
	virtual void run_and_catch();

	template < typename T >
	testpp_assertion_c< T > assertion( const char *filename, int line
			, const T &actual_value );
	void fail( const char *filename, int line, const std::string &msg );

private:
	testpp_result_c *m_result;
};


/**
 * A class that takes a parameter as a testpp_func
 * and stores it to run later.
 */
class testpp_runner
{
public:
	testpp_runner( testpp_c *, const char *test_name
		, const char *file_name, int line_number );
	~testpp_runner();

	/**
	 * Run the test.
	 */
	void run( testpp_result_c & );

	static void run_all();

private:
	testpp_c *m_test;
	std::string m_test_name;
	const char *m_file_name;
	int m_line_number;

	static std::list< testpp_runner * > & runners();
};



#define assertpp( value ) \
	this->assertion( __FILE__, __LINE__, actual_value )

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

