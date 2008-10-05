#include "testpp.h"
#include "default_output.h"


TESTPP( test_human_summary )
{
	std::ostringstream out;
	human_testpp_output_c output;
	output.set_stream( out );
	output.summarize( 8, 2 );

	assertpp( out.str() ) == "2 failures in 10 tests\n";
}

