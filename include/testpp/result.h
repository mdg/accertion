#ifndef TESTPP_RESULT_H
#define TESTPP_RESULT_H
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
#include <vector>


/**
 * An object to report each test failure.
 */
class testpp_failure_c
{
public:
	/**
	 * Construct a failure object.
	 */
	testpp_failure_c( const std::string &msg, const std::string &filename
			, int line )
	: m_message( msg )
	, m_file_name( filename )
	, m_line_number( line )
	{}

	/**
	 * Get the error message for this test.
	 */
	inline const std::string & message() const { return m_message; }

	/**
	 * Get the file where the failure happened.
	 */
	inline const std::string & file() const { return m_file_name; }
	/**
	 * Get the line number where the failure happened.
	 */
	inline int line() const { return m_line_number; }

	/**
	 * Get the file where the failure happened.
	 * This is older and more undesirable syntax.
	 * Please use file() instead.
	 */
	inline const std::string & file_name() const { return m_file_name; }
	/**
	 * Get the line number where the failure happened.
	 * This is older and more undesirable syntax.
	 * Please use line() instead.
	 */
	inline int line_number() const { return m_line_number; }

private:
	std::string m_message;
	std::string m_file_name;
	int m_line_number;
};


/**
 * A class for storing the result of a testpp unit test.
 */
class testpp_result_c
{
public:
	typedef std::vector< testpp_failure_c > failure_list;
	typedef failure_list::const_iterator failure_iterator;
public:
	testpp_result_c()
	: m_failure()
	{}

	/**
	 * Mark this test as failed and give a message.
	 */
	void fail( const std::string &msg, const std::string &filename = NULL
			, int line = -1 )
	{
		m_failure.push_back( testpp_failure_c( msg, filename, line ) );
	}

	/**
	 * Check if this test failed.
	 */
	inline bool failure() const { return ! m_failure.empty(); }

	/**
	 * Get the number of failures for this test result.
	 */
	inline int size() const { return m_failure.size(); }

	/**
	 * Get the ith failure.
	 */
	inline const testpp_failure_c & operator [] ( int i ) const
	{
		return m_failure[i];
	}

	/**
	 * Get the begin iterator for the list of failures.
	 */
	inline failure_iterator begin() const { return m_failure.begin(); }
	/**
	 * Get the end iterator for the list of failures.
	 */
	inline failure_iterator end() const { return m_failure.end(); }

private:
	failure_list m_failure;
};


#endif

