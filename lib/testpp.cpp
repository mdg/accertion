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


testpp_runner_i::testpp_runner_i( const std::string &test_name
	       , const char *file_name, int line_number )
: m_id( test_name, file_name, line_number )
{
	runners().push_back( this );
}

testpp_runner_i::testpp_runner_i( testpp_suite_c &suite
	       , const std::string &test_name, const char *file_name
	       , int line_number )
: m_id( suite, test_name, file_name, line_number )
{
	runners().push_back( this );
}

testpp_runner_i::~testpp_runner_i()
{
	std::list< testpp_runner_i * >::iterator it;
	it = std::find( runners().begin(), runners().end(), this );
	if ( it == runners().end() ) {
		runners().erase( it );
	}
}


void testpp_runner_i::run_test( testpp_result_c &result )
{
	std::auto_ptr< testpp_c > test( create_test() );
	test->set_result( result );
	try {
		test->setup();
		test->test();
		test->teardown();
	} catch (...) {
		std::cerr << "catch...";
	}
}


void testpp_runner_i::run_all( testpp_output_i &out )
{
	std::list< testpp_runner_i * >::iterator it;
	int i( 0 );
	int passed( 0 );
	int failed( 0 );
	for ( it=runners().begin(); it!=runners().end(); ++it ) {
		out.begin( (*it)->id() );

		testpp_result_c result;
		(*it)->run_test( result );
		if ( result.failure() ) {
			++failed;
		} else {
			++passed;
		}

		out.complete( (*it)->id(), result );
	}

	out.summarize( passed, failed );
}

void testpp_runner_i::run_some( testpp_output_i &out, const std::string &suite )
{
	std::list< testpp_runner_i * >::iterator it;
	int i( 0 );
	int passed( 0 );
	int failed( 0 );
	for ( it=runners().begin(); it!=runners().end(); ++it ) {
		if ( ! (*it)->in_suite( suite ) ) {
			continue;
		}

		out.begin( (*it)->id() );

		testpp_result_c result;
		(*it)->run_test( result );
		if ( result.failure() ) {
			++failed;
		} else {
			++passed;
		}

		out.complete( (*it)->id(), result );
	}

	out.summarize( passed, failed );
}


std::list< testpp_runner_i * > & testpp_runner_i::runners()
{
	static std::list< testpp_runner_i * > static_runners;
	return static_runners;
}


testpp_set_c & testpp_tests()
{
	static testpp_set_c static_set;
	return static_set;
}

