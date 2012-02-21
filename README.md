accert is an easy to setup and use C++ testing framework.

It uses macros for the simplest cases, but doesn't hide a lot of complexity
behind the macros so it can be used without the macros.

Goals:
* Easy to use
* Brief syntax, simple enough to be used without macros if desired
* Run individual tests, files or suites from the command line
* Various output formats, user-definable
* Clear, operator-based assertion syntax
* Support linux, windows & mac os X
* C++ only build process, no code generation

NOT Goals:
* Supporting every obscure C++ compiler in existence


Example:

#include <accert.h>

/**
 * This is a simple test to show the accert syntax
 */
CCTEST(simple_test)
{
	// construct an object in the test
	my_object o(5);
	// assert that the methods return the expected values
	accert(o.doubled()) == 10;
	accert(o.tripled()) >= 15;
	accert(o.equals0()).f();

	string s("hello");
	accert(s).ends_with("ello");
	accert(s).begins_with("hel");
}
