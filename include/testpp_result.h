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
	testpp_result_c();

	/**
	 * Mark this test as failed and give a message.
	 */
	void fail( const char *filename, int line, const std::string &msg );

	inline bool failure() const { return m_failure; }
	inline const std::string & message() const { return m_message; }

private:
	bool m_failure;
	std::string m_message;
};


#endif

