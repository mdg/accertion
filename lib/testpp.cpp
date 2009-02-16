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
#include <ctime>


testpp_c::testpp_c()
: m_result( NULL )
{}

void testpp_c::set_result( testpp_result_c &result )
{
	m_result = &result;
}

void testpp_c::not_implemented()
{
	m_result->set_test_not_implemented();
}

void testpp_c::not_implemented( short year, short month, short day )
{
	if ( is_before( year, month, day ) ) {
		m_result->set_test_not_implemented();
	} else {
		m_result->fail( "not implemented" );
	}
}

void testpp_c::ignore_until( short year, short month, short day )
{
	if ( is_before( year, month, day ) ) {
		m_result->set_ignore_failures();
	}
}

bool testpp_c::is_before( short year, short month, short day )
{
	tm t = { 0 };
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	t.tm_mday = day;
	t.tm_isdst = -1;
	time_t then( mktime( &t ) );
	time_t now( time( NULL ) );
	return ( now < then );
}

void testpp_c::fail( const std::string &msg, const std::string &filename
		, int line )
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
		std::cerr << "catch...\n";
	}
}


void testpp_set_c::run( testpp_output_i &out )
{
	std::list< testpp_type_i * >::const_iterator it;
	int passed( 0 );
	int failed( 0 );
	int ignored( 0 );
	int not_implemented( 0 );

	for ( it=m_tests.begin(); it!=m_tests.end(); ++it ) {
		testpp_type_i &type( **it );
		out.begin( type.id() );

		std::auto_ptr< testpp_c > test( type.create_test() );
		testpp_result_c result;
		run_test( *test, result );
		if ( result.failure() ) {
			++failed;
		} else if ( result.ignore_failures() ) {
			++ignored;
		} else if ( result.test_not_implemented() ) {
			++not_implemented;
		} else {
			++passed;
		}

		out.complete( type.id(), result );
	}

	out.summarize( passed, failed, ignored, not_implemented );
}

void testpp_set_c::run( testpp_output_i &out, const std::string &test_name )
{
	std::list< testpp_type_i * >::iterator it;
	int passed( 0 );
	int failed( 0 );
	int ignored( 0 );
	int not_implemented( 0 );

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
		} else if ( result.ignore_failures() ) {
			++ignored;
		} else if ( result.test_not_implemented() ) {
			++not_implemented;
		} else {
			++passed;
		}

		out.complete( (*it)->id(), result );
	}

	out.summarize( passed, failed, ignored, not_implemented );
}


testpp_set_c & testpp_tests()
{
	static testpp_set_c static_set;
	return static_set;
}

