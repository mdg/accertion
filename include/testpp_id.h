#ifndef TESTPP_ID_H
#define TESTPP_ID_H
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


class testpp_suite_c;

class testpp_id_c
{
public:
	testpp_id_c( const std::string &test_name, const std::string &file_name
			, int line_number );
	testpp_id_c( testpp_suite_c &, const std::string &test_name
			, const std::string &file_name
			, int line_number );

	bool in_suite( const std::string &suite ) const;
	const std::string & test_name() const { return m_test_name; }
	const std::string & file_name() const { return m_file_name; }
	int line_number() const { return m_line_number; }

private:
	testpp_suite_c *m_suite;
	std::string m_test_name;
	std::string m_file_name;
	int m_line_number;
};


#endif

