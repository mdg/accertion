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

	const std::string & name() const { return m_name; }

	bool match( const std::string &suite_name ) const;

private:
	std::string m_name;
	testpp_suite_c *m_parent;
};


/**
 * An object for holding identifying information about tests
 */
class testpp_id_c
{
public:
	/**
	 * Construct a test id object.
	 */
	testpp_id_c( const std::string &test_name, const std::string &file_name
			, int line_number );
	/**
	 * Construct a test id object with a suite.
	 */
	testpp_id_c( testpp_suite_c &, const std::string &test_name
			, const std::string &file_name
			, int line_number );

	/**
	 * Check if this test id is in a given suite.
	 */
	bool in_suite( const std::string &suite ) const;
	/**
	 * Get the name of this test.
	 */
	const std::string & test_name() const { return m_test_name; }
	/**
	 * Get the file that this test is in.
	 */
	const std::string & file_name() const { return m_file_name; }
	/**
	 * Get the line number where this test is created.
	 */
	int line_number() const { return m_line_number; }

private:
	testpp_suite_c *m_suite;
	std::string m_test_name;
	std::string m_file_name;
	int m_line_number;
};


#endif

