#include <testpp/test.h>
#include <testpp/assertion.h>


TESTPP( test_truth_check_success )
{
	testpp_result_c result;
	testpp_assertion_c< bool > assertion( result, true, "dog", __FILE__
			, __LINE__ );

	assertion.t();

	assertpp( result.failure() ).f();
	assertpp( result.size() ) == 0;
}

TESTPP( test_truth_check_failure )
{
	testpp_result_c result;
	testpp_assertion_c< bool > assertion( result, false, "dog"
			, "test_file", 64 );

	assertion.t();

	assertpp( result.failure() ).t();
	assertpp( result.size() ) == 1;
	testpp_failure_c f( result[0] );

	assertpp( f.message() ) == "dog is not true";
	assertpp( f.file() ) == "test_file";
	assertpp( f.line() ) == 64;
}

TESTPP( test_false_check )
{
	testpp_result_c result;
	testpp_assertion_c< bool > assertion( result, false, "dog", __FILE__
			, __LINE__ );

	assertion.f();

	assertpp( result.failure() ).f();
	assertpp( result.size() ) == 0;
}

TESTPP( test_between_double )
{
	testpp_result_c result;
	testpp_assertion_c< double > assertion( result, 3.9, "dog", __FILE__
			, __LINE__ );
	assertion.between( 3.89, 3.91 );

	assertpp( result.failure() ).f();
	assertpp( result.size() ) == 0;
}

