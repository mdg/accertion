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


/**
 * A class for storing the result of a testpp unit test.
 */
class testpp_result_c
{
public:
	testpp_result_c()
	: m_failure( false )
	, m_message()
	, m_filename()
	, m_line_number( -1 )
	{}

	/**
	 * Mark this test as failed and give a message.
	 */
	void fail( const std::string &msg, const char *filename = NULL
			, int line = -1 )
	{
		m_failure = true;
		m_message = msg;
		m_filename = filename;
		m_line_number = line;
	}

	/**
	 * Check if this test failed.
	 */
	inline bool failure() const { return m_failure; }
	/**
	 * Get the error message for this test.
	 */
	inline const std::string & message() const { return m_message; }

	/**
	 * Get the file where the failure happened.
	 */
	inline const std::string & filename() const { return m_filename; }
	/**
	 * Get the line number where the failure happened.
	 */
	inline int line_number() const { return m_line_number; }

private:
	bool m_failure;
	std::string m_message;
	std::string m_filename;
	int m_line_number;
};


#endif

