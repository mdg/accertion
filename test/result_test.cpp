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

#include "testpp/result.h"
#include "testpp/test.h"


TESTPP( test_failure_constructor )
{
	testpp_failure_c f( "failure msg", "test.cpp", 99 );

	assertpp( f.message() ) == "failure msg";
	assertpp( f.file() ) == "test.cpp";
	assertpp( f.line() ) == 99;
}


TESTPP( test_result_constructor )
{
	testpp_result_c r;

	assertpp( r.failure() ).f();
	assertpp( r.ignore_failures() ).f();
	assertpp( r.test_not_implemented() ).f();
	assertpp( r.size() ) == 0;
}

/**
 * Test that an ignored test has the right output.
 */
TESTPP( test_ignored_result )
{
	testpp_result_c r;
	r.set_ignore_failures();

	assertpp( r.failure() ).f();
	assertpp( r.ignore_failures() ).t();
	assertpp( r.test_not_implemented() ).f();
	assertpp( r.size() ) == 0;
}

/**
 * Test that an ignored test with failures has the right output.
 */
TESTPP( test_ignored_result_with_failures )
{
	testpp_result_c r;
	r.set_ignore_failures();
	r.fail( "this failed", "test.cpp", 80 );

	assertpp( r.failure() ).f();
	assertpp( r.ignore_failures() ).t();
	assertpp( r.test_not_implemented() ).f();
	assertpp( r.size() ) == 1;
}

/**
 * Test what happens when calling not_implemented and fail
 * on the same result.
 */
TESTPP( test_not_implemented_and_failed )
{
	testpp_result_c r;

	r.set_test_not_implemented();
	r.fail( "this also failed", "test.cpp", 80 );

	assertpp( r.failure() ).f();
	assertpp( r.ignore_failures() ).f();
	assertpp( r.test_not_implemented() ).t();
	assertpp( r.size() ) == 1;
}

