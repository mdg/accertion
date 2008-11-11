testpp is a lightweight, easy to use c++ testing framework.

It uses macros for the simplest cases, but doesn't hide a lot of complexity
behind the macros so it can be used without the macros.

Goals:
* Easy to use
* Brief syntax, simple enough to be used without macros if desired
* Can run individual tests, files or suites from the command line
* Various output formats, user-definable
* Clear, operator-based assertion syntax
* Support linux & windows

NOT Goals:
* Supporting every obscure C++ compiler in existence


Example:

#include <testpp.h>

/**
 * This is a simple test to show the syntax in testpp.
 */
TESTPP( simple_test )
{
	// construct an object in the test
	my_object o( 5 );
	// assert that the methods return the expected values
	assertpp( o.doubled() ) == 10;
	assertpp( o.tripled() ) == 15;
}

