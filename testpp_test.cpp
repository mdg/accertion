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


/**
 * Define tests
 */
testpp_suite_c parent_suite( "parent" );
testpp_suite_c simple_suite( "simple", parent_suite );
testpp_suite_c special_suite( "special", parent_suite );


class test_custom
: public testpp_c
{
public:
	void test()
	{
		assertpp( m_x ).t();
		assertpp( m_x ) == 5;
	}

	void setup()
	{
		m_x = 5;
	}

	void teardown()
	{
		m_x = 0;
	}

private:
	int m_x;
};
REGISTER_TESTPP( test_custom );
// REGISTER_SUITE_TESTPP( test_custom, parent_suite );


// expansion of what the TESTPP macro does
class simple_test : public testpp_c { void test(); };
/*
static testpp_runner_i simple_test_runner( new simple_test(), "simple_test"
		, __FILE__, __LINE__ );
		*/
void simple_test::test()
{
}

TESTPP( test_equality )
{
	int value( 5 );
	assertpp( value ) == 5;
}

TESTPP( test_equality_failure )
{
	int value( 5 );
	assertpp( value ) == 4;
}

TESTPP( test_inequality )
{
	int value( 5 );
	assertpp( value ) != 4;
}

TESTPP( test_inequality_failure )
{
	int value( 5 );
	assertpp( value ) != 5;
}

TESTPP( test_string )
{
	std::string value( "hello" );
	assertpp( value ) == "hello";
}

SUITE_TESTPP( suite_test, simple_suite )
{
	assertpp( "hello" ) == "hello";
}

SUITE_TESTPP( multi_suite_test, parent_suite )
{
	assertpp( "hello" ) == "hello";
}

