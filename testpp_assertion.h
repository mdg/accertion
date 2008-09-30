#ifndef TESTPP_ASSERTION_H
#define TESTPP_ASSERTION_H
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

#include <sstream>


/**
 * A class for storing the result of a testpp unit test.
 */
class testpp_result_c
{
public:
	testpp_result_c();

	/**
	 * Mark this test as failed and give a message.
	 */
	void fail( const char *filename, int line, const std::string &msg );

private:
	bool m_failure;
	std::string m_message;
};


/**
 * Assertion class for asserting what a value is.
 */
template < typename T >
class testpp_assertion_c
{
public:
	/**
	 * Construct an assertion class
	 */
	testpp_assertion_c( testpp_result_c &, const char *filename, int line
			, const T &actual_value );

	/**
	 * Assert actual value is true.
	 */
	void t();
	/**
	 * Assert actual value is false.
	 */
	void f();

	/**
	 * Assert equal to an expected value.
	 */
	template < class T2 >
	void operator == ( const T2 &expected )
	{
		if ( m_actual == expected )
			return;
		m_result.fail( m_filename, m_line, "not equal" );
	}

	/**
	 * Assert not equal to an expected value.
	 */
	template < class T2 >
	void operator != ( const T2 &expected );
	/**
	 * Assert actual value less than expected value.
	 */
	template < class T2 >
	void operator < ( const T2 &expected );
	/**
	 * Assert actual value less than or equal to expected value.
	 */
	template < class T2 >
	void operator <= ( const T2 &expected );
	/**
	 * Assert actual value greater than expected value.
	 */
	template < class T2 >
	void operator > ( const T2 &expected );
	/**
	 * Assert actual value greater than or equal to expected value.
	 */
	template < class T2 >
	void operator >= ( const T2 &expected );

	/**
	 * Assert that the actual value is between the upper and lower.
	 */
	template < class T2 >
	void between( const T2 &lower, const T2 &upper );
	/**
	 * Assert that the actual value is within delta of
	 * the expected value.
	 */
	template < class T2 >
	void within( const T2 &expected, const T2 &delta );

private:
	testpp_result_c &m_result;
	const char *m_filename;
	int m_line;
	const T &m_actual;
};


#endif

