#include <testpp/test.h>
#include "default_output.h"


/**
 * Test the summary for the human output class.
 */
TESTPP( test_human_summary )
{
	std::ostringstream out;
	human_testpp_output_c output;
	output.set_stream( out );
	output.summarize( 8, 2, 1, 3 );

	assertpp( out.str() ) == "2 failures in 10 tests\n"
		"1 ignored and 3 not implemented\n";
}


/**
 * Test the summary output for the yaml_output class
 */
TESTPP( test_yaml_summary )
{
	std::ostringstream out;
	yaml_testpp_output_c output;
	output.set_stream( out );
	output.summarize( 8, 2, 1, 3 );

	assertpp( out.str() ) ==
		"passed: 8\n"
		"failed: 2\n"
		"ignored: 1\n"
		"not_implemented: 3\n";
}

