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


// TESTPP_SUITE( simple_suite );


/*
class simple_test
: public testpp< simple_test >
{
};
*/


class simple_test_x
{
public:
	void test()
	{
		/*
		int x( 5 );
		assertpp( x ).t();
		assertpp( x ) == 5;
		*/
	}

private:
	void run_and_catch()
	{
		/*
		try {
			test();
		} catch ( ... ) {
			// failpp( "exception" );
		}
		*/
	}
};


class simple_test : public testpp_c { void run(); };
static testpp_runner simple_test_runner( new simple_test(), "simple_test"
		, __FILE__, __LINE__ );
void simple_test::run()
{
	int value( 5 );
}

TESTPP( test_simple_2 )
{
	int value( 5 );
	// 5 == actual( value );
	// 4 == actual( value );
}

