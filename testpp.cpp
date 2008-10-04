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

#include "testpp.h"


bool testpp_suite_c::match( const std::string &suite_name ) const
{
	if ( m_name == suite_name )
		return true;
	if ( m_parent )
		return m_parent->match( suite_name );
	return false;
}


testpp_c::testpp_c()
: m_result( NULL )
{}

void testpp_c::set_result( testpp_result_c &result )
{
	m_result = &result;
}

void testpp_c::fail( const char *filename, int line, const std::string &msg )
{
	m_result->fail( filename, line, msg );
}


testpp_runner_i::testpp_runner_i( const std::string &test_name
	       , const char *file_name, int line_number )
: m_test_name( test_name )
, m_suite( NULL )
, m_file_name( file_name )
, m_line_number( line_number )
{
	/*
	static int i( 0 );
	std::cerr << "runners().push_back( " << i++ << " )"
		<< " = " << runners().size() << std::endl;
	*/
	runners().push_back( this );
}

testpp_runner_i::testpp_runner_i( const std::string &test_name
	       , testpp_suite_c &suite, const char *file_name
	       , int line_number )
: m_test_name( test_name )
, m_suite( &suite )
, m_file_name( file_name )
, m_line_number( line_number )
{
	/*
	static int i( 0 );
	std::cerr << "runners().push_back( " << i++ << " )"
		<< " = " << runners().size() << std::endl;
	*/
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

bool testpp_runner_i::in_suite( const std::string &suite_name ) const
{
	if ( suite_name == m_file_name ) {
		return true;
	} else if ( m_suite && m_suite->match( suite_name ) ) {
		return true;
	} else if ( ( suite_name +".cpp" ) == m_file_name ) {
		return true;
	}
	return false;
}


void testpp_runner_i::run_test( testpp_result_c &result )
{
	std::cout << "testpp( " << m_file_name << ':' << m_test_name;
	std::cout << ':' << m_line_number << " )" << std::endl;
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


void testpp_runner_i::run_all()
{
	// std::cerr << "run_all( " << runners().size() << " )\n";
	std::list< testpp_runner_i * >::iterator it;
	int i( 0 );
	int failures( 0 );
	for ( it=runners().begin(); it!=runners().end(); ++it ) {
		testpp_result_c result;
		// std::cerr << "run( " << i++ << " )" << std::endl;
		(*it)->run_test( result );
		if ( result.failure() ) {
			++failures;
			std::cout << "\t" << result.message() << std::endl;
		}
	}

	std::cerr << failures << " failures in " << runners().size()
		<< " tests\n";
}

void testpp_runner_i::run_some( const std::string &suite )
{
	std::list< testpp_runner_i * >::iterator it;
	int i( 0 );
	int failures( 0 );
	int run_count( 0 );
	for ( it=runners().begin(); it!=runners().end(); ++it ) {
		if ( ! (*it)->in_suite( suite ) ) {
			continue;
		}
		++run_count;
		testpp_result_c result;
		// std::cerr << "run( " << i++ << " )" << std::endl;
		(*it)->run_test( result );
		if ( result.failure() ) {
			++failures;
			std::cout << "\t" << result.message() << std::endl;
		}
	}

	std::cout << failures << " failures in " << run_count
		<< " tests\n";
}


std::list< testpp_runner_i * > & testpp_runner_i::runners()
{
	static std::list< testpp_runner_i * > static_runners;
	return static_runners;
}


int main( int argc, char **argv )
{
	if ( argc == 1 ) {
		testpp_runner_i::run_all();
	} else if ( argc == 2 ) {
		testpp_runner_i::run_some( argv[1] );
	}
	return 0;
}

