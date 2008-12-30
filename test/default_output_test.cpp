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

