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

#include "testpp_id.h"


bool testpp_suite_c::match( const std::string &suite_name ) const
{
	if ( m_name == suite_name )
		return true;
	if ( m_parent )
		return m_parent->match( suite_name );
	return false;
}


testpp_id_c::testpp_id_c( const std::string &test_name
		, const std::string &file_name, int line_number )
: m_suite( NULL )
, m_test_name( test_name )
, m_file_name( file_name )
, m_line_number( line_number )
{}

testpp_id_c::testpp_id_c( testpp_suite_c &suite, const std::string &test_name
		, const std::string &file_name, int line_number )
: m_suite( &suite )
, m_test_name( test_name )
, m_file_name( file_name )
, m_line_number( line_number )
{}


bool testpp_id_c::in_suite( const std::string &suite_name ) const
{
	if ( suite_name == m_file_name ) {
		return true;
	} else if ( suite_name == m_test_name ) {
		return true;
	} else if ( m_suite && m_suite->match( suite_name ) ) {
		return true;
	} else if ( ( suite_name +".cpp" ) == m_file_name ) {
		return true;
	}
	return false;
}

