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
#include "testpp_result.h"


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
	testpp_assertion_c( testpp_result_c &result, const T &actual_value
			, const std::string &actual_expression
			, const char *filename, int line )
	: m_result( result )
	, m_actual( actual_value )
	, m_expression( actual_expression )
	, m_filename( filename )
	, m_line( line )
	{}

	/**
	 * Assert actual value is true.
	 */
	void t()
	{
		if ( m_actual )
			return;
		fail( "not_true" );
	}
	/**
	 * Assert actual value is false.
	 */
	void f()
	{
		if ( ! m_actual )
			return;
		fail( "not false" );
	}

	/**
	 * Assert equal to an expected value.
	 */
	template < class T2 >
	void operator == ( const T2 &expected )
	{
		if ( m_actual == expected )
			return;
		std::ostringstream out;
		out << m_expression << " == " << m_actual << " != "
			<< expected;
		fail( out.str() );
	}

	/**
	 * Assert not equal to an expected value.
	 */
	template < class T2 >
	void operator != ( const T2 &expected )
	{
		if ( m_actual != expected )
			return;
		std::ostringstream out;
		out << m_expression << " == " << m_actual << " == "
			<< expected;
		fail( out.str() );
	}
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
	/**
	 * Mark the result as failed with the given message.
	 */
	void fail( const std::string &msg )
	{
		m_result.fail( msg, m_filename, m_line );
	}

	testpp_result_c &m_result;
	const T &m_actual;
	const std::string &m_expression;
	const char *m_filename;
	int m_line;
};


#endif

