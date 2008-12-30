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
 * Test the output for a successful test
 */
TESTPP( test_yaml_complete_success )
{
	std::ostringstream out;
	yaml_testpp_output_c output;
	output.set_stream( out );

	testpp_id_c id( "special_test", "special.cpp", 99 );
	testpp_result_c result;
	output.complete( id, result );
	assertpp( out.str() ) == "    result: success\n";
}

/**
 * Test the output for a failed test
 */
TESTPP( test_yaml_complete_failure )
{
	std::ostringstream out;
	yaml_testpp_output_c output;
	output.set_stream( out );

	testpp_result_c result;
	result.fail( "didn't work", "special.cpp", 80 );

	testpp_id_c id( "special_test", "special_test.cpp", 99 );
	output.complete( id, result );
	assertpp( out.str() ) ==
		"    result: failure\n"
		"    failures:\n"
		"      - message: \"didn't work\"\n"
		"        failure-file: special.cpp\n"
		"        failure-line: 80\n";
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

