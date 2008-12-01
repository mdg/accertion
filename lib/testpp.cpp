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

#include <testpp/test.h>
#include "default_output.h"
#include <memory>
#include <algorithm>


testpp_c::testpp_c()
: m_result( NULL )
{}

void testpp_c::set_result( testpp_result_c &result )
{
	m_result = &result;
}

void testpp_c::fail( const std::string &msg, const char *filename, int line )
{
	m_result->fail( msg, filename, line );
}


testpp_set_c::~testpp_set_c()
{
	std::list< testpp_type_i * >::iterator it;
	for ( it=m_tests.begin(); it!=m_tests.end(); ++it ) {
		delete *it;
	}
	m_tests.clear();
	m_files.clear();
	m_suites.clear();
}


void testpp_set_c::run_test( testpp_c & test, testpp_result_c &result )
{
	test.set_result( result );
	try {
		test.setup();
		test.test();
		test.teardown();
	} catch (...) {
		std::cerr << "catch...";
	}
}


void testpp_set_c::run( testpp_output_i &out )
{
	std::list< testpp_type_i * >::const_iterator it;
	int i( 0 );
	int passed( 0 );
	int failed( 0 );
	for ( it=m_tests.begin(); it!=m_tests.end(); ++it ) {
		out.begin( (*it)->id() );

		std::auto_ptr< testpp_c > test( (*it)->create_test() );
		testpp_result_c result;
		run_test( *test, result );
		if ( result.failure() ) {
			++failed;
		} else {
			++passed;
		}

		out.complete( (*it)->id(), result );
	}

	out.summarize( passed, failed );
}

void testpp_set_c::run( testpp_output_i &out, const std::string &test_name )
{
	std::list< testpp_type_i * >::iterator it;
	int i( 0 );
	int passed( 0 );
	int failed( 0 );
	for ( it=m_tests.begin(); it!=m_tests.end(); ++it ) {
		if ( ! (*it)->id().in_suite( test_name ) ) {
			continue;
		}

		out.begin( (*it)->id() );

		std::auto_ptr< testpp_c > test( (*it)->create_test() );
		testpp_result_c result;
		run_test( *test, result );
		if ( result.failure() ) {
			++failed;
		} else {
			++passed;
		}

		out.complete( (*it)->id(), result );
	}

	out.summarize( passed, failed );
}


testpp_set_c & testpp_tests()
{
	static testpp_set_c static_set;
	return static_set;
}

